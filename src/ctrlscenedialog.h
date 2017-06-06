#ifndef CTRLSCENEDIALOG_H
#define CTRLSCENEDIALOG_H

#include <QDialog>

namespace Ui {
class CtrlSceneDialog;
}

class PEGraphicsScene;

class CtrlSceneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CtrlSceneDialog(QWidget *parent = 0);
    ~CtrlSceneDialog();

    static QIcon getColorIcon(const QColor &color, const QSize &size = QSize(24, 24));

public slots:
    void setScene(PEGraphicsScene *scene);

private slots:
    void on_horizontalSlider_penWidth_valueChanged(int value);

    void on_toolButton_penColor_clicked();

    void on_toolButton_brushColor_clicked();

    void on_comboBox_shape_currentIndexChanged(int index);

private:
    Ui::CtrlSceneDialog *ui;

    PEGraphicsScene *mScene;
};

#endif // CTRLSCENEDIALOG_H
