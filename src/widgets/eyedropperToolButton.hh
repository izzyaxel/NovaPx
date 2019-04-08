#pragma once

#include <QtWidgets/QPushButton>

struct EyedropperToolButton : public QPushButton
{
	Q_OBJECT
public:
	EyedropperToolButton(QString name, QWidget *parent = nullptr);

public slots:
	void selectTool();
};
