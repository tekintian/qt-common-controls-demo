#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include<QSlider>
#include<QSpinBox>

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);

    // spinbox的值改变,跟随改变进度条的值
    // 因为QSpinBox::valueChanged 这个信号有重载,所以这里必须使用指针, 指明我们要使用的是 void valueChanged(int i)
    void (QSpinBox::*sbptr)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox, sbptr,ui->horizontalSlider,&QSlider::setValue);

    // 进度条的值改变, 跟随改变spinbox的值; 这里的信号&QSlider::valueChanged 无重载,所以可以直接使用
    connect(ui->horizontalSlider,&QSlider::valueChanged,[=](int i){
        ui->spinBox->setValue(i);
    });

}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}
