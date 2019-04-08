#pragma once

#include <QtWidgets/QPushButton>

struct FillToolButton : public QPushButton
{
Q_OBJECT
public:
	FillToolButton(QString name, QWidget *parent = nullptr);

public slots:
	void selectTool();
};
