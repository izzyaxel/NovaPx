#include "glWidget.hh"
#include "../util/util.hh"
#include "../util/globals.hh"
#include "../graphics/shader.hh"
#include "../graphics/mesh.hh"
#include "../assets/shaders.hh"
#include "../assets/meshes.hh"
#include "../util/threadPool.hh"
#include "../graphics/texture.hh"

#include <QtGui/QMouseEvent>
#include <QtCore/QTime>
#include <QtGui/QOpenGLContext>
#include <exception>
#include <ctime>
#include <chrono>
#include <iris/vec4.hh>
#include <iris/shapes.hh>

UP<Shader> objectShader, orthoShader;
UP<Mesh> llQuadMesh, orthoQuadMesh, centeredQuadMesh;

void screenshotIOThread(std::string const &folderPath, uint32_t width, uint32_t height, std::vector<unsigned char> pixels)
{
	createDirectory(folderPath); //Create the screenshots directory if it doesn't exist
	std::string fileName = "Screenshot ";
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	char dt[16];
	strftime(dt, 16, "%m-%d-%y %H%M%S", &tm); //Produce a formatted date and time string for the filename
	fileName += dt;
	fileName += ".png";
	unsigned char **pngData = new unsigned char *[height * sizeof(unsigned char *)]; //Reorder the data into rows for libpng
	for(unsigned int i = 0; i < height; i++) pngData[i] = new unsigned char[width * 3];
	for(unsigned int x = 0; x < height; x++) memcpy(pngData[height - x - 1], pixels.data() + x * (width * 3), width * 3);
	writePNG(folderPath + fileName, width, height, pngData); //Call to Beast to write the PNG file to disk
	for(uint32_t i = 0; i < height; i++) delete[] pngData[i];
	delete[] pngData;
}

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	camera = MS<Camera>();
	camera->pos = {-100, 100};
	
	this->timer = new QTimer(this);
	QObject::connect(this->timer, &QTimer::timeout, this->timer, [&](){this->update();});
	this->timer->setInterval(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(1.0 / 60.0)));
	this->timer->start();
	
	QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
	fmt.setMajorVersion(4);
	fmt.setMinorVersion(5);
	fmt.setDepthBufferSize(24);
	fmt.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
	fmt.setSwapInterval(1);
	fmt.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
	this->setFormat(fmt);
	this->setFocusPolicy(Qt::ClickFocus);
}

GLWidget::~GLWidget()
{
	this->makeCurrent();
	objectShader.reset();
	orthoShader.reset();
	llQuadMesh.reset();
	orthoQuadMesh.reset();
	centeredQuadMesh.reset();
}

void GLWidget::initializeGL()
{
	this->initializeOpenGLFunctions();
	int major, minor;
	this->glGetIntegerv(GL_MAJOR_VERSION, &major);
	this->glGetIntegerv(GL_MINOR_VERSION, &minor);
	if(major != 4 && minor < 5) throw std::runtime_error("Couldn't start OpenGL, your graphics card doesn't support version 4.5");
	this->glEnable(GL_DEPTH_TEST);
	this->glEnable(GL_SCISSOR_TEST);
	this->glEnable(GL_BLEND);
	this->glDisable(GL_CULL_FACE);
	this->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->glViewport(0, 0, Context::width, Context::height);
	this->glScissor(0, 0, Context::width, Context::height);
	this->glClearColor(0.33f, 0.33f, 0.33f, 0.0f);
	this->glLineWidth(3.0f);
	this->glEnable(GL_LINE_SMOOTH);
	this->glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	this->glPointSize(6.0f);
	
	//Initialize assets
	objectShader = MU<Shader>(defaultVertSource, defaultFragSource);
	orthoShader = MU<Shader>(orthoVertSource, orthoFragSource);
	llQuadMesh = MU<Mesh>(llQuadVerts, 12, llQuadUVs, 8);
	orthoQuadMesh = MU<Mesh>(orthoQuadVerts, 12, orthoQuadUVs, 8);
	centeredQuadMesh = MU<Mesh>(centeredQuadVerts, 12, centeredQuadUVs, 8);
	
	canvas = MS<Image>(getCWD() + "test.png");
}

void GLWidget::resizeGL(int w, int h)
{
	Context::width = static_cast<uint32_t>(w);
	Context::height = static_cast<uint32_t>(h);
	this->glViewport(0, 0, Context::width, Context::height);
	this->glScissor(0, 0, Context::width, Context::height);
	camera->pos.x() = -(Context::width / 2);
	camera->pos.y() = -(Context::height / 2);
	this->v = IR::mat4x4<float>::viewMatrix(IR::quat<float>{}, IR::vec3<float>{camera->pos, 0});
}

