﻿#include "jiemian.h"
#include<QDebug>
Jiemian::Jiemian(QWidget *parent) : QWidget(parent)
{
    game=new Gamemodel;
    setMouseTracking(true);//开启鼠标监听
    Sound_effect = new QMediaPlayer;
    Sound_effect->setMedia(QUrl("qrc:/new/background/reso/down.wav"));
    Sound_effect->setVolume(200);
}


void Jiemian::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor("black")));
    painter.setRenderHint(QPainter:: Antialiasing, true);  //设置渲染,启动反锯齿
    painter.setBrush(QColor(230,255,255));
    painter.drawRect(margin-2*r,margin-2*r,one*20+4*r,one*20+4*r);//画轮廓

    for(int i=0;i<rowline;i++){
        painter.drawLine(margin,margin+i*one,margin+20*one,margin+i*one);
    }
    for(int i=0;i<columnline;i++){
        painter.drawLine(margin+i*one,margin,margin+i*one,margin+20*one);
    }//画棋牌
/*    painter.setPen(QPen(QColor("green")));
    painter.setFont(QFont("微软雅黑",10,700,false));
    for(int i=0;i<rowline;i++){
        for(int j=0;j<columnline;j++){
            painter.drawText(QPoint(margin+one*i,margin+one*j),QString::number(game->black_score[i][j]));
        }
    }
    painter.setPen(QPen(QColor("blue")));
    painter.setFont(QFont("微软雅黑",10,700,false));
    for(int i=0;i<rowline;i++){
        for(int j=0;j<columnline;j++){
            painter.drawText(QPoint(margin+one*i,margin+one*j-10),QString::number(game->white_score[i][j]));
        }
    }*///绘制分数（调试时用）
    painter.setPen(QPen(QColor("blue")));
    if(isselected){
        if(game->Gameflags){
            painter.setBrush(QColor("black"));
        }else{
            painter.setBrush(QColor("white"));
        }
        QPoint ing(clickx*one+margin,clicky*one+margin);
        painter.drawEllipse(ing,r,r);
    }//鼠标监听
    for(int i=0;i<columnline;i++)//行
    {
        for(int j=0;j<rowline;j++)//添加21列
        {
            switch (game->game_progress[i][j]) {
            case iswhite:
                painter.setBrush(QColor("white"));
                break;
            case isblack:
                painter.setBrush(QColor("black"));
                break;
            default:
                continue;
            }
            QPoint qizi(i*one+margin,j*one+margin);
            painter.drawEllipse(qizi,r,r);
        }
    }//画棋子
    if(game->state==win){
        painter.setPen(QPen(QBrush(QColor("red")),8));
        switch (game->derect) {
         case 0:
            painter.drawLine(game->winx*one+margin,game->winy*one+margin,game->winx*one+margin,(game->winy-5)*one+margin);
            break;
        case 3:
            painter.drawLine(game->winx*one+margin,game->winy*one+margin,(game->winx-5)*one+margin,(game->winy+5)*one+margin);
            break;
        case 2:
            painter.drawLine(game->winx*one+margin,game->winy*one+margin,(game->winx-5)*one+margin,game->winy*one+margin);
            break;
        case 1:
            painter.drawLine(game->winx*one+margin,game->winy*one+margin,(game->winx-5)*one+margin,(game->winy-5)*one+margin);
            break;
        default:
            break;
        }
    }//游戏赢了画红线

}

void Jiemian::mouseMoveEvent(QMouseEvent *event)
{
    if(game->state!=playing) GameOver();
    if(game->type==AA){ if(game->isAA){}else {game->isAA=1;AABattle();} return;}
    if(game->type==MA&&!game->Gameflags) return;//AI下棋时不监听
    x=event->x();
    y=event->y();
    isselected=0;
    int minx;
    int miny;
    if((x-margin)%one>one-((x-margin)%one)){
        minx= ((x-margin)%one)-one;
    }else{
        minx=(x-margin)%one>one;
    }
    if((y-margin)%one>one-((y-margin)%one)){
        miny= ((y-margin)%one)-one;
    }else{
        miny=(y-margin)%one;
    }
    if(minx*minx+miny*miny<r*r){
        clickx=(x-margin-minx)/one;
        clicky=(y-margin-miny)/one;
    if(clickx<0||clicky<0||clickx>20||clicky>20) return;//防止程序异常
        if(game->game_progress[clickx][clicky]==isempty){
                isselected=1;
        }
    }


}

