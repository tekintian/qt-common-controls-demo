#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QListWidget>
#include<QTreeWidget>
#include <QTreeWidgetItem>
#include<QTableWidget>
#include <QMovie>

#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置默认选中
    ui->btnMale->setChecked(true);

    // 连接信号和槽
    connect(ui->btnMale,&QRadioButton::clicked,[=](){
        qDebug()<<"你选择了  男 "<<endl;
    });


    connect(ui->btnFemale,&QRadioButton::clicked,[=](){
        qDebug()<< ui->btnFemale->text().toUtf8().data() << endl;
    });

    connect(ui->btnYh,&QRadioButton::clicked,[=](){
        qDebug()<< ui->btnYh->text().toUtf8().data() << endl;
    });

    connect(ui->btnWh,&QRadioButton::clicked,[=](){
        qDebug()<< ui->btnWh->text().toUtf8().data()  << endl;

    });


    // 列表控件
    // 添加Item到列表控件
    QListWidgetItem *item = new QListWidgetItem("你好");
    ui->listWidget->addItem(item);


    // 添加列表到列表控件
    QStringList list;
    list<< "床前明月光" << "疑是地上霜"<<"举头望明月"<<"低头思故乡";
    ui->listWidget->addItems(list);

    connect(ui->listWidget,&QListWidget::itemClicked,[=](QListWidgetItem *item){
       // qDebug()<< item->text().toUtf8().data() << endl;

        // 输出不带引号的字符
        qDebug("%s",item->text().toUtf8().data());

    });


    /** 树控件 treeWidget */
     // 设置控件的头信息
//    QStringList twlist;
//    list<<"名称"<<"名称介绍";
//    ui->treeWidgetCode->setHeaderLabels(twlist);// 不会覆盖原来的,需要先删除原来的label

    // 采用匿名函数形式增加
    ui->treeWidgetCode->setHeaderLabels(QStringList()<<"名称"<<"描述");

    //
    // 这里的参数使用的是匿名函数形式 QStringList()<<"德玛"<<"攻击"
    QTreeWidgetItem *twItem1 = new QTreeWidgetItem(QStringList()<<"德玛");
    ui->treeWidgetCode->addTopLevelItem(twItem1);
    // 传统模式添加参数
    QTreeWidgetItem *twChild1 = new QTreeWidgetItem(QStringList()<<"上单"<<"坦克, 功高防厚1!");
    twItem1->addChild(twChild1);

    // addChild第一个参数为指针类型,所以使用new;  QTreeWidgetItem参数为引用 & 类型,所以使用匿名对象模式  添加参数
    twItem1->addChild(new QTreeWidgetItem(QStringList()<<"上单"<<"坦克, 功高防厚2!"));

    // 动起来 注意型号参数
    connect(ui->treeWidgetCode, &QTreeWidget::itemClicked, [](QTreeWidgetItem *item, int column){
        qDebug() << item->text(column).toUtf8().data();
    });


    /** 表格控件 */
    ui->tableWidgetCode->setColumnCount(3); // 设置3列

    //设置水平表头信息  setHorizontalHeaderLabels设置水平表头信息  setHorizontalHeaderItem 设置水平表头控件
    ui->tableWidgetCode->setHorizontalHeaderLabels(QStringList()<<"英雄"<<"性别"<<"年龄");

    ui->tableWidgetCode->setRowCount(2); // 设置2行

    // 向表格中添加项目
    // void setItem(int row, int column, QTableWidgetItem *item)
    QStringList name;
    name<<"关羽"<<"张飞";
    QStringList sex;
    sex<<"男"<<"男";
    //循环设置值
    for (int i = 0; i < 2; ++i) {
        ui->tableWidgetCode->setItem(i,0, new QTableWidgetItem(name[i]));

        ui->tableWidgetCode->setItem(i,1, new QTableWidgetItem(sex[i]));

        //年龄设置    QString::number(i+20)  将数字转换为字符串
        ui->tableWidgetCode->setItem(i,2, new QTableWidgetItem( QString::number(i+20) ));
    }

    // 动起来   void itemClicked(QTableWidgetItem *item)
    connect(ui->tableWidgetCode,&QTableWidget::itemClicked, [](QTableWidgetItem *item){
        qDebug()<< item->text().toUtf8().data() ;
    });

    // 信号有参数 void cellClicked(int row, int column)  注意lambda表达式的参数需要与信号传递的参数保存一致
    connect(ui->tableWidgetUi, &QTableWidget::cellClicked, [](int row, int column){
        qDebug("row=%d, col=%d", row, column);
    });

    /** combo 下拉列表框控件 */
    // 使用匿名对象添加
    ui->comboBox->addItems(QStringList()<<"HTML"<<"CSS"<<"JS");

    // 添加带图标的项目
    ui->comboBox->addItem(QIcon(QPixmap(":/images/java0.jpg")),"JAVA");

    // 设置默认选项  void setCurrentIndex(int index)
    ui->comboBox->setCurrentIndex(3);

    // 动起来  void currentIndexChanged(int index)
    // 注意这里的信号有重载,不可直接使用,需要使用指针形式
    void (QComboBox:: *cbptr)(int) = &QComboBox::currentIndexChanged;

    connect(ui->comboBox, cbptr,[=](int index){
        qDebug("index = %d , value = %s ",index,ui->comboBox->currentText().toUtf8().data());
    });

    /** label 可显示文本图片,动画等 */
    ui->label->setText("Tekin");
    // 设置图片
    ui->label_pic->setPixmap(QPixmap(":/images/pc.png"));

    QMovie *movie = new QMovie(":/images/boating.gif");
    movie->setScaledSize(QSize(310,260));
    ui->label_movie->setMovie(movie);

    movie->start();//默认开始播放

    connect(ui->pushButton_paly,&QPushButton::clicked,[=](){
        movie->start();
    });

    connect(ui->pushButton_stop,&QPushButton::clicked, [=](){
        movie->stop();
    });



    //通过自定义控件的自定义外部接口获取自定义控件的进度条的值
    connect(ui->pushButton_getApi, &QPushButton::clicked,[=](){
        qDebug()<<"进度条的值:"<< ui->widget->myGetValue();

        QMessageBox::information(this,"自定义容器信息","进度条的值为:" + QString::number(ui->widget->myGetValue()) );

    });

    connect(ui->pushButton_setApi,&QPushButton::clicked,[=](){
        ui->widget->mySetValue(99); // 通过自定义控件的api设置进度条的值
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