void GLWidget::paintGL()
{
	if(canvas)
	{
		this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->v = IR::mat4x4<float>::viewMatrix(IR::quat<float>{}, IR::vec3<float>{camera->pos, 0});
		this->p = IR::mat4x4<float>::orthoProjectionMatrix(0, Context::width, Context::height, 0, 0, 1);
		this->m = IR::mat4x4<float>::modelMatrix(IR::vec3<float>(0, 0, -0.5f), IR::quat<float>{}, IR::vec3<float>(canvas->width * canvas->scale.x(), canvas->height * canvas->scale.y(), 1));
		this->mvp = IR::mat4x4<float>::modelViewProjectionMatrix(this->m, this->v, this->p);
		objectShader->use();
		objectShader->sendMat4f("mvp", this->mvp);
		centeredQuadMesh->use();
		SP<Texture> canvasTexture = MS<Texture>(canvas);
		canvasTexture->use(0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	
	if(Info::screenshotQueued)
	{
		this->screenshot(Info::screenshotDir, Context::width, Context::height);
		Info::screenshotQueued = false;
	}
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	switch(event->button())
	{
		case Qt::LeftButton:
			Mouse::lmbDown = true;
			break;
		
		case Qt::RightButton:
			Mouse::rmbDown = true;
			break;
		
		case Qt::MiddleButton:
			Mouse::mmbDown = true;
			break;
		
		default: break;
	}
	Mouse::pos = IR::vec2<int32_t>(event->x(), event->y());
	Mouse::lastClickPos = IR::vec2<int32_t>(event->x(), event->y());
	
	//IR::mat4x4<float> invVP = (this->v * this->p).inverse();
	//invVP.print("InvVP");
	//IR::vec4<float> worldPoint = IR::vec4<float>(Mouse::pos, 0.0f, 0.0f) * invVP;
	//worldPoint.print("Worldspace point");
	
	IR::mat4x4<float> v2 =
			{1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			1432, 128, 0, 1};
	IR::mat4x4<float> p2 =
			{0.000698, 0, 0, 0,
			0, 0.007812, 0, 0,
			0, 0, -2, 0,
			-1, -1, -1, 1};
	IR::vec4<float> test = {9, 11, 0.5f, 1};
	IR::mat4x4<float> invVP = (v2 * p2).inverse();
	(test * invVP).print("Test");
	
	IR::aabb2D<float> canvasBounds(IR::vec2<float>(0, 0), canvas->scale);
	
/*	if(canvasBounds.containsPoint(imagespacePoint.x(), imagespacePoint.y())) 
	{
		printf("Clicked inside canvas\n\n");
		//canvas->setPixel();
	}*/
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	switch(event->button())
	{
		case Qt::LeftButton:
			Mouse::lmbDown = false;
			Mouse::lmbDownDrag = false;
			break;
		
		case Qt::RightButton:
			Mouse::rmbDown = false;
			Mouse::rmbDownDrag = false;
			break;
		
		case Qt::MiddleButton:
			Mouse::mmbDown = false;
			Mouse::mmbDownDrag = false;
			break;
		
		default: break;
	}
	Mouse::lastReleasePos = IR::vec2<int32_t>(event->x(), event->y());
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	Mouse::prevPos = Mouse::pos;
	Mouse::pos.x() = event->pos().x();
	Mouse::pos.y() = event->pos().y();
	if(Mouse::lmbDown) Mouse::lmbDownDrag = true;
	if(Mouse::rmbDown) Mouse::rmbDownDrag = true;
	if(Mouse::mmbDown) Mouse::mmbDownDrag = true;
	
	if(Mouse::lmbDownDrag && Keyboard::spaceDown)
	{
		IR::vec2<int32_t> delta = Mouse::pos - Mouse::prevPos;
		//delta /= 1.5f;
		delta.x() = -delta.x();
		camera->pos += delta;
	}
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
	canvas->scale += event->delta() > 0 ? 1 : -1;
	if(canvas->scale.x() < 1) canvas->scale.x() = 1;
	if(canvas->scale.y() < 1) canvas->scale.y() = 1;
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Space) Keyboard::spaceDown = true;
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Space) Keyboard::spaceDown = false;
}

void GLWidget::screenshot(std::string const &folderPath, uint32_t width, uint32_t height)
{
	std::vector<unsigned char> pixels;
	pixels.resize(width * height * 3); //Preallocate
	this->glPixelStorei(GL_PACK_ALIGNMENT, 1); //Ensure the pixel data we get from OGL is in the right format
	this->glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data()); //Grab the pixels currently in the buffer and store them in the vector
	threadPool.enqueue(screenshotIOThread, folderPath, width, height, pixels); //I/O will cause a hiccup in the framerate if we don't spin it off into a new asynchronous thread 
}
