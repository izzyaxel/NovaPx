#include "glWidget.hh"
#include "../util/util.hh"
#include "../util/globals.hh"
#include "../graphics/shader.hh"
#include "../graphics/mesh.hh"
#include "../assets/shaders.hh"
#include "../assets/meshes.hh"
#include "../util/threadPool.hh"
#include "../util/gui.hh"
#include "../graphics/texture.hh"

#include <QtGui/QMouseEvent>
#include <QtCore/QTime>
#include <QtGui/QOpenGLContext>
#include <exception>
#include <ctime>
#include <chrono>
#include <iris/vec4.hh>
#include <iris/vec2.hh>
#include <iris/shapes.hh>
#include <iris/interpolation.hh>

static void screenshotIOThread(std::string const &folderPath, uint32_t width, uint32_t height, std::vector<unsigned char> pixels)
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

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) //TODO zooming out doesnt work
{
	this->timer = new QTimer(this);
	QObject::connect(this->timer, &QTimer::timeout, this->timer, [&](){this->update();});
	this->timer->setInterval(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(1.0 / this->framerate)));
	this->timer->start();
	
	/*this->zoomTimer = new QTimer(this);
	QObject::connect(this->zoomTimer, &QTimer::timeout, this->zoomTimer, [this]()
	{
		float remap = 1.0f;
		this->progress += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(1.0 / this->framerate)).count() / 1000.0f;
		if(this->progress > remap) this->progress = remap;
		this->progress /= remap;
		float start = static_cast<int32_t>(canvas->scale.x());
		float time = std::min(this->prevAccum, this->accum) / std::max(this->prevAccum, this->accum);
		float end = static_cast<int32_t>(IR::loglerp<float>(Camera::minZoom, Camera::maxZoom, time));
		end = std::max(start + this->sign, end);
		float result = IR::alerp<float>(start, end, this->progress, 2.0f);
		if(result > end) result = end;
		canvas->setScale({result});
		if(this->progress >= remap)
		{
			this->zoomTimer->stop();
			this->progress = 0.0f;
			canvas->setScale({std::floor(canvas->scale.x())});
		}
	});
	this->zoomTimer->setInterval(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(1.0 / this->framerate)));*/
	
	QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
	fmt.setVersion(4, 5);
	fmt.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
	fmt.setSwapInterval(1);
	fmt.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
	this->setFormat(fmt);
	this->setFocusPolicy(Qt::StrongFocus);
}

GLWidget::~GLWidget()
{
	this->makeCurrent();
	Assets::objectShader.reset();
	Assets::centeredQuadMesh.reset();
	delete this->timer;
	//delete this->zoomTimer;
}

void GLWidget::initializeGL()
{
	this->initializeOpenGLFunctions();
	int major, minor;
	this->glGetIntegerv(GL_MAJOR_VERSION, &major);
	this->glGetIntegerv(GL_MINOR_VERSION, &minor);
	if(major != 4 && minor < 5) throw std::runtime_error("Couldn't start OpenGL, your graphics card doesn't support version 4.5+");
	this->glEnable(GL_DEPTH_TEST);
	this->glEnable(GL_SCISSOR_TEST);
	this->glEnable(GL_BLEND);
	this->glDisable(GL_CULL_FACE);
	this->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->glViewport(0, 0, Context::width, Context::height);
	this->glScissor(0, 0, Context::width, Context::height);
	this->glClearColor(0.33f, 0.33f, 0.33f, 1.0f);
	this->glLineWidth(3.0f);
	this->glEnable(GL_LINE_SMOOTH);
	this->glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	this->glPointSize(6.0f);
	
	//Initialize assets
	Assets::objectShader = MU<Shader>(defaultVertSource, defaultFragSource);
	Assets::centeredQuadMesh = MU<Mesh>(centeredQuadVerts, 12, centeredQuadUVs, 8);
	
	canvas = MS<Image>(getCWD() + "test.png");
	canvas->setScale({1});
	
	State::tool = Tools::BRUSH;
}

void GLWidget::resizeGL(int w, int h)
{
	Context::width = static_cast<uint32_t>(w);
	Context::height = static_cast<uint32_t>(h);
	this->glViewport(0, 0, Context::width, Context::height);
	this->glScissor(0, 0, Context::width, Context::height);
	Camera::pos.x() = -(Context::width / 2);
	Camera::pos.y() = -(Context::height / 2);
	this->v = IR::viewMatrix<float>(IR::quat<float>{}, IR::vec3<float>{Camera::pos, 0});
}

