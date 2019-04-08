#include "pickColorButton.hh"
#include "../util/globals.hh"

#include <QtWidgets/QColorDialog>

PickColorButton::PickColorButton(QWidget *parent)
{
	this->setParent(parent);
	this->connect(this, SIGNAL(clicked()), this, SLOT(changeColor()));
	this->color.fromRgb(0, 0, 0, 255);
	this->updateColor();
}

void PickColorButton::updateColor()
{
	this->setStyleSheet(R"(
QPushButton
{
	background-color: )" + this->color.name() + R"(;
	border 1px solid rgb(200, 200, 200);
})");
}

void PickColorButton::changeColor()
{
	QColor newColor = QColorDialog::getColor(this->color, this->parentWidget());
	if(newColor != this->color) this->setColor(newColor);
}

void PickColorButton::setColor(QColor const &color)
{
	this->color = color;
	this->updateColor();
	State::curColor.fromRGBAui8(static_cast<uint8_t>(this->color.red()), static_cast<uint8_t>(this->color.green()), static_cast<uint8_t>(this->color.blue()), static_cast<uint8_t>(this->color.alpha()));
}
