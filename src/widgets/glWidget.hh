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
	
	QTimer *timer;

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
};
