# QNetworkAccessManager

widget.cpp

~~~cpp
#include "widget.h"
#include "ui_widget.h"
#include <QNetworkReply>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    netManager =  new QNetworkAccessManager(this);
    netReply = nullptr;
    mDataBuffer = new QByteArray();

    //Define net request5
    QNetworkRequest request;
    request.setUrl(QUrl("https://www.qt.io"));

    netReply = netManager->get(request);
    connect(netReply,&QIODevice::readyRead,this,&Widget::dataReadyToRead);
    connect(netReply,&QNetworkReply::finished,this,&Widget::dataReadFinished);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::dataReadyToRead()
{
    qDebug()<< "Some data available";
    mDataBuffer->append(netReply->readAll());
}

void Widget::dataReadFinished()
{
    if( netReply->error())
    {
        qDebug() << " Error : " << QString(*mDataBuffer) ;
    }else
    {
        ui->textEdit->setPlainText(QString(*mDataBuffer));
    }

}


~~~



widget.h

~~~cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void dataReadyToRead();
    void dataReadFinished();

private:
    Ui::Widget *ui;

    QNetworkAccessManager * netManager;
    QNetworkReply * netReply;
    QByteArray * mDataBuffer;
};

#endif // WIDGET_H

~~~

