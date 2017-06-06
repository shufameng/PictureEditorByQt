#ifndef CTRLVIEWDIALOG_H
#define CTRLVIEWDIALOG_H

#include <QDialog>

class PEGraphicsView;

namespace Ui {
class CtrlViewDialog;
}

class CtrlViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CtrlViewDialog(QWidget *parent = 0);
    ~CtrlViewDialog();

public slots:
    void setView(PEGraphicsView *view);

private slots:
    void on_toolButton_showFitViewSize_clicked();

    void on_toolButton_showOriginalSize_clicked();

    void on_toolButton_zoomIn_clicked();

    void on_toolButton_zoomOut_clicked();

    void on_toolButton_rotate90clockWise_clicked();

    void on_toolButton_rotate90antiClockWise_clicked();

    void on_toolButton_rotate180_clicked();

private:
    Ui::CtrlViewDialog *ui;

    PEGraphicsView *mView;
};

#endif // CTRLVIEWDIALOG_H
