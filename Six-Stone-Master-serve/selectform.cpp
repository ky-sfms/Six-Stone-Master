﻿#include "selectform.h"
#include "ui_selectform.h"
#include<QDebug>
Selectform::Selectform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Selectform)
{
    ui->setupUi(this);
    ui->ButtonEasy->hide();
    ui->ButtonDiff->hide();
    ui->ButtonBack->hide();
    ui->ButtonAA->installEventFilter(this);  //在窗体上为ButtonAA安装过滤器
    ui->ButtonMA->installEventFilter(this);  //在窗体上为ButtonMA安装过滤器
    ui->ButtonMM->installEventFilter(this);  //在窗体上为ButtonMM安装过滤器
    ui->ButtonEasy->installEventFilter(this);  //在窗体上为ButtonEasy安装过滤器
    ui->ButtonDiff->installEventFilter(this);  //在窗体上为ButtonDiff安装过滤器
    ui->ButtonOn->installEventFilter(this);
    ui->ButtonBack->installEventFilter(this);
    connect(ui->ButtonAA,&QPushButton::clicked,this,&Selectform::ButtonAAclicked);
    connect(ui->ButtonMA,&QPushButton::clicked,this,&Selectform::ButtonMAclicked);
    connect(ui->ButtonMM,&QPushButton::clicked,this,&Selectform::ButtonMMclicked);
    connect(ui->ButtonDiff,&QPushButton::clicked,this,&Selectform::ButtonDiffclicked);
    connect(ui->ButtonEasy,&QPushButton::clicked,this,&Selectform::ButtonEasyclicked);
    connect(ui->ButtonOn,&QPushButton::clicked,this,&Selectform::ButtonOnclicked);

}
Selectform::~Selectform()
{
    delete ui;
}

bool Selectform::eventFilter(QObject *watched, QEvent *event)//对按钮进行美化设置，鼠标进入，字体放大，颜色变为白色，鼠标离开恢复
{
     if (watched==ui->ButtonAA)
     {
          if (event->type()==QEvent::Enter)     //然后再判断控件的具体事件 (这里指鼠标进入事件)
          {
            ui->ButtonAA->setStyleSheet("color:rgb(255,255,255);font: 45pt;");//鼠标进入，字体放大，颜色变为白色
          }
          else if (event->type()==QEvent::Leave)    // 这里指鼠标离开事件
          {
             ui->ButtonAA->setStyleSheet("color:rgb(255,255,0);font: 30pt;");//鼠标离开，字体缩小，颜色变为黄色
           }
     }
     if (watched==ui->ButtonMA)
     {
          if (event->type()==QEvent::Enter)
          {
            ui->ButtonMA->setStyleSheet("color:rgb(255,255,255);font: 45pt;");
            ui->ButtonEasy->show();
            ui->ButtonDiff->show();
            ui->ButtonBack->show();
          }
          else if (event->type()==QEvent::Leave)
          {
             ui->ButtonMA->setStyleSheet("color:rgb(255,255,0);font: 30pt;");
             ui->ButtonEasy->hide();
             ui->ButtonDiff->hide();
             ui->ButtonBack->hide();
           }
     }

     if (watched==ui->ButtonMM)
     {
          if (event->type()==QEvent::Enter)
          {
            ui->ButtonMM->setStyleSheet("color:rgb(255,255,255);font: 45pt;");
          }
          else if (event->type()==QEvent::Leave)
          {
             ui->ButtonMM->setStyleSheet("color:rgb(255,255,0);font: 30pt;");
           }
     }
     if (watched==ui->ButtonBack)
     {
          if (event->type()==QEvent::Enter)
          {
            ui->ButtonBack->setStyleSheet("color:rgb(255,255,255);font: 45pt;");
          }
          else if (event->type()==QEvent::Leave)
          {
             ui->ButtonBack->setStyleSheet("color:rgb(255,255,0);font: 30pt;");
           }
     }
     if (watched==ui->ButtonEasy)
     {
          if (event->type()==QEvent::Enter)
          {
            ui->ButtonEasy->setStyleSheet("color:rgb(255,255,255);font: 45pt;");
          }
          else if (event->type()==QEvent::Leave)
          {
             ui->ButtonEasy->setStyleSheet("color:rgb(255,255,0);font: 30pt;");
           }
     }
     if (watched==ui->ButtonDiff)
     {
          if (event->type()==QEvent::Enter)
          {
            ui->ButtonDiff->setStyleSheet("color:rgb(255,255,255);font: 45pt;");
          }
          else if (event->type()==QEvent::Leave)
          {
             ui->ButtonDiff->setStyleSheet("color:rgb(255,255,0);font: 30pt;");
           }
     }
     if (watched==ui->ButtonOn)
     {
          if (event->type()==QEvent::Enter)
          {
            ui->ButtonOn->setStyleSheet("color:rgb(255,255,255);font: 45pt;");
          }
          else if (event->type()==QEvent::Leave)
          {
             ui->ButtonOn->setStyleSheet("color:rgb(255,255,0);font: 30pt;");
           }
     }
 return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
}

void Selectform::ButtonMMclicked()
{
    emit sendmes(MM,none);
    this->close();
}
void Selectform::ButtonMAclicked()
{
    ui->ButtonMM->hide();
    ui->ButtonAA->hide();
    ui->ButtonMA->hide();
    ui->ButtonOn->hide();
    ui->ButtonEasy->show();
    ui->ButtonDiff->show();
}

void Selectform::ButtonAAclicked()
{
    emit sendmes(AA,none);
    this->close();
}

void Selectform::ButtonEasyclicked()
{
        emit sendmes(MA,easy);
        this->close();
}

void Selectform::ButtonDiffclicked()
{
    emit sendmes(MA,diff);
    this->close();
}

void Selectform::ButtonOnclicked()
{
    this->close();
    emit online();
}

void Selectform::on_ButtonBack_clicked()
{
    ui->ButtonEasy->hide();
    ui->ButtonDiff->hide();
    ui->ButtonBack->hide();
    ui->ButtonMM->show();
    ui->ButtonAA->show();
    ui->ButtonMA->show();
    ui->ButtonOn->show();
}
