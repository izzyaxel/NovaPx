#include "widget.hh"
#include "../info/globals.hh"

#include <QtGui/QKeyEvent>

Widget::Widget(QWidget *parent) : QMainWindow(parent)
{
	this->setBaseSize(Context::width, Context::height);
	this->setMinimumSize(Context::width, Context::height);
}

void Widget::resizeEvent(QResizeEvent *event)
{
	
}

void Widget::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Alt)
	{
		
	}
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Alt)
	{
		
	}
}
