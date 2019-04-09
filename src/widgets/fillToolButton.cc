#include "fillToolButton.hh"

#include "../util/globals.hh"
#include "../util/instances.hh"

FillToolButton::FillToolButton(QString name, QWidget *parent) : QPushButton(name, parent)
{
	this->connect(this, SIGNAL(clicked()), this, SLOT(selectTool()));
}

void FillToolButton::selectTool()
{
	State::tool = Tools::FLOODFILL;
	currentToolLabel->setText("Fill");
}
