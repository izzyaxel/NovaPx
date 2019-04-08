#include "eraserToolButton.hh"

#include "../util/globals.hh"

EraserToolButton::EraserToolButton(QString name, QWidget *parent) : QPushButton(name, parent)
{
	this->connect(this, SIGNAL(clicked()), this, SLOT(selectTool()));
}

void EraserToolButton::selectTool()
{
	State::tool = Tools::ERASER;
}
