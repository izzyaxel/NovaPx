#pragma once

#include <QtWidgets/QPushButton>

struct EraserToolButton : public QPushButton
{
	Q_OBJECT
public:
	EraserToolButton(QString name, QWidget *parent = nullptr);

public slots:
	void selectTool();
};
