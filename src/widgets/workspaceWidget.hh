#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QTimer>
#include <QtGui/QWheelEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QImage>

struct WorkspaceWidget : public QWidget
{
	Q_OBJECT
public:
	WorkspaceWidget(QWidget *parent = nullptr);
	~WorkspaceWidget();
	
	QTimer *updateTimer;
	QImage qCanvas;

protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

private:
	float accum = 0, maxAccum = 50, framerate = 60;
};
