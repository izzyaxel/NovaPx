#include "mainWindowWidget.hh"
#include "../util/globals.hh"

#include <QtGui/QKeyEvent>

MainWindowWidget::MainWindowWidget() : QMainWindow()
{
	
}

void MainWindowWidget::resizeEvent(QResizeEvent *event)
{
	
}

void MainWindowWidget::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Alt)
	{
		
	}
}

void MainWindowWidget::keyReleaseEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Alt)
	{
		
	}
}
