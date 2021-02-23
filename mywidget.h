#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
//  自定义控件外部接口定义
    void mySetValue(int value);
    int myGetValue(void);


private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
