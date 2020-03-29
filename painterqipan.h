#ifndef PAINTERQIPAN_H
#define PAINTERQIPAN_H
#include <mainwindow.h>








void MainWindow::paintEvent(QPaintEvent *)//画事件~~~~~~~~~
{

  //初始化一些变量信息————————————————
  int i,j;
  QString linshi;
  if (network_player==0 || network_player==3)
  player_who=player % 2 + 1;
  //初始化一些变量信息————————————————

  //设置鼠标跟踪————————————————————————————————
  ui->centralWidget->setMouseTracking(true);
  setMouseTracking(true);
  //设置鼠标跟踪————————————————————————————————

  //设置背景——————————————————————————
  QPixmap pixmap11(":/image/Qqipan2.jpg");
  QPixmap pixmap = pixmap11.scaled(1400, 800);
  QPainter bgp(this);
  bgp.drawPixmap(0,0,pixmap);
  //设置背景————————————————————————————————————


  //设置画笔信息——————————————————————————————
  QPainter pen (this);
  pen.setRenderHint(QPainter::Antialiasing, true);
  QPen bi;
  bi.setWidth(0.5);
  QImage tp;
  bi.setStyle(Qt::SolidLine);
  bi.setCapStyle(Qt::SquareCap);
  pen.setPen(bi);
  QImage baiqi;
  baiqi.load(":/image/baiqi1.png");
  QImage heiqi;
  heiqi.load(":/image/heiqi1.png");
  QImage mz;
  mz.load(":/image/miaozhun.png");
  QImage redpoint;
  redpoint.load(":/image/point.png");
  QImage big_baiqi;
  big_baiqi.load(":/image/big_baiqi.png");
  QImage big_heiqi;
  big_heiqi.load(":/image/big_heiqi.png");
  QImage tiaofu;
  tiaofu.load(":/image/tiaofu.png");
  QImage topic;
  topic.load(":/image/topic.png");
  QBrush point;
  //设置画笔信息————————————————————————————————————

  //画棋盘————————————————————————————————————————
if (open != 0)
{  QPixmap pix(":/image/qipanss.png");
   QPixmap pix2 = pix.scaled(605, 605);
   pen.drawPixmap(qipan_x-30,qipan_y-30,pix2);
  for (i=0;i<=14;i++)
  {
   pen.drawLine(qipan_x,qipan_y+i*qipan_kuan,qipan_x+14*qipan_kuan,qipan_y+i*qipan_kuan);
   pen.drawLine(qipan_x+i*qipan_kuan,qipan_y,qipan_x+i*qipan_kuan,qipan_y+14*qipan_kuan);
  }
    //画棋盘点——————————————————————————————————————————————————————————
    point.setStyle(Qt::SolidPattern);
    pen.setBrush(point);
    pen.drawEllipse(QPoint (qipan_x+3*qipan_kuan,qipan_y+3*qipan_kuan),3,3);
    pen.drawEllipse(QPoint (qipan_x+11*qipan_kuan,qipan_y+3*qipan_kuan),3,3);
    pen.drawEllipse(QPoint (qipan_x+7*qipan_kuan,qipan_y+7*qipan_kuan),3,3);
    pen.drawEllipse(QPoint (qipan_x+3*qipan_kuan,qipan_y+11*qipan_kuan),3,3);
    pen.drawEllipse(QPoint (qipan_x+11*qipan_kuan,qipan_y+11*qipan_kuan),3,3);
    //画棋盘点——————————————————————————————————————————————————————————
  for (i = 0; i < 15; i++)
  {
   for (j = 0; j < 15; j++)
   {
      if (qipan[i][j] == 1)
      {

          pen.drawImage(qipan_x+qipan_kuan*i-20,qipan_y+qipan_kuan*j-20,heiqi);

      }
      else if (qipan[i][j] == 2)
      {

          pen.drawImage(qipan_x+qipan_kuan*i-20,qipan_y+qipan_kuan*j-20,baiqi);

      }
   }
  }

  pen.drawImage(qipan_x-60,qipan_y+580,tiaofu);//画条幅

  if (player_who==1)//画大棋子
      pen.drawImage(qipan_x+230,qipan_y+590,big_heiqi);
  else
      pen.drawImage(qipan_x+230,qipan_y+590,big_baiqi);
}
else
  pen.drawImage(qipan_x+95,qipan_y,topic);


  //画棋子—————————————————————————————————————————




  //处理信息————————————————————————————————————————

 if (Win == true)//如果胜利则画一条线
 {
     QPen redbi;
     redbi.setColor(Qt::red);
     redbi.setWidth(5);
     pen.setPen(redbi);
     pen.drawLine(x1,y1,x3,y3);
     pen.drawLine(x3,y3,x2,y2);
 }




 if (start1==true && Win==false)                    //画红色方框~~~和预选棋子~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  {  if (qipan[(Mouse_x-qipan_x+20)/qipan_kuan][(Mouse_y-qipan_y+20)/qipan_kuan] == 0 && network_Isyou==true)
    {   if (Mouse_x>qipan_x-20 && Mouse_x<qipan_x+14*qipan_kuan+20 && Mouse_y>qipan_y-20 &&Mouse_y<19+qipan_y+14*qipan_kuan)
       {
       int cl_mouse_x,cl_mouse_y;
       cl_mouse_x=qipan_x+qipan_kuan*((Mouse_x-qipan_x+20)/qipan_kuan)-20;
       cl_mouse_y=qipan_y+qipan_kuan*((Mouse_y-qipan_y+20)/qipan_kuan)-20;
       if (player_who==1)//画棋子
          pen.drawImage(cl_mouse_x,cl_mouse_y,heiqi);
       else
          pen.drawImage(cl_mouse_x,cl_mouse_y,baiqi);

        pen.drawImage(cl_mouse_x,cl_mouse_y,mz);

        }
    }

    if(Haveddrop==true)//画红点
    {
     int cl_qizi_x,cl_qizi_y;
     cl_qizi_x=qipan_x+qizi_x*qipan_kuan-20;
     cl_qizi_y=qipan_y+qizi_y*qipan_kuan-20;
     pen.drawImage(cl_qizi_x,cl_qizi_y,redpoint);
     if (network_player==3)
     {
         cl_qizi_x=qipan_x+medium_ai_last[1]*qipan_kuan-20;
         cl_qizi_y=qipan_y+medium_ai_last[2]*qipan_kuan-20;
         pen.drawImage(cl_qizi_x,cl_qizi_y,redpoint);
     }
    }


   }

  //处理信息————————————————————————————————————————

 //画记录次数——————————————————————————————————————

   if (Haveddrop==true&&is_shownumber==true)
   {


       QPen numberbi;
       QFont ziti;


     for (int a=1;a<=225;a++)
     {
        for (int b=1;b<=2;b++)
        {

            if (back_qipan[a][b]<=14&&back_qipan[a][b]>=0)
            {   int x=back_qipan[a][1],y=back_qipan[a][2];
                linshi=QString::number(a,10);
                if (qipan[x][y]==2)
                    numberbi.setColor(Qt::black);
                if (qipan[x][y]==1)
                    numberbi.setColor(Qt::white);
                pen.setPen(numberbi);
                if (qipan[x][y]==0)
                    continue;
                else if (a>0&&a<=9)
                { ziti.setPointSize(20);
                  pen.setFont(ziti);
                  pen.drawText(qipan_x+x*qipan_kuan-7, qipan_y+y*qipan_kuan+9, linshi);
                }
                if (a>=10&&a<=99)
                {
                    ziti.setPointSize(15);
                    pen.setFont(ziti);
                    pen.drawText(qipan_x+x*qipan_kuan-10, qipan_y+y*qipan_kuan+7, linshi);

                }
                else if (a>=100)
                {
                  ziti.setPointSize(10);
                  pen.setFont(ziti);
                  pen.drawText(qipan_x+x*qipan_kuan-10, qipan_y+y*qipan_kuan+5, linshi);
                }
            }
        }
      }
 }


}





#endif // PAINTERQIPAN_H