void GLWidget::paintGL()
{
	if(canvas && canvas->needsRedraw())
	{
		this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->v = IR::viewMatrix<float>(IR::quat<float>{}, IR::vec3<float>{Camera::pos, 0});
		this->p = IR::orthoProjectionMatrix<float>(0, Context::width, Context::height, 0, 0, 1);
		this->m = IR::modelMatrix<float>(IR::vec3<float>(0, 0, -0.5f), IR::quat<float>{}, IR::vec3<float>(canvas->width * canvas->scale.x(), canvas->height * canvas->scale.y(), 1));
		this->mvp = IR::modelViewProjectionMatrix<float>(this->m, this->v, this->p);
		Assets::objectShader->use();
		Assets::objectShader->sendMat4f("mvp", this->mvp);
		Assets::objectShader->sendUInt("gridSize", State::gridSize);
		Assets::objectShader->sendVec3f("color1", State::transparencyGridColor1.asRGBf());
		Assets::objectShader->sendVec3f("color2", State::transparencyGridColor2.asRGBf());
		Assets::centeredQuadMesh->use();
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

static void modifyCanvas() //TODO pixel selection breaks when panned
{
	IR::vec2<int32_t> worldspaceClick = IR::vec2<int32_t>(Mouse::pos.x(), static_cast<int32_t>(Context::height) - Mouse::pos.y()) + Camera::pos;
	IR::vec2<uint32_t> curCanvasSize(canvas->scale * IR::vec2<uint32_t>(canvas->width, canvas->height));
	IR::vec2<int32_t> canvasOffsets(curCanvasSize / 2);
	if(worldspaceClick.x() > -canvasOffsets.x() && worldspaceClick.x() < canvasOffsets.x() && worldspaceClick.y() > -canvasOffsets.y() && worldspaceClick.y() < canvasOffsets.y())
	{
		IR::vec2<uint32_t> imageSpaceClick(static_cast<uint32_t>(std::abs(worldspaceClick.x() + canvasOffsets.x())), static_cast<uint32_t>(std::abs(worldspaceClick.y() - canvasOffsets.y())));
		IR::vec2<uint32_t> pixelCoord = imageSpaceClick / (curCanvasSize / IR::vec2<uint32_t>(canvas->width, canvas->height));
		switch(State::tool)
		{
			case Tools::BRUSH:
				canvas->setPixel(pixelCoord.x(), pixelCoord.y(), State::curColor);
				break;
			
			case Tools::ERASER:
				canvas->setPixel(pixelCoord.x(), pixelCoord.y(), State::eraserColor);
				break;
			
			case Tools::EYEDROPPER:
				State::curColor = canvas->getPixel(pixelCoord.x(), pixelCoord.y());
				{
					auto c = State::curColor.asRGBui8();
					pickColorButton->setColor(QColor(c.r(), c.g(), c.b()));
				}
				break;
			
			case Tools::FLOODFILL:
				{
					Color c = canvas->getPixel(pixelCoord.x(), pixelCoord.y());
					canvas->floodFill(pixelCoord.x(), pixelCoord.y(), c, State::curColor); //TODO a way to select between the modes
					//canvas->floodFillDiagonal(pixelCoord.x(), pixelCoord.y(), c, State::curColor);
					//canvas->replaceColor(c, State::curColor);
				}
				break;
			
			default: break;
		}
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
	
	if(!Keyboard::spaceDown)
	{
		modifyCanvas();
	}
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
		delta.x() = -delta.x();
		Camera::pos += delta;
	}
	else
	{
		modifyCanvas();
	}
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
	float maxAccum = 50.0f;
	int32_t sign = event->delta() > 0 ? 1 : -1;
	this->accum += sign;
	if(this->accum < 0.0f) this->accum = 0.0f;
	if(this->accum > maxAccum) this->accum = maxAccum;
	canvas->setScale(std::max({std::max(1.0f, std::floor(IR::alerp<float>(Camera::minZoom, Camera::maxZoom, this->accum / maxAccum, 1.2f)))}));
	
	/*if(this->progress == 0)
	{
		this->sign = event->delta() > 0 ? 1 : -1;
		this->prevAccum = this->accum;
		this->accum += this->sign;
		if(this->accum < 0.0f) this->accum = 0.0f;
		if(this->accum > this->maxAccum) this->accum = this->maxAccum;
		this->zoomTimer->start();
	}*/
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
	pixels.resize(width * height * 3);
	this->glPixelStorei(GL_PACK_ALIGNMENT, 1); //Ensure the pixel data we get from OGL is in the right format
	this->glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data()); //Grab the pixels currently in the buffer
	threadPool.enqueue(screenshotIOThread, folderPath, width, height, pixels); //File I/O will cause a hiccup if we don't spin it into a new async thread 
}
