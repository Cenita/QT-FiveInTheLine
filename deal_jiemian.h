#ifndef DEAL_JIEMIAN_H
#define DEAL_JIEMIAN_H
#include <mainwindow.h>
#include <mousevents.h>
namespace mouse {
class control;
}

void MainWindow::deal_chushi()//初始化页面
{//______________________初始化界面_______________________
    open=0;
    ui->bendi->setVisible(true);
    ui->shownumber->setVisible(false);
    ui->renji_jiandan->setVisible(false);
    ui->renji_putong->setVisible(false);
    ui->wangluo->setVisible(true);
    ui->renji->setVisible(true);
    ui->Back->setVisible(false);
    ui->Flash->setVisible(false);
    ui->home->setVisible(false);
    Killstart(false);
    ui->ready->setVisible(false);
    ui->talk_show->clear();
    network_connect(2);
    network_talk(2);
 //——————————————————————初始化界面——————————————————————————
 //______________________初始化数值__________________________
    player=0;
    player_who=0;//1黑棋 2白棋
    x1=0,x2=0,x3=0,y1=0,y2=0,y3=0;//胜利坐标
    Win=false;//是否胜利
    Mouse_x=0,Mouse_y=0;//判断实时鼠标位置
    qizi_x=0,qizi_y=0;//判断最新一次下的棋子位置
    Haveddrop;//出过棋子吗？
    start1=false;
    network_player=0;
    network_Isyou=true;
    network_response=false;
    network_ready=0;
    open=0;
    ready_on=0;
    memset(qipan, 0, 15 * 15 * 4);
    is_shownumber=false;

 //——————————————————————初始化数值——————————————————————————
}
void MainWindow::deal_bendi()
{   open=1;
    ui->bendi->setVisible(false);
    ui->wangluo->setVisible(false);
    ui->renji->setVisible(false);
    ui->Back->setVisible(true);
    ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
    ui->shownumber->setStyleSheet("border-image: url(:/image/shownumber1.png);");
    ui->Back->setEnabled(true);
    ui->home->setVisible(true);
    ui->shownumber->setVisible(true);
    ui->Flash->setVisible(true);
    update();
}
void MainWindow::deal_wangluo()
{
    ui->message->setText("");
    open=2;
    ui->shownumber->setVisible(true);
    ui->home->setVisible(true);
    ui->bendi->setVisible(false);
    ui->wangluo->setVisible(false);
    ui->renji->setVisible(false);
    ui->ready->setVisible(true);
    ui->ready->setStyleSheet("border-image: url(:/image/ready-3.png);");
    ui->ready->setEnabled(false);
    ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
    ui->Back->setEnabled(false);
    ui->Back->setVisible(true);
    QString hostname = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(hostname);
    foreach(QHostAddress address,info.addresses())
    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol)
         {   IP="本机IP地址是:"+address.toString();
             ui->message->setText(IP);
         }
    }
    network_connect(1);
    network_talk(1);
    network_talk(4);
    networkstart();
    update();
}
void MainWindow::deal_renji(int a)
{
    open=3;
    network_player=3;
    if (a==1)
    Degree=1;
    if (a==2)
    Degree=2;
    ui->Back->setVisible(true);
    ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
    ui->Back->setEnabled(true);
    ui->home->setVisible(true);
    ui->Flash->setVisible(true);
    ui->shownumber->setVisible(true);
    ui->renji_jiandan->setVisible(false);
    ui->renji_putong->setVisible(false);
    update();
}
void MainWindow::Killstart(bool yesorno)//重启事件
{

    if (yesorno==true)
    {
        if (start1==false)
        {   on_Flash_clicked();
            ui->Flash->setStyleSheet("border-image: url(:/image/start2.png);");
            update();
        }
        else
        {   on_Flash_clicked();
            on_Flash_clicked();
            ui->Flash->setStyleSheet("border-image: url(:/image/start2.png);");
            update();
        }
    }
    if (yesorno==false)
    {
        if (start1==true)
        {    on_Flash_clicked();
             ui->Flash->setStyleSheet("border-image: url(:/image/start.png);");
             update();
        }
        else
        {   on_Flash_clicked();
            on_Flash_clicked();
            ui->Flash->setStyleSheet("border-image: url(:/image/start.png);");
            update();
        }
    }
    if (network_player==1)
        network_Isyou=true;
    if (network_player==2)
        network_Isyou=false;
    update();


}
void MainWindow::deal_ready(int player)
{ if (player==1)
    {
        playeroneready=true;
        if (playeroneready==true && playertwoready==true)
        {
            Killstart(true);
            ui->message->setText("双方准备完毕开始游戏");
            update();
        }
    }
  else if (player==2)
    {
        playertwoready=true;
        if (playeroneready==true && playertwoready==true)
        {
            Killstart(true);
            ui->message->setText("双方准备完毕开始游戏");
            update();
        }
    }
}
void MainWindow::deal_networkchongzhi(int player)
{   if (player==1)
    {
        Killstart(false);
        network_response=false;
        ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
        ui->Back->setEnabled(false);
        playeroneready=false;
        playertwoready=false;
    }
    else if (player==2)
    {
        Killstart(false);
        network_response=false;
        ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
        ui->Back->setEnabled(false);
        playeroneready=false;
        playertwoready=false;
    }
}
void MainWindow::network_talk(int a)//聊天窗口 1.显示 2.隐藏 3.允许使用 4.禁止使用
{
    if (a==1)//显示
    {
        ui->talk_line1->setVisible(true);
        ui->talk_line2->setVisible(true);
        ui->talk_line3->setVisible(true);
        ui->talk_line4->setVisible(true);
        ui->talk_send->setVisible(true);
        ui->talk_show->setVisible(true);
        ui->talk_text->setVisible(true);
        ui->talk_input->setVisible(true);
    }
    else if (a==2)//隐藏
    {
        ui->talk_line1->setVisible(false);
        ui->talk_line2->setVisible(false);
        ui->talk_line3->setVisible(false);
        ui->talk_line4->setVisible(false);
        ui->talk_send->setVisible(false);
        ui->talk_show->setVisible(false);
        ui->talk_text->setVisible(false);
        ui->talk_input->setVisible(false);
    }
    else if (a==3)//允许使用
    {
        ui->talk_send->setEnabled(true);
        ui->talk_show->setEnabled(true);
        ui->talk_text->setEnabled(true);
        ui->talk_input->setEnabled(true);
    }
    else if (a==4)//禁止使用
    {
        ui->talk_send->setEnabled(false);
        ui->talk_show->setEnabled(false);
        ui->talk_text->setEnabled(false);
        ui->talk_input->setEnabled(false);
    }
}
void MainWindow::network_connect(int a)//连接窗口 1.显示 2.隐藏
{
    if (a==1)
    {
        ui->line->setVisible(true);
        ui->line_2->setVisible(true);
        ui->line_3->setVisible(true);
        ui->line_4->setVisible(true);
        ui->lineEdit->setVisible(true);
        ui->lineEdit_2->setVisible(true);
        ui->connect->setVisible(true);
        ui->listen->setVisible(true);
        ui->message->setVisible(true);
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
    }
    else if (a==2)
    {
        ui->line->setVisible(false);
        ui->line_2->setVisible(false);
        ui->line_3->setVisible(false);
        ui->line_4->setVisible(false);
        ui->lineEdit->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->connect->setVisible(false);
        ui->listen->setVisible(false);
        ui->message->setVisible(false);
        ui->label->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
    }
}















#endif // DEAL_JIEMIAN_H
