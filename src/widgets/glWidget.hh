#pragma once

#include <QtGui/QOpenGLFunctions_4_5_Core>
#include <QtWidgets/QOpenGLWidget>
#include <QtCore/QTimer>
#include <QtGui/QWheelEvent>
#include <QtGui/QKeyEvent>
#include <iris/mat4.hh>

struct GLWidget : public QOpenGLWidget, private QOpenGLFunctions_4_5_Core
{
	Q_OBJECT
	
public:
	GLWidget(QWidget *parent = nullptr);
	~GLWidget();
	
	void screenshot(std::string const &folderPath, uint32_t width, uint32_t height);
	
	QTimer *timer, *zoomTimer;

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

private:
	IR::mat4x4<float> m, v, p, mvp;
	float prevAccum = 0.0f, accum = 0.0f, maxAccum = 30, zoomTimerDuration = 10.0f, progress = 0.0;
	double framerate = 120.0;
	int32_t sign = 1;
};
