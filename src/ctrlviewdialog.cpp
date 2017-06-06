#include "ctrlviewdialog.h"
#include "ui_ctrlviewdialog.h"
#include "pegraphicsview.h"

CtrlViewDialog::CtrlViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CtrlViewDialog)
{
    ui->setupUi(this);
}

CtrlViewDialog::~CtrlViewDialog()
{
    delete ui;
}

void CtrlViewDialog::setView(PEGraphicsView *view)
{
    mView = view;
}

void CtrlViewDialog::on_toolButton_showFitViewSize_clicked()
{
    if (mView)
        mView->showFitViewSize();
}

void CtrlViewDialog::on_toolButton_showOriginalSize_clicked()
{
    if (mView)
        mView->showOriginalSize();
}

void CtrlViewDialog::on_toolButton_zoomIn_clicked()
{
    if (mView)
        mView->zoomIn();
}

void CtrlViewDialog::on_toolButton_zoomOut_clicked()
{
    if (mView)
        mView->zoomOut();
}

void CtrlViewDialog::on_toolButton_rotate90clockWise_clicked()
{
    if (mView)
        mView->rotate90Clockwise();
}

void CtrlViewDialog::on_toolButton_rotate90antiClockWise_clicked()
{
    if (mView)
        mView->rotate90AntiClockwise();
}

void CtrlViewDialog::on_toolButton_rotate180_clicked()
{
    if (mView)
        mView->rotate180();
}
