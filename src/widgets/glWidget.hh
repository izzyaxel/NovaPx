#pragma once

#include <QtGui/QOpenGLFunctions_4_5_Core>
#include <QtWidgets/QOpenGLWidget>
#include <QtCore/QTimer>

struct GLWidget : public QOpenGLWidget
{
	Q_OBJECT
	
public:
	GLWidget(QWidget *parent = nullptr);
	
	QTimer *timer;
	QOpenGLFunctions_4_5_Core *funcs;

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
};
