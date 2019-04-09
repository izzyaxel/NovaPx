#include "eyedropperToolButton.hh"

#include "../util/globals.hh"
#include "../util/instances.hh"

EyedropperToolButton::EyedropperToolButton(QString name, QWidget *parent) : QPushButton(name, parent)
{
	this->connect(this, SIGNAL(clicked()), this, SLOT(selectTool()));
}

void EyedropperToolButton::selectTool()
{
	State::tool = Tools::EYEDROPPER;
	currentToolLabel->setText("Eyedropper");
}
