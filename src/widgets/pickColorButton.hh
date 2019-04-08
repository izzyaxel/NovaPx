#pragma once

#include "../graphics/color.hh"

#include <QtWidgets/QPushButton>
#include <QtGui/QColor>

struct PickColorButton : public QPushButton
{
	Q_OBJECT
public:
	PickColorButton(QWidget *parent = nullptr);
	void setColor(QColor const &color);

public slots:
	void updateColor();
	void changeColor();

private:
	QColor color;
};
