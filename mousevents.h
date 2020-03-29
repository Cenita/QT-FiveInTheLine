#ifndef MOUSEVENTS_H
#define MOUSEVENTS_H
#include <mainwindow.h>
void MainWindow::mouseReleaseEvent(QMouseEvent *e)//鼠标释放事件~~~~~~~~~~~判断输赢~~~~~~~~~
{

    int x, y;
    x=e->pos().x();
    y=e->pos().y();
    if (start1==false)
    {
        if (x>qipan_x+230 && x<qipan_x+330 && y>qipan_y+590 && y<qipan_y+690)//换棋
        {     player++;
              update();
        }
    }
    else
   {
    if(x >= qipan_x-20 && x < qipan_x+14*qipan_kuan+20 && y >= qipan_y-20 && y < qipan_y+14*qipan_kuan+20 && network_Isyou==true)//使鼠标在规定范围内~~~~~~
    {
        x = (x - qipan_x+20) / qipan_kuan;
        y = (y - qipan_y+20) / qipan_kuan;
        qDebug ("x=%d y=%d",x,y);
        if (qipan[x][y]==0)//如果此位置是空位置则可以放入棋子
        {
            Haveddrop = true;
            if (network_player==0)//人人对战
            {   back_number++;
                back_number_use=back_number;
                back_qipan[back_number][1]=x;
                back_qipan[back_number][2]=y;
                qipan[x][y] = (player++) % 2 + 1;
                ui->Back->setEnabled(true);
                ui->Back->setStyleSheet("border-image: url(:/image/huiqi1.png);");
                Is_Win(x,y);//判断输赢
                 update();
            }
            else if (network_player==1)//服务端对战
            {
                back_number++;
                back_number_use=back_number;
                back_qipan[back_number][1]=x;
                back_qipan[back_number][2]=y;
                player_who=1;
                QString sent;
                sent = "chess:"+QString::number(x,10)+","+QString::number(y,10)+",1";
                network_Isyou=false;
                socket->write(qPrintable(sent));
                qipan[x][y] = 1;
                ui->Back->setStyleSheet("border-image: url(:/image/huiqi1.png);");
                ui->Back->setEnabled(true);
                Is_Win(x,y);
            }
            else if (network_player==2)//客户端对战
            {
                back_number++;
                back_number_use=back_number;
                back_qipan[back_number][1]=x;
                back_qipan[back_number][2]=y;
                player_who=2;
                QString sent;
                sent = "chess:"+QString::number(x,10)+","+QString::number(y,10)+",2";
                network_Isyou=false;
                socket1->write(qPrintable(sent));
                qipan[x][y] = 2;
                ui->Back->setStyleSheet("border-image: url(:/image/huiqi1.png);");
                ui->Back->setEnabled(true);
                Is_Win(x,y);//判断输赢
                 update();
            }
            else if (network_player==3)//人机对战
            {
                network_Isyou=true;
                back_number++;
                back_number_use=back_number;
                back_qipan[back_number][1]=x;
                back_qipan[back_number][2]=y;
                if (player_who==1)
                qipan[x][y] = 1;
                if (player_who==2)
                qipan[x][y] = 2;
                ui->Back->setEnabled(true);
                ui->Back->setStyleSheet("border-image: url(:/image/huiqi1.png);");
                if (Is_Win(x,y)==false)
                {
                    if (Degree==1)
                        simple_ai_down();
                    if (Degree==2)
                        medium_ai_down();
                }
            }


            qizi_x=x,qizi_y=y;
        }
        update();

    }
   }

}

void MainWindow::mouseMoveEvent(QMouseEvent *m)//一直跟踪鼠标~~~~~~~~~~~~~~~~~~~~~
{
Mouse_x=m->pos().x();
Mouse_y=m->pos().y();
update();
}

#endif // MOUSEVENTS_H
