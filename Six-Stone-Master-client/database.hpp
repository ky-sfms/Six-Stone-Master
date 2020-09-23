﻿#ifndef DATABASE_H
#define DATABASE_H
#include<QString>
#include<QTimer>
#include<QEventLoop>
#include<QMessageBox>


#define WIDTH 1920
#define HEIGHT 1080
enum Gametype{MM,MA,AA};//游戏模式,创建游戏时赋值
enum Gamestate{win,playing,death,waiting};//游戏状态,初始化时设置
enum GameAI{easy,diff,none};//AI模式,创建游戏时赋值
const int margin=45;
const int rowline=21;
const int columnline=21;
const int r=20;
const int one=45;
enum what{iswhite=0,isblack,isempty};



 // 用户程序之间交互协议
enum comm_request_type
{
    //连接服务器失败
    COMM_SERVER_CONN_FAILED,
    //连接服务器成功
    COMM_SERVER_CONN_SUCCESSFUL,
    //服务器关闭
    COMM_SERVER_CLOSE,
    //服务器发送大厅信息
    COMM_SERVER_GAMEINFO,
    //双方准备，服务器开始游戏
    COMM_SERVER_GAMESTART,
    //某方玩家胜利，服务器结束游戏
    COMM_SERVER_GAMEOVER,

    //客户端请求创建主机
    COMM_CLIENT_CREATE,
    //客户端请求加入房间
    COMM_CLIENT_JOIN,
    //玩家退出房间
    COMM_CLIENT_QUITGAME,
    //玩家游戏操作：落子
    COMM_CLIENT_GAMEOP,
     //玩家游戏操作：悔棋
     COMM_CLIENT_UNDO,
     //玩家游戏操作：悔棋回复yes
     COMM_CLIENT_UNDO_YES,
     //玩家游戏操作：悔棋回复no
     COMM_CLIENT_UNDO_NO,
    //玩家游戏操作：认输
    COMM_CLIENT_LOSE,
    //玩家发来ip地址
    COMM_CLIENT_IP,
    //玩家游戏操作：发送聊天信息
    COMM_CLIENT_CHAT,
    //玩家发送胜利，游戏结束
    COMM_CLIENT_WIN
};
// 用户程序之间交互数据包的格式
struct msg_request_struct
{
    //请求类型
    qint8 request;//qint8一种数据类型  /* 8 bit signed */
    //数据
    QString data;
};

#endif // DATABASE_H
