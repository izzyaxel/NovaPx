#include "glWidget.hh"
#include "../util/util.hh"
#include "../util/globals.hh"

#include <QtGui/QMouseEvent>
#include <QtCore/QTime>
#include <QtGui/QOpenGLContext>
#include <exception>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	camera = MS<Camera>();
	
	this->timer = new QTimer(this);
	QObject::connect(this->timer, &QTimer::timeout, this->timer, [&](){this->update();});
	this->timer->start(0);
	
	QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
	fmt.setMajorVersion(4);
	fmt.setMinorVersion(5);
	fmt.setDepthBufferSize(24);
	fmt.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
	fmt.setSwapInterval(1);
	fmt.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
	this->setFormat(fmt);
}

void GLWidget::initializeGL()
{
	this->funcs = this->context()->versionFunctions<QOpenGLFunctions_4_5_Core>();
	int major, minor;
	this->funcs->glGetIntegerv(GL_MAJOR_VERSION, &major);
	this->funcs->glGetIntegerv(GL_MINOR_VERSION, &minor);
	if(major != 4 && minor != 5)
	{
		throw std::runtime_error("Couldn't start OpenGL, your graphics card doesn't support version 4.5");
	}
	this->funcs->glEnable(GL_DEPTH_TEST);
	this->funcs->glEnable(GL_SCISSOR_TEST);
	this->funcs->glEnable(GL_BLEND);
	this->funcs->glDisable(GL_CULL_FACE);
	this->funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->funcs->glViewport(0, 0, Context::width, Context::height);
	this->funcs->glScissor(0, 0, Context::width, Context::height);
	this->funcs->glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	this->funcs->glLineWidth(3.0f);
	this->funcs->glEnable(GL_LINE_SMOOTH);
	this->funcs->glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	this->funcs->glPointSize(6.0f);
	renderer = MU<Renderer>(this->funcs);
	canvas = MS<Image>(getCWD() + "test.png");
}

void GLWidget::resizeGL(int w, int h)
{
	Context::width = static_cast<uint32_t>(w);
	Context::height = static_cast<uint32_t>(h);
	renderer->onResize(this->funcs);
}

void GLWidget::paintGL()
{
	renderer->render(this->funcs);
	if(Info::screenshotQueued)
	{
		renderer->screenshot(Info::screenshotDir, Context::width, Context::height, this->funcs);
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
	Mouse::lastClickPos = IR::vec2<int32_t>(event->x(), event->y());
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
}
