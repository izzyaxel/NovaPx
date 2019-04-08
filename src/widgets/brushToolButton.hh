#pragma once

#include <QtWidgets/QPushButton>

struct BrushToolButton : public QPushButton
{
	Q_OBJECT
public:
	BrushToolButton(QString name, QWidget *parent = nullptr);

public slots:
	void selectTool();
};
