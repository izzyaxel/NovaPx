#pragma once

#include "../widgets/mainWindowWidget.hh"
#include "../widgets/glWidget.hh"
#include "../widgets/pickColorButton.hh"
#include "../widgets/brushToolButton.hh"
#include "../widgets/eraserToolButton.hh"
#include "../widgets/eyedropperToolButton.hh"
#include "../widgets/fillToolButton.hh"

#include <QtWidgets/QShortcut>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QLabel>

void setupGUI();

extern QVBoxLayout *mainLayout, *toolbarLayout, *canvasLayout;
extern QHBoxLayout *leftBarLayout, *infoBarLayout;
extern QSplitter *vSplitter, *hSplitter, *layersSplitter;
extern QLabel *magLabel, *currentToolLabel;

extern QWidget *center, *timelineContainer, *leftBarContainer, *rightBarContainer, *canvasContainer, *infoBarContainer, *vDiv, *hDiv;
extern MainWindowWidget *mainWindowWidget;
extern GLWidget *canvasWidget;
extern PickColorButton *pickColorButton;
extern BrushToolButton *brushToolButton;
extern EraserToolButton *eraserToolButton;
extern EyedropperToolButton *eyedropperToolButton;
extern FillToolButton *fillToolButton;

extern QMenuBar *menuBar;
extern QMenu *fileMenu;
extern QMenu *editMenu;
extern QMenu *helpMenu;

extern QAction *screenshotAction, *changeToBrushAction, *changeToEraserAction;
extern QShortcut *screenshotShortcut;
