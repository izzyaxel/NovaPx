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

long long unsigned int ticks = 0;
uint32_t windowWidth = 800, windowHeight = 600;
uint32_t majorVersion = 1, minorVersion  = 0, bugfixVersion = 0;
std::string windowName = "PixelCreator | " + std::to_string(majorVersion) + "." + std::to_string(minorVersion) + "." + std::to_string(bugfixVersion);

QVBoxLayout *mainLayout;
QHBoxLayout *subLayout;

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
	
	subLayout = new QHBoxLayout;
	subLayout->setContentsMargins(0, 0, 0, 0);
	subLayout->setSpacing(0);
	
	center = new QWidget;
	
	mainWindowWidget = new MainWindowWidget;
	mainWindowWidget->setWindowTitle(QString::fromStdString(windowName));
	mainWindowWidget->setCentralWidget(center);
	mainWindowWidget->setStyleSheet(R"(
QMainWindow
{
	background-color: rgb(40, 40, 40);
	color: rgb(255, 255, 255);
})");
	
	canvasWidget = new GLWidget;
	canvasWidget->setMinimumSize(128, 128);
	canvasWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	timelineContainer = new QWidget;
	timelineContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	timelineContainer->setStyleSheet(R"(
QWidget
{
	background-color: rgb(255, 0, 0);
})");
	
	leftBarContainer = new QWidget;
	leftBarContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	leftBarContainer->setStyleSheet(R"(
QWidget
{
	background-color: rgb(0, 255, 0);
})");
	
	rightBarContainer = new QWidget;
	rightBarContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	rightBarContainer->setStyleSheet(R"(
QWidget
{
	background-color: rgb(0, 0, 255);
})");
	
	//Menus
	menuBar = new QMenuBar;
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
	subLayout->addWidget(leftBarContainer, Qt::AlignLeft);
	subLayout->addWidget(canvasWidget);
	subLayout->addWidget(rightBarContainer, Qt::AlignRight);
	
	mainLayout->addWidget(menuBar);
	mainLayout->addLayout(subLayout, 1);
	mainLayout->addWidget(timelineContainer, Qt::AlignBottom);
	
	center->setLayout(mainLayout);
	
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
