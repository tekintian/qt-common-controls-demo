#include "mywidget.h"
#include "ui_mywidget.h"
#include<QSpinBox>
#include<QSlider>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
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

MyWidget::~MyWidget()
{
    delete ui;
}

//MyWidget外部接口实现
void MyWidget::mySetValue(int value)
{
    // 设置进度条slider的值
    ui->horizontalSlider->setValue(value);
}

int MyWidget::myGetValue(void)
{
    // 获取进度条的值
    return ui->horizontalSlider->value();
}
