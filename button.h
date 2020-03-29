#ifndef BUTTON_H
#define BUTTON_H
#include <mainwindow.h>
//主页面——————————————————————————————————————————————
void MainWindow::on_Flash_clicked()//开始被按下~~~~~~~~~~~~~~~~~~~
{

    memset(simple_ai_Cqizinumber, 0, sizeof(simple_ai_Cqizinumber));
    memset(simple_ai_credit, 0, sizeof(simple_ai_credit));
    memset(qipan, 0, sizeof(qipan));
    memset(back_qipan, 20, sizeof (back_qipan));
    x1=0,x2=0,x3=0,y1=0,y2=0,y3=0,Win=false;
    back_number=0;
    back_number_use=0;
    Haveddrop=false;
    network_Isyou=true;
    if (start1==false)//开始——结束
    {   start1=true;
        ui->Back->setStyleSheet("border-image: url(:/image/huiqi1.png);");
        if (network_player==3&&player_who==2)
         {  qipan[7][7]=1;
            back_number++;
            back_number_use=back_number;
            back_qipan[back_number][1]=7;
            back_qipan[back_number][2]=7;
            update();
         }
    }
    else if (start1==true)//结束——开始
    {
     if (is_shownumber==true)
     on_shownumber_clicked();
     start1=false;
     ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
    }
    Win=false;
    update();

}
void MainWindow::on_Back_clicked()//悔棋按钮
{
  if (start1==true )
  {
      if (network_player ==0 && back_number_use>=1)//本地对战
      { player++;
        int a,b;
        a=back_qipan[back_number_use][1];
        b=back_qipan[back_number_use][2];
        qipan[a][b]=0;
        back_qipan[back_number_use][1]=20;
        back_qipan[back_number_use][2]=20;
        back_number_use--;
        back_number=back_number_use;
        qizi_x=back_qipan[back_number_use][1];
        qizi_y=back_qipan[back_number_use][2];
        if (back_number_use==0)
        {

           ui->Back->setEnabled(false);
           ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
            memset(back_qipan, 20, sizeof(back_qipan));
           back_number=0;
           back_number_use=0;
        }
         update();
      }
      if (network_player ==3 && back_number_use>=1)//人机对战
      {
        int a,b;
         a=back_qipan[back_number_use][1];
         b=back_qipan[back_number_use][2];
         qipan[a][b]=0;
         back_qipan[back_number_use][1]=20;
         back_qipan[back_number_use][2]=20;
          if (back_number_use-1>=1)
          {a=back_qipan[back_number_use-1][1];
          b=back_qipan[back_number_use-1][2];
          qipan[a][b]=0;
          back_qipan[back_number_use-1][1]=20;
          back_qipan[back_number_use-1][2]=20;}
          if (back_number_use-3>=0)
          {    medium_ai_last[1]=back_qipan[back_number_use-2][1];
               medium_ai_last[2]=back_qipan[back_number_use-2][2];
               qizi_x=back_qipan[back_number_use-3][1];
               qizi_y=back_qipan[back_number_use-3][2];
          }
          else
          {
              medium_ai_last[1]=20;
              medium_ai_last[2]=20;
               qizi_x=20;
               qizi_y=20;
          }
           back_number_use-=2;
          back_number=back_number_use;
          if (back_number_use==0)
          {
              ui->Back->setEnabled(false);
              ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
              back_number=0;
              back_number_use=0;
          }
          if (back_number_use==1)
          {
              ui->Back->setEnabled(false);
              ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
              back_number=1;
              back_number_use=1;
          }
         update();
      }
      if (network_player==1 && qipan[qizi_x][qizi_y]!=0)//服务端撤回
      {
          QString send;
          send = "ineedBack";
          socket->write(qPrintable(send));
          ui->message->setText("等待对方回应");
      }
      if (network_player==2 && qipan[qizi_x][qizi_y]!=0)//客户端撤回
      {
          QString send;
          send = "ineedBack";
          socket1->write(qPrintable(send));
          ui->message->setText("等待对方回应");
      }
    }

}
void MainWindow::on_connect_clicked()//客户端连接按键
{   QString IP;
    int port;
    port=ui->lineEdit_2->text().toInt();
    IP = ui->lineEdit->text();

    if (ui->lineEdit_2->text()=="")//判断端口号是否为空
    {
        ui->message->setText("请输入端口号");
        return ;
    }
    if (ui->lineEdit->text()=="")//判断IP地址是否为空
    {
        ui->message->setText("请输入IP地址");
        return ;
    }
    socket1->connectToHost(IP, port);
    if (ui->connect->text()=="连接")
    {   if(!socket1->waitForConnected(3000))//判断连接是否超时
        {
        ui->message->setText ("连接失败");//超时
        return;
        }
        else//正常连接
        {network_player=2;
         player_who=2;
         ui->listen->setEnabled(false);
         ui->lineEdit->setEnabled(false);
         ui->lineEdit_2->setEnabled(false);
         ui->message->setText ("与玩家1(黑棋)通信成功！");
         network_talk(3);
         ui->connect->setText ("断开连接");
         network_Isyou=false;
         ui->ready->setStyleSheet("border-image: url(:/image/ready-1.png);");
         ui->ready->setEnabled(true);
         update();
        }
    }
    else//取消连接
    {   network_player=0;
        ui->listen->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->connect->setText ("连接");
        ui->message->setText ("断开连接");
        network_Isyou=false;
        socket1->disconnectFromHost();
        ui->ready->setStyleSheet("border-image: url(:/image/ready-3.png);");
        ui->ready->setEnabled(false);
        update();
    }

}
void MainWindow::on_listen_clicked()//侦听按钮
{
    int port;
    port=ui->lineEdit_2->text().toInt();
    if (ui->lineEdit_2->text()=="")//判断端口号是否为空
    {
        ui->message->setText("请输入端口号");
        return ;

    }
    if (ui->listen->text()=="侦听")
    {

        if(server->listen(QHostAddress::Any,port)==0)//判断是否能打开监听按钮，如果不能则失败
        {
            ui->message->setText ("本端侦听失败");
            return;
        }
        else//正常监听
        {   network_player=1;
            player_who=1;
            update();
            ui->connect->setEnabled(false);
            ui->lineEdit->setEnabled(false);
            ui->lineEdit_2->setEnabled(false);
            ui->listen->setText ("取消侦听");
            ui->message->setText(IP);
            network_Isyou=false;

        }
    }
    else//取消监听
    {   network_player=0;
        socket->close();
        server->close();
        ui->connect->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->listen->setText("侦听");
        ui->message->setText(IP);
        network_Isyou=false;
        ui->ready->setStyleSheet("border-image: url(:/image/ready-3.png);");
        ui->ready->setEnabled(false);
    }
}
//开始界面处理——————————————————————————————————————
void MainWindow::on_bendi_clicked()//本地按钮被单击
{

 deal_bendi();

}
void MainWindow::on_wangluo_clicked()//网络按钮
{

 deal_wangluo();
}
void MainWindow::on_renji_clicked()//人机按钮
{
    ui->bendi->setVisible(false);
    ui->wangluo->setVisible(false);
    ui->renji->setVisible(false);
    ui->renji_putong->setVisible (true);
    ui->renji_jiandan->setVisible(true);
}
void MainWindow::on_home_clicked()//菜单按钮
{ if (ui->listen->text()=="取消侦听")
    {
        QString sent;
        sent = "player1isquit";
        socket->write(qPrintable(sent));
        playertwoready=false;
        playertwoready=false;
        Killstart(false);
        network_talk(4);
        ui->talk_show->clear ();
        server->close();
        socket->close();
        on_listen_clicked();
    }
if (ui->connect->text()=="断开连接")
    {
        QString sent;
        sent = "player2isquit";
        socket1->write(qPrintable(sent));
        on_connect_clicked();
        playertwoready=false;
        playertwoready=false;
        network_talk(4);
        ui->talk_show->clear ();
        Killstart(false);
    }
     deal_chushi();
}
void MainWindow::on_ready_clicked()//准备按钮
{
 if (ready_on!=0)
 {
    if (network_player==1)
    {
     QString sent;
     sent = "player1isready";
     socket->write(qPrintable(sent));
     ui->message->setText("等待玩家2(白棋)准备");
     deal_ready(1);
    }
    else if (network_player==2)
    {
     QString sent;
     sent = "player2isready";
     socket1->write(qPrintable(sent));
     ui->message->setText("等待玩家1(黑棋)准备");
     deal_ready(2);
    }
 }
 else if (ready_on==0)
 {
     if (network_player==1)
     {
      QString sent;
      sent = "player1isquit";
      socket->write(qPrintable(sent));
      ui->message->setText("你退出了游戏");
      playeroneready=false;
      Killstart(false);
      network_Isyou=true;
      }
     else if (network_player==2)
     {
      QString sent;
      sent = "player2isquit";
      socket1->write(qPrintable(sent));
      ui->message->setText("你退出了游戏");
      playertwoready=false;
      Killstart(false);
      network_Isyou=false;
     }
     update();
 }

}
void MainWindow::on_renji_jiandan_clicked()//人机简单按钮
{
deal_renji(1);

}
void MainWindow::on_renji_putong_clicked()//人机普通按钮
{
deal_renji(2);
}
void MainWindow::on_shownumber_clicked()//显数按钮
{
    if (is_shownumber==false)
    {
        ui->shownumber->setStyleSheet("border-image: url(:/image/hidenumber1.png);");
        is_shownumber=true;
        update();
    }
    else if (is_shownumber==true)
    {
        ui->shownumber->setStyleSheet("border-image: url(:/image/shownumber1.png);");
        is_shownumber=false;
        update();
    }
}
void MainWindow::on_talk_send_clicked()//发送聊天信息
{   QString say,say1,say2;
    say1=ui->talk_input->text();
    QByteArray datasend = ui->talk_input->text().toLocal8Bit();
    say="talk:";
    qDebug ()<<datasend;
    if (network_player==1)
    {   say2="黑棋:"+say1;
        ui->talk_show->addItem(say2);
        socket->write(say.toLatin1()+datasend);
        ui->talk_input->clear();


    }
    else if (network_player==2)
    {   say2="白棋:"+say1;
        ui->talk_show->addItem(say2);
        socket1->write(say.toLatin1()+datasend);
        ui->talk_input->clear();
    }

}
//按钮图片处理集_____________________________________________
void MainWindow::on_bendi_pressed()//本地按钮被按下
{
    ui->bendi->setStyleSheet("border-image: url(:/image/bendi_push.png);");
}
void MainWindow::on_bendi_released()//本地按钮
{
    ui->bendi->setStyleSheet("border-image: url(:/image/bendi.png);");
}
void MainWindow::on_wangluo_pressed()//网络按钮被按下
{
 ui->wangluo->setStyleSheet("border-image: url(:/image/wangluo_push.png);");
}
void MainWindow::on_wangluo_released()//网络按钮被松开
{
 ui->wangluo->setStyleSheet("border-image: url(:/image/wangluo.png);");
}
void MainWindow::on_renji_pressed()//人机按钮被按下
{
 ui->renji->setStyleSheet("border-image: url(:/image/renji_push.png);");
}
void MainWindow::on_renji_released()//人机按钮被松开
{
 ui->renji->setStyleSheet("border-image: url(:/image/renji.png);");
}
void MainWindow::on_home_pressed()//菜单按钮被按下
{
   ui->home->setStyleSheet("border-image: url(:/image/home-2.png);");
}
void MainWindow::on_home_released()//菜单按钮被松开
{
    ui->home->setStyleSheet("border-image: url(:/image/home-1.png);");
}
void MainWindow::on_Flash_pressed()//开始按钮被按着
{
   if (start1==false)
    {
       ui->Flash->setStyleSheet("border-image: url(:/image/start1.png);");//是开始按钮 按下变红 即将变成结束
    }
   else
    {
    ui->Flash->setStyleSheet("border-image: url(:/image/start3.png);");//是结束按钮 按下变红 即将变成开始
    player=0;
    }

}
void MainWindow::on_Flash_released()//开始按钮被放开
{if (start1==false)
ui->Flash->setStyleSheet("border-image: url(:/image/start2.png);");//放下变结束
 else
ui->Flash->setStyleSheet("border-image: url(:/image/start.png);");//放下变开始

}
void MainWindow::on_Back_pressed()//悔棋按钮被按下
{  if (start1==true)
   ui->Back->setStyleSheet("border-image: url(:/image/huiqi2.png);");
}
void MainWindow::on_Back_released()//悔棋按钮被松开
{   if (start1==true)
    ui->Back->setStyleSheet("border-image: url(:/image/huiqi1.png);");

}
void MainWindow::on_ready_pressed()//准备按钮被按下
{
    ui->ready->setStyleSheet("border-image: url(:/image/ready-2.png);");

}
void MainWindow::on_ready_released()//准备按钮被松开
{   if (ready_on==0)//变退出
    {  ui->ready->setStyleSheet("border-image: url(:/image/quit-1.png);");
        ready_on=1;
    }
    else if (ready_on==1)//变开始
    {
        ui->ready->setStyleSheet("border-image: url(:/image/ready-1.png);");
        ready_on=0;
    }
}
void MainWindow::on_renji_jiandan_pressed()//人机简单按钮被按下
{
ui->renji_jiandan->setStyleSheet("border-image: url(:/image/renji_jiandan2.png);");
}
void MainWindow::on_renji_jiandan_released()//人机简单按钮被松开
{
ui->renji_jiandan->setStyleSheet("border-image: url(:/image/renji_jiandan1.png);");
}
void MainWindow::on_renji_putong_pressed()//人机普通按钮被按下
{
ui->renji_putong->setStyleSheet("border-image: url(:/image/renji_putong2.png);");
}
void MainWindow::on_renji_putong_released()//人机普通按钮被松开
{
ui->renji_putong->setStyleSheet("border-image: url(:/image/renji_putong1.png);");
}
void MainWindow::on_shownumber_pressed()//显数按钮被按下
{
    if (is_shownumber==false)
        ui->shownumber->setStyleSheet("border-image: url(:/image/shownumber2.png);");
    else if (is_shownumber==true)
        ui->shownumber->setStyleSheet("border-image: url(:/image/hidenumber2.png);");
}
void MainWindow::on_shownumber_released()//显数按钮松开
{
    if (is_shownumber==false)
        ui->shownumber->setStyleSheet("border-image: url(:/image/hidenumber1.png);");
    else if (is_shownumber==true)
        ui->shownumber->setStyleSheet("border-image: url(:/image/shownumber1.png);");
}

//界面处理————————————————————————————————————————————————————————————
#endif // BUTTON_H
