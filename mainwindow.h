#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include "QPainter"
#include <QPixmap>
#include <Qpen>
#include <QImage>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QBrush>
#include <QTextCodec>
#include <QFont>
#include <QHostInfo>
#include <QDialog>
#include <QTextCodec>
//常量————————————————————————————————
#define qipan_kuan 39
#define qipan_x 370
#define qipan_y 90
#define _S(X) (QStringLiteral(X))
//常量————————————————————————————————
namespace Ui {
class MainWindow;
class Paint;
class control;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int pd_shuying (int x=0,int y=0);//判断输赢
    int pd_ZYsou(int x=0,int y=0);//左右搜索
    int pd_SXsou(int x=0,int y=0);//上下搜索
    int pd_ZSYXsou(int x=0,int y=0);//左上到右下搜索
    int pd_ZXYSsou(int x=0,int y=0);//左下到右上搜索
    void P_Winline (int x1=0,int y1=0,int x2=0,int y2=0);//胜利函数 1为玩家1 2为玩家2
    void paintEvent(QPaintEvent *);//画事件
    void mouseReleaseEvent(QMouseEvent *);//鼠标释放事件
    void mouseMoveEvent(QMouseEvent *);//鼠标移动事件
    void networkstart();
    void server_New_Connect();//服务器有新的连接
    void Dealnetworkmessage(QByteArray q);//判断客户端和服务端接收到的数据
    bool Is_Win (int x,int y);//判断是否胜利
    void Killstart (bool yesorno);//使游戏变量得到重置，用于调用开始函数
    void deal_chushi();//初始化所有的值，用于返回菜单使用
    void deal_bendi();//启动本地对战函数
    void deal_wangluo();//启动网络对战函数
    void deal_renji();//启动人机对战函数
    void deal_ready(int player);//准备函数
    void deal_networkchongzhi(int player);//网络重置变量函数
    void deal_renji(int a);//判断启用什么模式
    void simple_ai_search_han();//初等ai搜索函数
    void simple_ai_credit_han();//初等ai打分函数
    void simple_ai_down();//初等ai下棋动作
    void medium_ai_search_han();//中等ai搜索函数
    void medium_ai_credit_han();//中等ai打分函数
    void medium_ai_down();//中等ai下棋动作
    bool medium_ai_judge(int A,int B,int C,int a1,int a2,int a3,int a4,int b1,int b2,int b3,int b4);//中等ai判断棋性
    void medium_ai_getcredit(int A,int B,int C,int D,int E,int a1,int a2,int a3,int a4,int b1,int b2,int b3,int b4);//输入分数
    bool medium_ai_getqixing(int A,int B,int C,int a1,int a2,int a3,int a4,int b1,int b2,int b3,int b4);//判断连棋
    void network_talk(int a);//聊天窗口 1.显示 2.隐藏 3.允许使用 4.禁止使用
    void network_connect(int a);//连接窗口 1.显示 2.隐藏
    void win_deal();//胜利处理事件

private slots:
    void on_Flash_clicked();
    void on_Back_clicked();
    void on_Flash_pressed();
    void on_Flash_released();
    void on_Back_pressed();
    void on_Back_released();
    void socket_Read_Data();
    void socket_Disconnected();
    void socket1_Read_Data();
    void socket1_Disconnected();
    void on_connect_clicked();
    void on_listen_clicked();
    void on_bendi_clicked();
    void on_bendi_pressed();
    void on_bendi_released();
    void on_wangluo_clicked();
    void on_wangluo_pressed();
    void on_wangluo_released();
    void on_renji_clicked();
    void on_renji_pressed();
    void on_renji_released();
    void on_home_clicked();
    void on_home_pressed();
    void on_home_released();
    void on_ready_clicked();
    void on_ready_pressed();
    void on_ready_released();
    void on_renji_jiandan_clicked();
    void on_renji_jiandan_pressed();
    void on_renji_jiandan_released();
    void on_renji_putong_clicked();
    void on_renji_putong_pressed();
    void on_renji_putong_released();
    void on_shownumber_clicked();
    void on_shownumber_pressed();
    void on_shownumber_released();
    void on_talk_send_clicked();
private:
    Ui::MainWindow *ui;
    int back_number_use=0;//记录反悔按钮点击次数
    int back_number=0;//可反悔次数
    int back_qipan[250][2];//反悔棋盘数据
    int qipan [16][16];//棋盘
    int player=0;//哪个玩家？
    int player_who=0;//1黑棋 2白棋
    int x1=0,x2=0,x3=0,y1=0,y2=0,y3=0;//胜利坐标
    int Mouse_x=0,Mouse_y=0;//判断实时鼠标位置
    int qizi_x=0,qizi_y=0;//判断最新一次下的棋子位置
    int network_player=0;//判断是客户端还是服务端还是本地对战
    int network_ready=0;//判断是否准备
    int open=0;//判断打开了哪种模式
    int ready_on=0;//准备按钮控制
    int receive_number=0;//确定发送次数防止无限发送.
    int simple_ai_Cqizinumber[15][15][2][4];//简单ai用于打分的棋子数  第三个代表不同方棋子,1横2竖3左下右上4左上右下
    int simple_ai_livethree[15][15][2][8];//专门设置一种算法来提高活三的优先级
    int simple_ai_credit[15][15][2];
    int medium_ai_all[16][16][8][4];//用来存储一个方向上四个棋子的数目 【位置】【位置】【方向】【此位置的方向的四个棋位类型】
    int medium_ai_credit[16][16][2];//中等难度ai用来储存分数
    int medium_ai_last[3];//上一次下的
    int Degree=0;//电脑等级
    bool Win=false;//是否胜利
    bool Haveddrop;//出过棋子吗？
    bool start1=false;//用于辅助开始按钮判断是否开始了游戏
    bool network_response=false;
    bool playeroneready=false;//玩家1准备
    bool playertwoready=false;//玩家2准备
    bool network_Isyou=true;//网络对战时是不是你在下棋？
    bool is_shownumber=false;
    QTcpServer* server;//服务器
    QTcpSocket* socket;//服务器的数据接收中心
    QTcpSocket* socket1;//客户端
    QString IP;//本机ip地址

};





#endif // MAINWINDOW_H
