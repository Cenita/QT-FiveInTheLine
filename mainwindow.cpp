#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <pd_shuying.h>
#include <button.h>
#include <painterqipan.h>
#include <mousevents.h>
#include <deal_jiemian.h>
#include <ai_simple.h>
#include <ai_medium.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
      ui->setupUi(this);
      setWindowIcon(QIcon("tubiao.ico"));
      resize(1400, 800);
      this->setFixedSize( this->width (),this->height ());
      memset(back_qipan, 20, sizeof(back_qipan));
      memset(qipan, 0,sizeof (qipan));
      deal_chushi();


    }
MainWindow::~MainWindow()
{
    delete this->socket1;
    delete this->socket;
    delete this->server;
    delete ui;

}

void MainWindow::server_New_Connect()//服务端获得新的连接
{
    socket = server->nextPendingConnection();
    //连接QTcpSocket的信号槽，以读取新数据
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &MainWindow::socket_Disconnected);
    ui->message->setText("玩家2(白棋):上线！");
    qDebug() << "A Client connect!";
    ui->ready->setStyleSheet("border-image: url(:/image/ready-1.png);");
    ui->ready->setEnabled(true);
    network_talk(3);
}
void MainWindow::socket_Read_Data()//服务端读取数据
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        Dealnetworkmessage(buffer);
    }
}
void MainWindow::socket_Disconnected()//服务端失去连接
{
    //发送按键失能
    ui->message->setText("玩家2(白棋):下线");
    on_Flash_clicked();
    qDebug() << "Disconnected!";
    ui->ready->setStyleSheet("border-image: url(:/image/ready-3.png);");
    ui->ready->setEnabled(false);
    Killstart(false);
    playeroneready=false;
    playertwoready=false;
    network_talk(4);
    ui->talk_show->clear ();
}
void MainWindow::networkstart()//网络初始化
{
        server = new QTcpServer();
        socket1 = new QTcpSocket();
        //连接信号槽
        QObject::connect(socket1, &QTcpSocket::readyRead, this, &MainWindow::socket1_Read_Data);
        QObject::connect(socket1, &QTcpSocket::disconnected, this, &MainWindow::socket1_Disconnected);
        connect(server,&QTcpServer::newConnection,this,&MainWindow::server_New_Connect);
}
void MainWindow::socket1_Disconnected()//客户端断开连接
{
   on_Flash_clicked();
   qDebug() << "Disconnected!";
    playeroneready=false;
    playertwoready=false;
    Killstart(false);
    network_talk(4);
    ui->message->setText("失去连接");
    ui->talk_show->clear ();
    if (ui->connect->text()=="断开连接")
       on_connect_clicked();
}
void MainWindow::socket1_Read_Data()//客户端读取数据
{
    QByteArray buffer;

    //读取缓冲区数据
    buffer = socket1->readAll();
    if(!buffer.isEmpty())
    {
     Dealnetworkmessage(buffer);
    }
}
void MainWindow::Dealnetworkmessage(QByteArray q)//处理事件函数
{
    int a,b,c;
    QString get;
    get = QString (q);
    qDebug(get.toLatin1());
    if (get.contains("chess")==true)//收到棋子下棋
    {
      if (network_ready==1)
      {
      Killstart(true);
      ui->message->setText("Game Start!");
      }
      get = get.section("chess:",1);
      a = get.section(",",0,0).toInt();
      b = get.section(",",1,1).toInt();
      c = get.section(",",2,3).toInt();
      back_number++;
      back_number_use=back_number;
      back_qipan[back_number][1]=a;
      back_qipan[back_number][2]=b;
      qipan[a][b]=c;
      qizi_x=a;
      qizi_y=b;
      Haveddrop=true;
      network_Isyou=true;
      ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
      ui->Back->setEnabled(false);
      network_talk(3);
      Is_Win(a,b);

    }
    else if (get.contains("ineedBack")==true)//收到悔棋消息
    {
       QMessageBox back (QMessageBox::Information,tr("收到消息"),tr("对方想要悔棋是否同意？"));
       back.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
       back.setButtonText(QMessageBox::Yes,QString("同意"));
       back.setButtonText(QMessageBox::No,QString("拒绝"));
       if (back.exec()==QMessageBox::Yes)
       {
           network_Isyou=false;
           qipan[qizi_x][qizi_y]=0;
           back_qipan[back_number_use][1]=20;
           back_qipan[back_number_use][2]=20;
           back_number_use--;
           back_number=back_number_use;
           qizi_x=back_qipan[back_number_use][1];
           qizi_y=back_qipan[back_number_use][2];
           ui->Back->setStyleSheet("border-image: url(:/image/huiqi1.png);");
           ui->Back->setEnabled(true);
           update();
           if (network_player==1)
           {
               QString sent;
               sent = "Back:1";
               socket->write(qPrintable(sent));
           }
           else if (network_player==2)
           {
               QString sent;
               sent = "Back:1";
               socket1->write(qPrintable(sent));
           }
       }
       else
       {
           if (network_player==1)
           {
               QString sent;
               sent = "Back:2";
               socket->write(qPrintable(sent));
           }
           else if (network_player==2)
           {
               QString sent;
               sent = "Back:2";
               socket1->write(qPrintable(sent));
           }
       }
    }
    else if (get.contains("Back:")==true)//悔棋成功
    {
        get = get.section("Back:",1);
        if (get.toInt()==1)
        {
            qipan[qizi_x][qizi_y]=0;
            network_Isyou=true;
            back_qipan[back_number_use][1]=20;
            back_qipan[back_number_use][2]=20;
            back_number_use--;
            back_number=back_number_use;
            qizi_x=back_qipan[back_number_use][1];
            qizi_y=back_qipan[back_number_use][2];
            ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
            ui->Back->setEnabled(false);
            ui->message->setText("对方同意悔棋");
            update();
        }
        else if (get.toInt()==2)
        {
            ui->message->setText("对方拒绝悔棋");
        }
    }
    else if (get.contains("player1isready")==true)//玩家1准备消息
    {
       ui->message->setText("玩家1(黑棋)已经准备");
       deal_ready(1);

    }
    else if (get.contains("player2isready")==true)//玩家2准备消息
    {
       ui->message->setText("玩家2(白棋)已经准备");
       ui->ready->setEnabled(true);
       deal_ready(2);
    }
    else if (get.contains("player1isquit")==true)
    {
        ui->message->setText("玩家1(黑棋)退出游戏");
        ui->ready->setStyleSheet("border-image: url(:/image/ready-1.png);");
        ready_on=0;
        playeroneready=false;
        playertwoready=false;
        network_talk(4);
        ui->talk_show->clear ();
        Killstart(false);
    }
    else if (get.contains("player2isquit")==true)
    {
        ui->message->setText("玩家2(白棋)退出游戏");
        ui->ready->setStyleSheet("border-image: url(:/image/ready-1.png);");
        ready_on=0;
        playeroneready=false;
        playertwoready=false;
        network_talk(4);
        ui->talk_show->clear ();
        Killstart(false);
    }
    else if (get.contains("keyile")==true)
    { if (receive_number<=2)
      {  if (network_player==1)
        {
            QString sent;
            sent = "keyile";
            socket->write(qPrintable(sent));
        }
        else if (network_player==2)
        {
               QString sent;
               sent = "keyile";
               socket1->write(qPrintable(sent));
        }
        ui->ready->setStyleSheet("border-image: url(:/image/ready-1.png);");
        ui->ready->setEnabled(true);
        network_talk(3);
        ready_on=0;
      }  
        receive_number++;
    }
    else if (get.contains("talk")==true)
      {   QString msg;
          msg=QString::fromLocal8Bit(q);

          qDebug ()<<msg;
          if (network_player==2)
          {   msg="黑棋:"+msg.section("talk:",1);
              ui->talk_show->addItem(msg);
          }
          if (network_player==1)
          {   msg="白棋:"+msg.section("talk:",1);
              ui->talk_show->addItem(msg);
          }
      }
    update();

}























