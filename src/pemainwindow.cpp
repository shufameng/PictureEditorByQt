#include "pemainwindow.h"
#include "ui_pemainwindow.h"

#include "pegraphicsscene.h"
#include "pegraphicsview.h"
#include "ctrlscenedialog.h"

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

    // controller dialog
    mCtrlDialog = new CtrlSceneDialog;
    mCtrlDialog->setScene(mScene);
    QDockWidget *sceneCtrllerDock = new QDockWidget("Scene Contorller");
    sceneCtrllerDock->setWidget(mCtrlDialog);
    addDockWidget(Qt::LeftDockWidgetArea, sceneCtrllerDock);
    ui->menuView->addAction(sceneCtrllerDock->toggleViewAction());

    QDockWidget *viewCtrllerDock = new QDockWidget("View Controller");
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


