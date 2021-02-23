# qt-common-controls-demo
qt常用控件演示项目, JUST FOR LEARNING QT!



##QT 帮助文档查看方法

![](./docs/help1.png)

建议直接使用软件自带的帮助文档, 查找帮助文档的时候直接使用英文 搜索

找到相应的类后 先看  Contents 中的索引:

找方法: 依次查看 Public Functions, Public Slots, Protected Functions ,  Reimplemented Protected Functions ;  如果这些里面都没有找到, 可以到类的继承类中去查找,  查看继承类的方法直接点击 左侧的  Inherits: 后面的类名称即可





## 信号或者槽函数有重载的时候 需要使用指针

![](./docs/pointer_overload.png)

~~~cpp
 // spinbox的值改变,跟随改变进度条的值
    // 因为QSpinBox::valueChanged 这个信号有重载,所以这里必须使用指针, 指明我们要使用的是 void valueChanged(int i)
    void (QSpinBox::*sbptr)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox, sbptr,ui->horizontalSlider,&QSlider::setValue);

    // 进度条的值改变, 跟随改变spinbox的值; 这里的信号&QSlider::valueChanged 无重载,所以可以直接使用
    connect(ui->horizontalSlider,&QSlider::valueChanged,[=](int i){
        ui->spinBox->setValue(i);
    });

~~~

ps: connect 可使用常规模式,或者使用ladbda模式, 推荐使用lambda模式,

使用时 需要注意信号的形参



自定义控件 使用

1.   add new  --> QT-->设计师界面类;

2. 界面模板这里一般选择Widget :  注意这里的类型需要与你在容器中提升时的类型保存一致.

3. 新建完成后可双击 新建的.ui文件 对自定义控件进行编辑

4. 在其他界面中使用自定义控件:  先添加一个container的widget容器; 然后选择容器后  右键 -->提升到, 打开自定义控件提升页面, 录入自定义类名称,选择全局后,点击添加, 然后选择添加的类, 最后点击提升即可

   ![](./docs/diy_container.png)



### 自定义控件提供外部API接口

- mywidget.h

  ~~~mywidget.h
  public:
      explicit MyWidget(QWidget *parent = nullptr);
      ~MyWidget();
  //  自定义控件外部接口定义
      void mySetValue(int value);
      int myGetValue(void);
  
  
  ~~~

- mywidget.cpp


  ~~~mywidget.cpp
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
  
  ~~~



- mainwindow.cpp

~~~mainwindow.cpp

    //通过自定义控件的自定义外部接口获取自定义控件的进度条的值
    connect(ui->pushButton_getApi, &QPushButton::clicked,[=](){
        qDebug()<<"进度条的值:"<< ui->widget->myGetValue();
    });

    connect(ui->pushButton_setApi,&QPushButton::clicked,[=](){
        ui->widget->mySetValue(99); // 通过自定义控件的api设置进度条的值
    });

~~~



















