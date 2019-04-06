#include "util/util.hh"
#include "graphics/camera.hh"
#include "util/globals.hh"
#include "widgets/mainWindowWidget.hh"
#include "widgets/glWidget.hh"

#include <iris/vec2.hh>
#include <string>
#include <thread>
#include <QtCore/QTextCodec>
#include <QtWidgets/QApplication>
#include <QtWidgets/QShortcut>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSplitter>

long long unsigned int ticks = 0;
uint32_t windowWidth = 800, windowHeight = 600;
uint32_t majorVersion = 1, minorVersion  = 0, bugfixVersion = 0;
std::string windowName = "PixelCreator | " + std::to_string(majorVersion) + "." + std::to_string(minorVersion) + "." + std::to_string(bugfixVersion);

QVBoxLayout *mainLayout;
QSplitter *vSplitter, *hSplitter;

QWidget *center, *timelineContainer, *leftBarContainer, *rightBarContainer;
MainWindowWidget *mainWindowWidget;
GLWidget *canvasWidget;

QMenuBar *menuBar;
QMenu *fileMenu;
QMenu *editMenu;
QMenu *helpMenu;

QAction *screenshotAction;
QShortcut *screenshotShortcut;

int main(int argc, char **argv)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QApplication app = QApplication(argc, argv);
	
	mainLayout = new QVBoxLayout;
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);
	
	center = new QWidget(mainWindowWidget);
	center->setLayout(mainLayout);
	
	mainWindowWidget = new MainWindowWidget;
	mainWindowWidget->setWindowTitle(QString::fromStdString(windowName));
	mainWindowWidget->setMinimumSize(640, 480);
	mainWindowWidget->setCentralWidget(center);
	mainWindowWidget->setStyleSheet(R"(
QMainWindow
{
	background-color: rgb(40, 40, 40);
	color: rgb(255, 255, 255);
})");
	
	vSplitter = new QSplitter(center);
	vSplitter->setContentsMargins(0, 0, 0, 0);
	vSplitter->setMinimumSize(100, 100);
	vSplitter->setOrientation(Qt::Vertical);
	vSplitter->setStyleSheet(R"(
QSplitter::handle
{
	background-color: rgb(120, 120, 120);
	border: 1px solid rgb(40, 40, 40);
})");
	
	hSplitter = new QSplitter(vSplitter);
	hSplitter->setContentsMargins(0, 0, 0, 0);
	hSplitter->setMinimumSize(100, 100);
	hSplitter->setOrientation(Qt::Horizontal);
	hSplitter->setStyleSheet(R"(
QSplitter::handle
{
	background-color: rgb(120, 120, 120);
	border: 1px solid rgb(40, 40, 40);
})");
	
	canvasWidget = new GLWidget(hSplitter);
	canvasWidget->setMinimumSize(256, 256);
	canvasWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	
	timelineContainer = new QWidget(vSplitter);
	timelineContainer->setMinimumSize(100, 100);
	timelineContainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	timelineContainer->setStyleSheet(R"(
QWidget
{
	background-color: rgb(255, 0, 0);
})");
	
	leftBarContainer = new QWidget(hSplitter);
	leftBarContainer->setMinimumSize(100, 100);
	leftBarContainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	leftBarContainer->setStyleSheet(R"(
QWidget
{
	background-color: rgb(0, 255, 0);
})");
	
	rightBarContainer = new QWidget(hSplitter);
	rightBarContainer->setMinimumSize(100, 100);
	rightBarContainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	rightBarContainer->setStyleSheet(R"(
QWidget
{
	background-color: rgb(0, 0, 255);
})");
	
	//Menus
	menuBar = new QMenuBar(center);
	menuBar->setStyleSheet(R"(
QMenuBar
{
	background-color: rgb(60, 60, 60);
	color: rgb(255, 255, 255);
}
QMenuBar:item:pressed
{
	background-color: rgb(90, 90, 90);
}
QMenuBar:item:selected
{
	background-color: rgb(90, 90, 90);
})");
	
	fileMenu = menuBar->addMenu("File");
	editMenu = menuBar->addMenu("Edit");
	helpMenu = menuBar->addMenu("Help");
	
	//Layouts
	hSplitter->addWidget(leftBarContainer);
	hSplitter->addWidget(canvasWidget);
	hSplitter->addWidget(rightBarContainer);
	hSplitter->setStretchFactor(0, 2);
	hSplitter->setStretchFactor(1, 10);
	hSplitter->setStretchFactor(2, 1);
	
	vSplitter->addWidget(hSplitter);
	vSplitter->addWidget(timelineContainer);
	vSplitter->setStretchFactor(0, 5); //TODO not affecting the layout at all
	vSplitter->setStretchFactor(1, 1);
	
	mainLayout->addWidget(menuBar);
	mainLayout->addWidget(vSplitter);
	
	//Actions
	screenshotAction = new QAction("Save Preview");
	QObject::connect(screenshotAction, &QAction::triggered, screenshotAction, [&](){canvasWidget->screenshot(getCWD() + "previews/", Context::width, Context::height);});
	
	//Shortcuts
	screenshotShortcut = new QShortcut(QKeySequence(Qt::Key_F12), canvasWidget);
	QObject::connect(screenshotShortcut, SIGNAL(activated()), screenshotAction, SLOT(trigger()));
	
	mainWindowWidget->showMaximized();
	int ret = app.exec();
	//TODO check if canvas has been saved, ask if it hasn't
	delete canvasWidget;
	return ret;
}
