#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>

struct Widget : public QMainWindow
{
	Widget(QWidget *parent = nullptr);
	
	void resizeEvent(QResizeEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

Q_OBJECT
};
