﻿#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "gamemodel.h"
#include<QMessageBox>
#include<QString>
#include<QWidget>
#include<QPainter>
#include<QKeyEvent>
#include<math.h>
#include<QTime>
#include<QMediaPlayer>
namespace Ui {
class Chessboard;
}

class Chessboard : public QWidget
{
    Q_OBJECT
public:
    bool isselected=0;
    int x=-1.0;
    int y=-1.0;
    int clickx=-1;
    int clicky=-1;
    Gamemodel *game;

    explicit Chessboard(QWidget *parent = 0,Gamemodel *game=0);
    ~Chessboard();
    QMediaPlayer *Sound_effect;
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void startgame();
private slots:
    void on_btback_clicked();
    void on_btgvup_clicked();

    void on_btsend_clicked();

    void on_lineEdit_returnPressed();

signals:
    void mouseRelease();
    void sendmesschat(QString);
    void sendback();
    void sendgiveup();
public slots:
    void receivemeschat(QString);
private:
    Ui::Chessboard *ui;
};

#endif // CHESSBOARD_H
