#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>

struct MainWindowWidget : public QMainWindow
{
Q_OBJECT

public:
	MainWindowWidget();
	
	void resizeEvent(QResizeEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
};
