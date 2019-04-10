#include "workspaceWidget.hh"
#include "../util/globals.hh"
#include "../util/gui.hh"

#include <chrono>
#include <iris/vec2.hh>

static void modifyCanvas()
{
	IR::vec2<int32_t> worldspaceClick = Mouse::pos + Camera::pos;
	worldspaceClick.y() = -worldspaceClick.y();
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

WorkspaceWidget::WorkspaceWidget(QWidget *parent) : QWidget(parent)
{
	this->timer = new QTimer(this);
	QObject::connect(this->timer, &QTimer::timeout, this->timer, [&](){this->update();});
	this->timer->setInterval(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(1.0 / 60.0)));
	this->timer->start();
}

WorkspaceWidget::~WorkspaceWidget()
{
	delete this->timer;
}

void WorkspaceWidget::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Space) Keyboard::spaceDown = true;
}

void WorkspaceWidget::keyReleaseEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Space) Keyboard::spaceDown = false;
}

void WorkspaceWidget::mousePressEvent(QMouseEvent *event)
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
	modifyCanvas();
}

void WorkspaceWidget::mouseReleaseEvent(QMouseEvent *event)
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

void WorkspaceWidget::mouseMoveEvent(QMouseEvent *event)
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

static float loglerp(float a, float b, float progress)
{
	return a * std::pow(b / a, progress);
}

void WorkspaceWidget::wheelEvent(QWheelEvent *event)
{
	int32_t sign = event->delta() > 0 ? 1 : -1;
	this->accum += sign;
	if(this->accum < 0.0f) this->accum = 0.0f;
	if(this->accum > this->maxAccum) this->accum = this->maxAccum;
	canvas->setScale({std::max<int32_t>(canvas->scale.x() + 1, static_cast<int32_t>(loglerp(Camera::minZoom, Camera::maxZoom, this->accum / maxAccum)))});
}
