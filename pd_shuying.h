#ifndef PD_SHUYING_H
#define PD_SHUYING_H
#include <mainwindow.h>

int MainWindow::pd_shuying(int x,int y)//判断输赢~~~~~~~~~~~~~~~~~~~~~~~
{
  if (pd_ZYsou(x,y)!=0)
  return (qipan [x][y]);
  if (pd_SXsou(x,y)!=0)
  return (qipan [x][y]);
  if (pd_ZXYSsou(x,y)!=0)
  return (qipan [x][y]);
  if (pd_ZSYXsou(x,y)!=0)
  return (qipan [x][y]);
  return (0);
}
int MainWindow::pd_ZYsou(int x,int y)//左右搜索~~~~~~~~~~~~~~~~~~~~~~
{
     int i,j,line_number=1;
     j=qipan [x][y];
     for (i=1;i<=4;i++)//左
     {if (qipan [x-i][y]==j)
      line_number++;
      else
      break;
     }
     x1=qipan_x+qipan_kuan*(x-i+1);//给予划线使用
     y1=qipan_y+qipan_kuan*y;//给予划线使用
     for (i=1;i<=4;i++)//右
     {if (qipan [x+i][y]==j)
      line_number++;
      else
      break;
     }
     x2=qipan_x+qipan_kuan*(x+i-1);//给予划线使用
     y2=qipan_y+qipan_kuan*y;//给予划线使用
     if (line_number>=5)
    {x3=qipan_x+qipan_kuan*x;//给予划线使用
     y3=qipan_y+qipan_kuan*y;//给予划线使用
     Win = true;
      return (j);}
     return (0);
}
int MainWindow::pd_SXsou(int x,int y)//上下搜索~~~~~~~~~~~~~~~~~~~~~~
{
     int i,j,line_number=1;
     j=qipan [x][y];
     for (i=1;i<=4;i++)//上
     {if (qipan [x][y-i]==j)
      line_number++;
      else
      break;
     }
     x1=qipan_x+qipan_kuan*x;//给予划线使用
     y1=qipan_y+qipan_kuan*(y-i+1);//给予划线使用
     for (i=1;i<=4;i++)//下
     {if (qipan [x][y+i]==j)
      line_number++;
      else
      break;
     }
     x2=qipan_x+qipan_kuan*x;//给予划线使用
     y2=qipan_y+qipan_kuan*(y+i-1);//给予划线使用
     if (line_number>=5)
     {x3=qipan_x+qipan_kuan*x;//给予划线使用
      y3=qipan_y+qipan_kuan*y;//给予划线使用
      Win = true;

       return (j);}
     return (0);
}
int MainWindow::pd_ZSYXsou(int x,int y)//左上到右下搜索~~~~~~~~~~~~~~~
{
     int i,j,line_number=1;
     j=qipan [x][y];
     for (i=1;i<=4;i++)//左上
     {if (qipan [x-i][y-i]==j)
      line_number++;
      else
      break;
     }
     x1=qipan_x+qipan_kuan*(x-i+1);//给予划线使用
     y1=qipan_y+qipan_kuan*(y-i+1);//给予划线使用
     for (i=1;i<=4;i++)//右下
     {if (qipan [x+i][y+i]==j)
      line_number++;
      else
      break;
     }
     x2=qipan_x+qipan_kuan*(x+i-1);//给予划线使用
     y2=qipan_y+qipan_kuan*(y+i-1);//给予划线使用
     if (line_number>=5)
     {x3=qipan_x+qipan_kuan*x;//给予划线使用
      y3=qipan_y+qipan_kuan*y;//给予划线使用
      Win = true;
       return (j);}
     return (0);
}int MainWindow::pd_ZXYSsou(int x,int y)//左下到右上搜索~~~~~~~~~~~~~
{
     int i,j,line_number=1;
     j=qipan [x][y];
     for (i=1;i<=4;i++)//左下
     {if (qipan [x-i][y+i]==j)
      line_number++;
      else
      break;
     }
     x1=qipan_x+qipan_kuan*(x-i+1);//给予划线使用
     y1=qipan_y+qipan_kuan*(y+i-1);//给予划线使用
     for (i=1;i<=4;i++)//右上
     {if (qipan [x+i][y-i]==j)
      line_number++;
      else
      break;
     }
     x2=qipan_x+qipan_kuan*(x+i-1);//给予划线使用
     y2=qipan_y+qipan_kuan*(y-i+1);//给予划线使用
     if (line_number>=5)
     {x3=qipan_x+qipan_kuan*x;//给予划线使用
      y3=qipan_y+qipan_kuan*y;//给予划线使用
      Win = true;
       return (j);}
     return (0);
}
bool MainWindow::Is_Win(int x,int y)//判断输赢并对其进行处理
{
    if (pd_shuying(x,y)!=0)//判断输赢并且对输赢后进行处理
    {
      update();
      if (qipan[x][y]==1)
         {if (is_shownumber==false)
          on_shownumber_clicked();
          QMessageBox win (QMessageBox::Information,tr("结果！"),tr("黑棋获胜！"));
          win.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
          win.setButtonText(QMessageBox::Yes,QString("结束游戏"));
          win.setButtonText(QMessageBox::No,QString("预览"));
          ui->message->setText("恭喜黑棋获得胜利");
          if(win.exec()==QMessageBox::Yes)
          {
              if (is_shownumber==true)
              on_shownumber_clicked();
              memset(qipan, 0, 15 * 15 * 4);
              x1=0,x2=0,x3=0,y1=0,y2=0,y3=0,Win=false;
              win_deal();
              update();
              playeroneready=false;
              playertwoready=false;
          }
          else
          {
              ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
              ui->Back->setEnabled(false);
              qDebug ()<<network_Isyou<<"heiqi";
              network_Isyou=false;
              qDebug ()<<network_Isyou;
              playeroneready=false;
              playertwoready=false;
          }

          }
      if (qipan[x][y]==2)
          {if (is_shownumber==false)
           on_shownumber_clicked();
          QMessageBox win (QMessageBox::Information,tr("结果！"),tr("白棋获胜！"));
          win.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
          win.setButtonText(QMessageBox::Yes,QString("结束游戏"));
          win.setButtonText(QMessageBox::No,QString("预览"));
          ui->message->setText("恭喜白棋获得胜利");
          if(win.exec()==QMessageBox::Yes)
          {
              if (is_shownumber==true)
              on_shownumber_clicked();
              memset(qipan, 0, 15 * 15 * 4);
              x1=0,x2=0,x3=0,y1=0,y2=0,y3=0,Win=false;
              win_deal();
              update();
          }
          else
          {
              ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
              ui->Back->setEnabled(false);
              qDebug ()<<network_Isyou<<"baiqi";
              network_Isyou=false;
              qDebug ()<<network_Isyou;
              update();
          }
         }

      return true;
    }
    return false;
}
void MainWindow::win_deal()
{
    if (network_player==1)//服务端对战
    {
        receive_number=0;
        QString sent;
        sent = "keyile";
        socket->write(qPrintable(sent));
        ui->ready->setStyleSheet("border-image: url(:/image/ready-3.png);");
        ui->ready->setEnabled(false);
        deal_networkchongzhi(1);
    }
    if (network_player==2)//客户端对战
    {
        receive_number=0;
        QString sent;
        sent = "keyile";
        socket1->write(qPrintable(sent));
        ui->ready->setStyleSheet("border-image: url(:/image/ready-3.png);");
        ui->ready->setEnabled(false);
        deal_networkchongzhi(2);

    }
    if (network_player==3)//人机对战
    {
        ui->Back->setStyleSheet("border-image: url(:/image/huiqi3.png);");
        Killstart(false);
        Haveddrop=false;
        update();
    }
    if (network_player==0)//人人对战
    {
        Killstart(false);
        Haveddrop=false;
        player=0;
    }
}
#endif // PD_SHUYING_H
