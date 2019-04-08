#include "instances.hh"
#include "globals.hh"
#include "util.hh"

QVBoxLayout *mainLayout = nullptr, *leftBarLayout = nullptr;
QSplitter *vSplitter = nullptr, *hSplitter = nullptr;

QWidget *center = nullptr, *timelineContainer = nullptr, *leftBarContainer = nullptr, *rightBarContainer = nullptr;
MainWindowWidget *mainWindowWidget = nullptr;
GLWidget *canvasWidget = nullptr;
PickColorButton *pickColorButton = nullptr;
BrushToolButton *brushToolButton = nullptr;
EraserToolButton *eraserToolButton = nullptr;
EyedropperToolButton *eyedropperToolButton = nullptr;

QMenuBar *menuBar = nullptr;
QMenu *fileMenu = nullptr;
QMenu *editMenu = nullptr;
QMenu *helpMenu = nullptr;

QAction *screenshotAction = nullptr, *changeToBrushAction = nullptr, *changeToEraserAction = nullptr;
QShortcut *screenshotShortcut = nullptr;

void setupGUI()
{
	mainLayout = new QVBoxLayout;
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);
	
	center = new QWidget(mainWindowWidget);
	center->setLayout(mainLayout);
	
	mainWindowWidget = new MainWindowWidget;
	mainWindowWidget->setWindowTitle(QString::fromStdString(Info::windowName));
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
	background-color: rgb(30, 30, 30);
})");
	
	leftBarContainer = new QWidget(hSplitter);
	leftBarContainer->setMinimumSize(100, 100);
	leftBarContainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	leftBarContainer->setStyleSheet(R"(
QWidget
{
	background-color: rgb(30, 30, 30);
})");
	
	leftBarLayout = new QVBoxLayout(leftBarContainer);
	leftBarContainer->setLayout(leftBarLayout);
	
	rightBarContainer = new QWidget(hSplitter);
	rightBarContainer->setMinimumSize(100, 100);
	rightBarContainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	rightBarContainer->setStyleSheet(R"(
QWidget
{
	background-color: rgb(30, 30, 30);
})");
	
	pickColorButton = new PickColorButton(leftBarContainer);
	pickColorButton->setFixedSize(30, 30);
	pickColorButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	
	brushToolButton = new BrushToolButton("B", leftBarContainer);
	brushToolButton->setFixedSize(30, 30);
	brushToolButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	brushToolButton->setStyleSheet(R"(
QPushButton
{
	background-color: rgb(60, 60, 60);
	color: white;
})");
	
	eraserToolButton = new EraserToolButton("E", leftBarContainer);
	eraserToolButton->setFixedSize(30, 30);
	eraserToolButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	eraserToolButton->setStyleSheet(R"(
QPushButton
{
	background-color: rgb(60, 60, 60);
	color: white;
})");
	
	eyedropperToolButton = new EyedropperToolButton("P", leftBarContainer);
	eyedropperToolButton->setFixedSize(30, 30);
	eyedropperToolButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	eyedropperToolButton->setStyleSheet(R"(
QPushButton
{
	background-color: rgb(60, 60, 60);
	color: white;
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
	hSplitter->setStretchFactor(0, 3);
	hSplitter->setStretchFactor(1, 10);
	hSplitter->setStretchFactor(2, 2);
	
	vSplitter->addWidget(hSplitter);
	vSplitter->addWidget(timelineContainer);
	vSplitter->setStretchFactor(0, 5);
	vSplitter->setStretchFactor(1, 1);
	
	leftBarLayout->addWidget(brushToolButton);
	leftBarLayout->addWidget(eraserToolButton);
	leftBarLayout->addWidget(eyedropperToolButton);
	leftBarLayout->addWidget(pickColorButton);
	
	mainLayout->addWidget(menuBar);
	mainLayout->addWidget(vSplitter);
	
	//Actions
	screenshotAction = new QAction("Save Preview");
	QObject::connect(screenshotAction, &QAction::triggered, screenshotAction, [&](){canvasWidget->screenshot(getCWD() + "previews/", Context::width, Context::height);});
	
	//Shortcuts
	screenshotShortcut = new QShortcut(QKeySequence(Qt::Key_F12), canvasWidget);
	QObject::connect(screenshotShortcut, SIGNAL(activated()), screenshotAction, SLOT(trigger()));
}
