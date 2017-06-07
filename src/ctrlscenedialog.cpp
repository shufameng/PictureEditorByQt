#include "ctrlscenedialog.h"
#include "ui_ctrlscenedialog.h"
#include "pegraphicsscene.h"
#include <QColorDialog>

CtrlSceneDialog::CtrlSceneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CtrlSceneDialog),
    mScene(NULL)
{
    ui->setupUi(this);
    setWindowTitle("View Controller");
}

CtrlSceneDialog::~CtrlSceneDialog()
{
    delete ui;
}

QIcon CtrlSceneDialog::getColorIcon(const QColor &color, const QSize &size)
{
    QPixmap pixmap(size);
    pixmap.fill(color);
    QIcon icon;
    icon.addPixmap(pixmap);

    return icon;
}

void CtrlSceneDialog::setScene(PEGraphicsScene *scene)
{
    mScene = scene;

    if (mScene) {
        // pen width
        ui->horizontalSlider_penWidth->setValue(mScene->pen().width());
        ui->label_penWidth->setText(QString::number(mScene->pen().width()));
        // pen color
        ui->toolButton_penColor->setIcon(getColorIcon(mScene->pen().color()));
        // brush color
        ui->toolButton_brushColor->setIcon(getColorIcon(mScene->brush().color()));
        // shape
        ui->comboBox_shape->setCurrentIndex((int)mScene->toolShape());
    }
}

void CtrlSceneDialog::on_horizontalSlider_penWidth_valueChanged(int value)
{
    if (mScene) {
        mScene->setPenWidth(value);
        ui->label_penWidth->setText(QString::number(value));
    }
}

void CtrlSceneDialog::on_toolButton_penColor_clicked()
{
    if (mScene) {
        QColor color = QColorDialog::getColor(mScene->pen().color(), this);
        mScene->setPenColor(color);
        ui->toolButton_penColor->setIcon(getColorIcon(color));
    }
}

void CtrlSceneDialog::on_toolButton_brushColor_clicked()
{
    if (mScene) {
        QColor color = QColorDialog::getColor(mScene->brush().color(), this);
        mScene->setBrushColor(color);
        ui->toolButton_brushColor->setIcon(getColorIcon(color));
    }
}

void CtrlSceneDialog::on_comboBox_shape_currentIndexChanged(int index)
{
    if (mScene) {
        mScene->setToolShape((PEGraphicsScene:: ToolShape)index);
    }
}
