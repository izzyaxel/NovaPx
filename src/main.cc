#include "util/util.hh"
#include "graphics/camera.hh"
#include "util/globals.hh"
#include "widgets/mainWindowWidget.hh"
#include "widgets/glWidget.hh"

#include <string>
#include <thread>
#include <QtCore/QTextCodec>
#include <QtWidgets/QApplication>

long long unsigned int ticks = 0;
uint32_t windowWidth = 800, windowHeight = 600;
uint32_t majorVersion = 1, minorVersion  = 0, bugfixVersion = 0;
std::string windowName = "PixelCreator | " + std::to_string(majorVersion) + "." + std::to_string(minorVersion) + "." + std::to_string(bugfixVersion);

MainWindowWidget *mainWindowWidget;
GLWidget *canvasWidget;
QWidget *testWidget;

int main(int argc, char **argv)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QApplication app = QApplication(argc, argv);
	
	mainWindowWidget = new MainWindowWidget;
	canvasWidget = new GLWidget;
	testWidget = new QWidget;
	
	mainWindowWidget->setWindowTitle(QString::fromStdString(windowName));
	mainWindowWidget->setCentralWidget(canvasWidget);
	//TODO create layout and items, shortcuts, connect callbacks, etc
	
	mainWindowWidget->showMaximized();
	int ret = app.exec();
	//TODO check if canvas has been saved, ask if it hasn't
	renderer.reset();
	delete testWidget;
	delete canvasWidget;
	delete mainWindowWidget;
	return ret;
}
