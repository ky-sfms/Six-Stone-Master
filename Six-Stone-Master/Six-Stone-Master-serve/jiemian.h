﻿#ifndef JIEMIAN_H
#define JIEMIAN_H
#include<QMessageBox>
#include<QString>
#include<QWidget>
#include<QPainter>
#include<QKeyEvent>
#include<math.h>
#include<gamemodel.h>
#include<QMediaPlayer>
#include <QtGlobal>
#include<QTime>
#include<QTimer>
#include<QEventLoop>
struct maxscore
{
    int x=-1;
    int y=-1;
    int score=-1;
    maxscore() {}
};

class Jiemian : public QWidget
{
    Q_OBJECT

    bool isselected=0;
    int x=-1.0;
    int y=-1.0;
    int clickx=-1;
    int clicky=-1;
public:
    QMediaPlayer *Sound_effect;
    Gamemodel * game;
    explicit Jiemian(QWidget *parent = nullptr);
    maxscore maxblack();
    maxscore maxwhite();
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void AABattle();
    void waitsec(int sec);
    void GameOver();
    void changeto(char *);
    char *changefrom();
    ~Jiemian();
signals:

public slots:

};

#endif // JIEMIAN_H
