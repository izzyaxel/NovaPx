#include "util/window.hh"
#include "util/util.hh"
#include "graphics/camera.hh"
#include "info/globals.hh"
#include "util/widget.hh"
#include "graphics/glWidget.hh"

#include <string>
#include <thread>
#include <QtCore/QTextCodec>
#include <QtWidgets/QApplication>

long long unsigned int ticks = 0;
uint32_t windowWidth = 800, windowHeight = 600;
uint32_t majorVersion = 1, minorVersion  = 0, bugfixVersion = 0;
std::string windowName = "PixelCreator | " + std::to_string(majorVersion) + "." + std::to_string(minorVersion) + "." + std::to_string(bugfixVersion);

Widget *w;

int main(int argc, char **argv)
{
	//setup
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QApplication app = QApplication(argc, argv);
	w = new Widget;
	w->setWindowTitle(QString::fromStdString(windowName));
	QWidget *center = new QWidget;
	w->setCentralWidget(center);
	//create layout and items, shortcuts, connect callbacks, etc
	
	//enter main loop
	w->showMaximized();
	int ret = app.exec();
	
	//cleanup
	//TODO check if canvas has been saved, ask if it hasn't
	renderer.reset();
	eventBus.reset();
	return ret;
}
