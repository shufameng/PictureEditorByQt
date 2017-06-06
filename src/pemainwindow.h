#ifndef PEMAINWINDOW_H
#define PEMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

namespace Ui {
class PEMainWindow;
}

class PEGraphicsScene;
class PEGraphicsView;
class CtrlSceneDialog;
class CtrlViewDialog;

class PEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PEMainWindow(QWidget *parent = 0);
    ~PEMainWindow();

private slots:
    void on_action_open_file_triggered();

private:
    Ui::PEMainWindow *ui;

    PEGraphicsScene     *mScene;
    PEGraphicsView      *mView;

    CtrlSceneDialog           *mCtrlSceneDialog;
    CtrlViewDialog              *mCtrlViewDialog;
};

#endif // PEMAINWINDOW_H
