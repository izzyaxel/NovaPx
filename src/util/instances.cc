#include "instances.hh"
#include "globals.hh"
#include "util.hh"

QVBoxLayout *mainLayout = nullptr, *toolbarLayout = nullptr, *canvasLayout = nullptr;
QHBoxLayout *leftBarLayout = nullptr, *infoBarLayout = nullptr;
QSplitter *vSplitter = nullptr, *hSplitter = nullptr, *layersSplitter = nullptr;
QLabel *magLabel = nullptr, *currentToolLabel = nullptr;

QWidget *center = nullptr, *timelineContainer = nullptr, *leftBarContainer = nullptr, *rightBarContainer = nullptr, *toolbarContainer = nullptr, *canvasContainer = nullptr, *infoBarContainer = nullptr, *vDiv = nullptr, *hDiv = nullptr;
MainWindowWidget *mainWindowWidget = nullptr;
GLWidget *canvasWidget = nullptr;
PickColorButton *pickColorButton = nullptr;
BrushToolButton *brushToolButton = nullptr;
EraserToolButton *eraserToolButton = nullptr;
EyedropperToolButton *eyedropperToolButton = nullptr;
FillToolButton *fillToolButton = nullptr;

QMenuBar *menuBar = nullptr;
QMenu *fileMenu = nullptr;
QMenu *editMenu = nullptr;
QMenu *helpMenu = nullptr;

QAction *screenshotAction = nullptr, *changeToBrushAction = nullptr, *changeToEraserAction = nullptr;
QShortcut *screenshotShortcut = nullptr;

uint32_t buttonWidth = 40;

