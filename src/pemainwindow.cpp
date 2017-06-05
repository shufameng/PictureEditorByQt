#include "pemainwindow.h"
#include "ui_pemainwindow.h"

#include "pegraphicsscene.h"
#include "pegraphicsview.h"

#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

PEMainWindow::PEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PEMainWindow)
{
    ui->setupUi(this);

    mView = new PEGraphicsView(centralWidget());
    QHBoxLayout *hLay = new QHBoxLayout(centralWidget());
    hLay->addWidget(mView);
    mView->setScene(mScene = new PEGraphicsScene);
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


