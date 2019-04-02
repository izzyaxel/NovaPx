#include "glWidget.hh"
#include "../util/util.hh"
#include "../info/globals.hh"

#include <QtGui/QMouseEvent>
#include <QtCore/QTime>
#include <QtGui/QOpenGLContext>
#include <exception>

static void *wrapperProcLoader(char const *name)
{
	return reinterpret_cast<void *>(QOpenGLContext::currentContext()->getProcAddress(name));
}

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), QOpenGLFunctions_4_5_Core()
{
	this->timer = new QTimer(this);
	QObject::connect(this->timer, &QTimer::timeout, this->timer, [&](){this->update();});
	this->timer->start(0);
	eventBus = MU<EventBus>();
}

void GLWidget::initializeGL()
{
	QSurfaceFormat fmt;
	fmt.setMajorVersion(4);
	fmt.setMinorVersion(5);
	fmt.setDepthBufferSize(24);
	fmt.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
	fmt.setSwapInterval(1);
	fmt.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
	this->setFormat(fmt);
	QOpenGLFunctions_4_5_Core *funcs = nullptr;
	funcs = this->context()->versionFunctions<QOpenGLFunctions_4_5_Core>();
	if(!funcs)
	{
		throw std::runtime_error("Couldn't start OpenGL, your graphics card doesn't support version 4.5");
	}
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, Context::width, Context::height);
	glScissor(0, 0, Context::width, Context::height);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glLineWidth(3.0f);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glPointSize(6.0f);
	renderer = MU<Renderer>();
}

void GLWidget::resizeGL(int w, int h)
{
	Context::width = static_cast<uint32_t>(w);
	Context::height = static_cast<uint32_t>(h);
	renderer->onResize();
}

void GLWidget::paintGL()
{
	renderer->render();
	if(Info::screenshotQueued)
	{
		renderer->screenshot(Info::screenshotDir, Context::width, Context::height);
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
	QPoint cPos = QCursor::pos();
	Mouse::pos.x() = cPos.x();
	Mouse::pos.y() = cPos.y();
	if(Mouse::lmbDown) Mouse::lmbDownDrag = true;
	if(Mouse::rmbDown) Mouse::rmbDownDrag = true;
	if(Mouse::mmbDown) Mouse::mmbDownDrag = true;
}