void Jiemian::mouseReleaseEvent(QMouseEvent *)
{
    if(game->state!=playing) GameOver();
    if(game->type==AA) return;//AA模式
    if(isselected){
        if(game->type==MA)
        {
            game->game_progress[clickx][clicky]=(what)game->Gameflags;
            game->state=game->GameEnd(clickx,clicky);
            Sound_effect->play();//播放落子音效
            if(game->state==win) return;
            update();
            if(game->Gameflags) {
                game->black_score[clickx][clicky]=-2000;
                game->white_score[clickx][clicky]=-2000;
                if(game->AItype==easy)     game->calculatBlack(clickx,clicky);
                else                       game->calculatBlackUp(clickx,clicky);

            }
            if(game->state==win) GameOver();
            game->Gameflags=!game->Gameflags;//换手
            waitsec(1000);
            maxscore maxBlack;maxBlack=maxblack();
            maxscore maxWhite;maxWhite=maxwhite();
            if(maxBlack.score>maxWhite.score){
                game->game_progress[maxBlack.x][maxBlack.y]=(what)game->Gameflags;
                game->state=game->GameEnd(maxBlack.x,maxBlack.y);
                if(game->AItype==easy)     game->calculatWhite(clickx,clicky);
                if(game->AItype==diff)     game->calculatWhiteUp(clickx,clicky);
                game->black_score[maxBlack.x][maxBlack.y]=-2000;
                game->white_score[maxBlack.x][maxBlack.y]=-2000;
            }else{
                game->game_progress[maxWhite.x][maxWhite.y]=(what)game->Gameflags;
                game->state=game->GameEnd(maxWhite.x,maxWhite.y);
                if(game->AItype==easy)     game->calculatWhite(clickx,clicky);
                if(game->AItype==diff)     game->calculatWhiteUp(clickx,clicky);
                game->black_score[maxWhite.x][maxWhite.y]=-2000;
                game->white_score[maxWhite.x][maxWhite.y]=-2000;
            }
            game->Gameflags=!game->Gameflags;//换手
        }

        //MA模式
        else{
            game->game_progress[clickx][clicky]=(what)game->Gameflags;
            game->state=game->GameEnd(clickx,clicky);
            game->Gameflags=!game->Gameflags;//换手
        }//MM模式

        Sound_effect->play();//播放落子音效
//        if(game->state==win){
//        }
        update();//重绘界面
    }//落点存储
}

Jiemian::~Jiemian(){
    delete game;
}

maxscore Jiemian::maxblack()
{
    maxscore scoremax;
    for(int i=0;i<columnline;i++)
    {
        for(int j=0;j<rowline;j++)
        {
            if(game->black_score[i][j]>scoremax.score){
                scoremax.score=game->black_score[i][j];
                scoremax.x=i;scoremax.y=j;
            }
        }
    }
    return scoremax;
}
void Jiemian::AABattle()
{
    int n=5;
    while(n--)
    {
        QTime time= QTime::currentTime();
        qsrand(time.msec()+time.second()*3000);  //设置随机种子
        int fx =qrand()%3+10;int fy =qrand()%3+10;
        if(game->game_progress[fx][fy]!=isempty){n++;continue;}
        game->game_progress[fx][fy]=(what)game->Gameflags;
        game->black_score[fx][fy]=-1000;
        game->white_score[fx][fy]=-1000;
        if(game->Gameflags)
        game->calculatBlack(fx,fy);
        else
        game->calculatWhite(fx,fy);
        Sound_effect->play();//播放落子音效
        game->Gameflags=!game->Gameflags;//换手
        update();//重绘界面
        waitsec(200);
    }
    while(game->state==playing)
    {
        maxscore maxBlack=maxblack();
        maxscore maxWhite=maxwhite();
        if(maxBlack.score>maxWhite.score){
            game->game_progress[maxBlack.x][maxBlack.y]=(what)game->Gameflags;
            game->state=game->GameEnd(maxBlack.x,maxBlack.y);
            game->black_score[maxBlack.x][maxBlack.y]=-2000;
            game->white_score[maxBlack.x][maxBlack.y]=-2000;
            if(game->Gameflags)
            game->calculatBlack(maxBlack.x,maxBlack.y);
            else
            game->calculatWhite(maxBlack.x,maxBlack.y);
        }else{
            game->game_progress[maxWhite.x][maxWhite.y]=(what)game->Gameflags;
            game->state=game->GameEnd(maxWhite.x,maxWhite.y);
            game->black_score[maxWhite.x][maxWhite.y]=-2000;
            game->white_score[maxWhite.x][maxWhite.y]=-2000;
            if(game->Gameflags)
            game->calculatBlack(maxWhite.x,maxWhite.y);
            else
            game->calculatWhite(maxWhite.x,maxWhite.y);
        }
        game->Gameflags=!game->Gameflags;//换手
        Sound_effect->play();//播放落子音效
        update();//重绘界面
        waitsec(200);
    }

}



void Jiemian::waitsec(int sec)
{
    QEventLoop eventloop;//创建一个事件循环
    QTimer::singleShot(sec, &eventloop, SLOT(quit())); //计时1s
    eventloop.exec();//启动一个事件循环
}



maxscore Jiemian::maxwhite()
{
    maxscore scoremax;
    for(int i=0;i<columnline;i++)
    {
        for(int j=0;j<rowline;j++)
        {
            if(game->white_score[i][j]>scoremax.score){
                scoremax.score=game->white_score[i][j];
                scoremax.x=i;scoremax.y=j;
            }
        }
    }
    return scoremax;
}
void Jiemian::GameOver()
{
    QMessageBox:: StandardButton result=game->gameOver();
    if(result==QMessageBox::Yes)
    {
        Gametype x=game->type;
        delete game;
        game=new Gamemodel;
        game->type=x;
     }
   else{
       exit(0);
    }

}

void Jiemian::changeto(char *towhat)
{
    for(int i=0;i<rowline;i++){
        for(int j=0;j<columnline;j++){
            int k=(int)towhat[i*j+j];
            game->game_progress[i].push_back((what)k);
        }
    }
}

char* Jiemian::changefrom()
{
    char buffer[1024];
    for(int i=0;i<rowline;i++){
        for(int j=0;j<columnline;j++){
            int k=(int)game->game_progress[i][j];
            buffer[i*j+j]=(char)k;
        }
    }
}
