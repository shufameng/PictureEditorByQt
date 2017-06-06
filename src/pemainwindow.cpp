#include "pemainwindow.h"
#include "ui_pemainwindow.h"

#include "pegraphicsscene.h"
#include "pegraphicsview.h"
#include "ctrlscenedialog.h"
#include "ctrlviewdialog.h"

#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDockWidget>
#include <QDebug>

PEMainWindow::PEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PEMainWindow)
{
    ui->setupUi(this);

    // view and scene
    mView = new PEGraphicsView(centralWidget());
    QHBoxLayout *hLay = new QHBoxLayout(centralWidget());
    hLay->addWidget(mView);
    mView->setScene(mScene = new PEGraphicsScene);

    // scene controller
    mCtrlSceneDialog = new CtrlSceneDialog;
    mCtrlSceneDialog->setScene(mScene);
    QDockWidget *sceneCtrllerDock = new QDockWidget("Scene Contorller");
    sceneCtrllerDock->setWidget(mCtrlSceneDialog);
    addDockWidget(Qt::LeftDockWidgetArea, sceneCtrllerDock);
    ui->menuView->addAction(sceneCtrllerDock->toggleViewAction());

    // view controller
    mCtrlViewDialog = new CtrlViewDialog;
    mCtrlViewDialog->setView(mView);
    QDockWidget *viewCtrllerDock = new QDockWidget("View Controller");
    viewCtrllerDock->setWidget(mCtrlViewDialog);
    addDockWidget(Qt::LeftDockWidgetArea, viewCtrllerDock);
    ui->menuView->addAction(viewCtrllerDock->toggleViewAction());
}

PEMainWindow::~PEMainWindow()
{
    delete ui;
}

void PEMainWindow::on_action_open_file_triggered()
{
    QString filePath = QFileDialog::getOpenFileName();
    if (filePath.isEmpty())
        return;

    if (!mScene->openFile(filePath))
        QMessageBox::warning(this, "Warning", "Open file failed", QMessageBox::Yes);
}