void setupGUI()
{
	vDiv = new QWidget;
	vDiv->setMinimumSize(2, 2);
	vDiv->setFixedWidth(2);
	vDiv->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
	vDiv->setStyleSheet(R"(
QWidget
{
	background-color: rgb(120, 120, 120);
})");
	
	hDiv = new QWidget;
	hDiv->setMinimumSize(2, 2);
	hDiv->setFixedWidth(2);
	hDiv->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
	hDiv->setStyleSheet(R"(
QWidget
{
	background-color: rgb(120, 120, 120);
})");
	
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
	
	toolbarContainer = new QWidget(leftBarContainer);
	toolbarContainer->setFixedWidth(50);
	toolbarContainer->setMinimumSize(50, 50);
	toolbarContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
	toolbarContainer->setStyleSheet(R"(
QWidget
{
	border: 1px solid rgb(100, 100, 100);
	background-color: rgb(30, 30, 30);
})");
	
	leftBarLayout = new QHBoxLayout(leftBarContainer);
	leftBarLayout->setContentsMargins(0, 0, 0, 0);
	leftBarContainer->setLayout(leftBarLayout);
	
	toolbarLayout = new QVBoxLayout(toolbarContainer);
	toolbarLayout->setContentsMargins(5, 5, 5, 5);
	
	rightBarContainer = new QWidget(hSplitter);
	rightBarContainer->setMinimumSize(100, 100);
	rightBarContainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	rightBarContainer->setStyleSheet(R"(
QWidget
{
	background-color: rgb(30, 30, 30);
})");
	
	pickColorButton = new PickColorButton(toolbarContainer);
	pickColorButton->setFixedSize(buttonWidth, buttonWidth);
	pickColorButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	
	brushToolButton = new BrushToolButton("B", toolbarContainer);
	brushToolButton->setFixedSize(buttonWidth, buttonWidth);
	brushToolButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	brushToolButton->setStyleSheet(R"(
QPushButton
{
	background-color: rgb(60, 60, 60);
	color: white;
})");
	
	eraserToolButton = new EraserToolButton("E", toolbarContainer);
	eraserToolButton->setFixedSize(buttonWidth, buttonWidth);
	eraserToolButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	eraserToolButton->setStyleSheet(R"(
QPushButton
{
	background-color: rgb(60, 60, 60);
	color: white;
})");
	
	eyedropperToolButton = new EyedropperToolButton("P", toolbarContainer);
	eyedropperToolButton->setFixedSize(buttonWidth, buttonWidth);
	eyedropperToolButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	eyedropperToolButton->setStyleSheet(R"(
QPushButton
{
	background-color: rgb(60, 60, 60);
	color: white;
})");
	
	fillToolButton = new FillToolButton("F", toolbarContainer);
	fillToolButton->setFixedSize(buttonWidth, buttonWidth);
	fillToolButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	fillToolButton->setStyleSheet(R"(
QPushButton
{
	background-color: rgb(60, 60, 60);
	color: white;
})");
	
	layersSplitter = new QSplitter(leftBarContainer);
	layersSplitter->setContentsMargins(0, 0, 0, 0);
	layersSplitter->setMinimumSize(0, 100);
	layersSplitter->setOrientation(Qt::Vertical);
	layersSplitter->setStyleSheet(R"(
QSplitter::handle
{
	background-color: rgb(120, 120, 120);
	border: 1px solid rgb(40, 40, 40);
})");
	
	canvasContainer = new QWidget(hSplitter);
	
	canvasLayout = new QVBoxLayout(canvasContainer);
	canvasLayout->setContentsMargins(0, 0, 0, 0);
	
	infoBarContainer = new QWidget(canvasContainer);
	infoBarContainer->setMinimumSize(20, 100);
	infoBarContainer->setFixedHeight(20);
	infoBarContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
	
	magLabel = new QLabel("", infoBarContainer);
	magLabel->setAlignment(Qt::AlignCenter);
	magLabel->setMinimumHeight(14);
	magLabel->setContentsMargins(0,0,0,6);
	magLabel->setStyleSheet(R"(
QLabel
{
	background-color: transparent;
	color: white;
})");
	
	currentToolLabel = new QLabel("Brush", infoBarContainer);
	currentToolLabel->setAlignment(Qt::AlignCenter);
	currentToolLabel->setMinimumHeight(14);
	currentToolLabel->setContentsMargins(0,0,0,6);
	currentToolLabel->setStyleSheet(R"(
QLabel
{
	background-color: transparent;
	color: white;
})");
	
	infoBarLayout = new QHBoxLayout(infoBarContainer);
	infoBarLayout->setContentsMargins(6, 0, 6, 0);
	
	infoBarLayout->addWidget(magLabel);
	infoBarLayout->addWidget(vDiv);
	infoBarLayout->addWidget(currentToolLabel);
	
	canvasLayout->addWidget(canvasWidget);
	canvasLayout->addWidget(infoBarContainer);
	
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
	hSplitter->addWidget(canvasContainer);
	hSplitter->addWidget(rightBarContainer);
	hSplitter->setStretchFactor(0, 6);
	hSplitter->setStretchFactor(1, 10);
	hSplitter->setStretchFactor(2, 3);
	
	vSplitter->addWidget(hSplitter);
	vSplitter->addWidget(timelineContainer);
	vSplitter->setStretchFactor(0, 5);
	vSplitter->setStretchFactor(1, 2);
	
	QWidget *expandingSpacer = new QWidget(toolbarContainer);
	expandingSpacer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
	
	toolbarLayout->addWidget(brushToolButton);
	toolbarLayout->addWidget(eraserToolButton);
	toolbarLayout->addWidget(eyedropperToolButton);
	toolbarLayout->addWidget(fillToolButton);
	toolbarLayout->addWidget(pickColorButton);
	toolbarLayout->addWidget(expandingSpacer);
	toolbarContainer->setLayout(toolbarLayout);
	
	leftBarLayout->addWidget(layersSplitter);
	leftBarLayout->addWidget(toolbarContainer);
	
	mainLayout->addWidget(menuBar);
	mainLayout->addWidget(vSplitter);
	
	//Actions
	screenshotAction = new QAction("Save Preview");
	QObject::connect(screenshotAction, &QAction::triggered, screenshotAction, [&](){canvasWidget->screenshot(getCWD() + "previews/", Context::width, Context::height);});
	
	//Shortcuts
	screenshotShortcut = new QShortcut(QKeySequence(Qt::Key_F12), canvasWidget);
	QObject::connect(screenshotShortcut, SIGNAL(activated()), screenshotAction, SLOT(trigger()));
}
