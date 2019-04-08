#include "util/util.hh"
#include "util/globals.hh"
#include "util/instances.hh"

#include <iris/vec2.hh>
#include <string>
#include <thread>
#include <QtCore/QTextCodec>
#include <QtWidgets/QApplication>

int main(int argc, char **argv)
{
	State::curColor.fromRGBAf(0.0f, 0.0f, 0.0f, 1.0f);
	State::eraserColor.fromRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
	State::transparencyGridColor1.fromRGBf(0.55f, 0.55f, 0.55f);
	State::transparencyGridColor2.fromRGBf(0.9f, 0.9f, 0.9f);
	State::gridSize = 8;
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QApplication app = QApplication(argc, argv);
	setupGUI();
	mainWindowWidget->showMaximized();
	int ret = app.exec();
	//TODO check if canvas has been saved, ask if it hasn't
	canvas.reset();
	delete canvasWidget;
	return ret;
}
