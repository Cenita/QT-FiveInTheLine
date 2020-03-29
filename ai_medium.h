#ifndef AI_MEDIUM_H
#define AI_MEDIUM_H



#include <mainwindow.h>
void MainWindow::medium_ai_search_han()
{//int medium_ai_all[15][15][8][4];用来存储一个方向上四个棋子的数目 【位置】【位置】【方向】【此位置的方向的四个棋位类型】
    for (int a=0;a<=14;a++)//全盘空位搜索
    {
        for (int b=0;b<=14;b++)
        {
         if (qipan[a][b]!=0)
            continue;

                for (int d=1;d<=4;d++)
                {
                        if (a-d<0)//左
                        medium_ai_all[a][b][1][d]=-1;
                        else
                        medium_ai_all[a][b][1][d]=qipan[a-d][b];
                        if (a+d>14)//右
                        medium_ai_all[a][b][2][d]=-1;
                        else
                        medium_ai_all[a][b][2][d]=qipan[a+d][b];
                        if (b-d<0)//上
                        medium_ai_all[a][b][3][d]=-1;
                        else
                        medium_ai_all[a][b][3][d]=qipan[a][b-d];
                        if (b+d>14)//下
                        medium_ai_all[a][b][4][d]=-1;
                        else
                        medium_ai_all[a][b][4][d]=qipan[a][b+d];
                        if (a-d<0||b-d<0)//左上
                        medium_ai_all[a][b][5][d]=-1;
                        else
                        medium_ai_all[a][b][5][d]=qipan[a-d][b-d];
                        if (a+d>14||b+d>14)//右下
                        medium_ai_all[a][b][6][d]=-1;
                        else
                        medium_ai_all[a][b][6][d]=qipan[a+d][b+d];
                        if (a+d>14||b-d<0)//右上
                        medium_ai_all[a][b][7][d]=-1;
                        else
                        medium_ai_all[a][b][7][d]=qipan[a+d][b-d];
                        if (a-d<0||b+d>14)//左下
                        medium_ai_all[a][b][8][d]=-1;
                        else
                        medium_ai_all[a][b][8][d]=qipan[a-d][b+d];

                 }




        }
    }

}
bool MainWindow::medium_ai_judge(int A, int B,int C, int a1, int a2, int a3, int a4, int b1, int b2, int b3, int b4)//数值3不判断
{

         bool left=true,right=true;
         int o=C*2-1,t=C*2;//同一直线上的方向
         int x[6],y[6],a[6],b[6];
         memset(x,0,sizeof(x));
         memset(y,0,sizeof(y));
         memset(a,0,sizeof(a));
         memset(b,0,sizeof(b));
         x[1]=medium_ai_all[A][B][o][1];
         x[2]=medium_ai_all[A][B][o][2];
         x[3]=medium_ai_all[A][B][o][3];
         x[4]=medium_ai_all[A][B][o][4];
         y[1]=medium_ai_all[A][B][t][1];
         y[2]=medium_ai_all[A][B][t][2];
         y[3]=medium_ai_all[A][B][t][3];
         y[4]=medium_ai_all[A][B][t][4];
         a[1]=a1,a[2]=a2,a[3]=a3,a[4]=a4;
         b[1]=b1,b[2]=b2,b[3]=b3,b[4]=b4;
         for (int i=1;i<=4;i++)
         {
             if (a[i]==3)
                 break;
             if (a[i]==x[i])
                 left=true;
             else
             {
                 left=false;
                 break;
             }
         }
         for (int i=1;i<=4;i++)
         {
             if (b[i]==3)
                 break;
             if (b[i]==y[i])
                 right=true;
             else
             {
                 right=false;
                 break;
             }

         }
         if (right==true&&left==true)
         {   if (a1==2&&a2==2&&a3==2)
                 qDebug()<<"X:"<<A<<"Y:"<<B;
             return true;}
         else
             return false;


}
void MainWindow::medium_ai_credit_han()
{
    int df_make5,df_live3,df_live2,df_live1,df_dead1,df_dead2,df_dead3,ec,fc;
    df_make5=100000,df_live3=4300,df_live2=120,df_live1=8,df_dead3=100,df_dead2=10,df_dead1=3;
    int at_make5,at_live3,at_live2,at_live1,at_dead1,at_dead2,at_dead3;
    at_make5=500000,at_live3=5000,at_live2=200,at_live1=7,at_dead3=1300,at_dead2=15,at_dead1=3;
    if (player_who==1)
        ec=1,fc=2;
    if (player_who==2)
        ec=2,fc=1;
    for (int a=0;a<=14;a++)//防守
    {
        for (int b=0;b<=14;b++)
        {

             for (int c=1;c<=4;c++)//普通估计
             {//medium_ai_judge(a,b,c,)==true

                 //死3
                 medium_ai_getcredit(a,b,c,ec,df_dead3,ec,ec,0,3,ec,fc,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead3,ec,0,3,3,ec,ec,fc,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead3,ec,3,3,3,0,ec,ec,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead3,fc,3,3,3,ec,ec,ec,0);
                 medium_ai_getcredit(a,b,c,ec,df_dead3-20,ec,ec,ec,fc,0,3,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead3+10,ec,0,3,3,ec,ec,fc,3);
                 //堵住
                 //成5
                 medium_ai_getcredit(a,b,c,ec,df_make5,ec,3,3,3,ec,ec,ec,3);
                 medium_ai_getcredit(a,b,c,ec,df_make5,ec,ec,3,3,ec,ec,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_make5-20000,ec,ec,ec,ec,3,3,3,3);
                 //活3
                 medium_ai_getcredit(a,b,c,ec,df_live3,ec,ec,ec,0,0,3,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_live3,ec,0,3,3,ec,ec,0,3);
                  //活2
                 medium_ai_getcredit(a,b,c,ec,df_live2,ec,0,3,3,ec,0,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_live2,ec,ec,0,3,0,3,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_live2,ec,ec,0,ec,3,3,3,3);
                   //死2
                 medium_ai_getcredit(a,b,c,ec,df_dead2,0,ec,3,3,0,ec,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,0,0,3,3,ec,ec,fc,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,0,3,3,3,0,ec,ec,fc);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,ec,0,0,3,ec,fc,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,0,3,3,3,ec,0,ec,fc);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,ec,0,3,3,0,ec,fc,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,0,ec,0,3,ec,fc,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,ec,0,ec,fc,3,3,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,ec,3,3,3,0,0,ec,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,0,ec,0,3,ec,0,3,3);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,3,3,3,3,0,ec,ec,0);
                 medium_ai_getcredit(a,b,c,ec,df_dead2,ec,0,ec,0,3,3,3,3);
               //活1
                 medium_ai_getcredit(a,b,c,ec,df_live1,ec,0,0,3,0,0,3,3);
               //防止bug
                 medium_ai_getcredit(a,b,c,ec,1,ec,3,3,3,3,3,3,3);
             //为空位加分


             }

             for (int c=1;c<=3;c++)//多棋性判断
             {
                 for (int d=c+1;d<=4;d++)
                 {
                     if (d==c)
                         continue;



                     if ((medium_ai_getqixing(a,b,c,0,3,3,3,ec,ec,0,3)
                          ||medium_ai_getqixing(a,b,c,ec,0,3,3,ec,0,3,3))
                             &&
                          (medium_ai_getqixing(a,b,d,ec,0,3,3,0,3,3,3)))//活2+活1
                         medium_ai_credit[a][b][ec]+=1000;



                     if ((medium_ai_getqixing(a,b,c,0,3,3,3,ec,ec,0,3)
                         ||medium_ai_getqixing(a,b,c,ec,0,3,3,ec,0,3,3)
                          ||medium_ai_getqixing(a,b,c,ec,ec,0,ec,3,3,3,3))
                            &&
                         (medium_ai_getqixing(a,b,d,0,3,3,3,ec,ec,0,3)
                          ||medium_ai_getqixing(a,b,d,ec,0,3,3,ec,0,3,3)
                          ||medium_ai_getqixing(a,b,d,ec,ec,0,ec,3,3,3,3)))//双活2
                         medium_ai_credit[a][b][ec]+=2000;


                     if ((medium_ai_getqixing(a,b,c,ec,0,3,3,ec,ec,3,3)
                          ||medium_ai_getqixing(a,b,c,ec,3,3,3,ec,ec,0,3)
                          ||medium_ai_getqixing(a,b,c,ec,ec,ec,0,3,3,3,3)
                          ||medium_ai_getqixing(a,b,c,0,ec,ec,ec,3,3,3,3)
                          ||medium_ai_getqixing(a,b,c,ec,ec,ec,3,0,3,3,3))&&
                        (medium_ai_getqixing(a,b,d,0,3,3,3,ec,ec,0,3)
                         ||medium_ai_getqixing(a,b,d,ec,0,3,3,ec,0,3,3)))//3+活2
                         medium_ai_credit[a][b][ec]+=3000;

                     if ((medium_ai_getqixing(a,b,c,ec,ec,ec,3,0,3,3,3)
                          ||medium_ai_getqixing(a,b,c,ec,0,ec,ec,3,3,3,3)
                          ||medium_ai_getqixing(a,b,c,ec,ec,0,ec,3,3,3,3)
                          ||medium_ai_getqixing(a,b,c,ec,ec,ec,0,3,3,3,3)
                          ||medium_ai_getqixing(a,b,c,ec,0,3,3,ec,ec,3,3)
                          ||medium_ai_getqixing(a,b,c,ec,3,3,3,ec,ec,0,3))&&
                        (medium_ai_getqixing(a,b,d,ec,ec,3,3,0,0,3,3)
                         ||medium_ai_getqixing(a,b,d,0,ec,ec,3,0,3,3,3)
                         ||medium_ai_getqixing(a,b,d,0,0,ec,ec,0,3,3,3)
                         ||medium_ai_getqixing(a,b,d,ec,0,3,3,ec,0,3,3)
                         ||medium_ai_getqixing(a,b,d,ec,0,0,3,ec,3,3,3)
                         ||medium_ai_getqixing(a,b,d,ec,0,ec,3,0,3,3,3)
                         ||medium_ai_getqixing(a,b,d,ec,0,ec,0,3,3,3,3)))//死3+死2
                         medium_ai_credit[a][b][ec]+=500;
                  }

             }
        }



    }

    for (int a=0;a<=14;a++)//进攻
    {   //贪心判断

        for (int b=0;b<=14;b++)
        {
            for (int c=1;c<=4;c++)
            {

                //死3
                medium_ai_getcredit(a,b,c,fc,at_dead3-20,0,fc,fc,fc,3,3,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead3,fc,fc,0,3,fc,ec,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead3,fc,0,3,3,fc,fc,ec,3);
                medium_ai_getcredit(a,b,c,fc,at_dead3,fc,3,3,3,0,fc,fc,3);
                medium_ai_getcredit(a,b,c,fc,at_dead3,ec,3,3,3,fc,fc,fc,0);
                medium_ai_getcredit(a,b,c,fc,at_dead3,fc,fc,fc,ec,0,3,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead3,fc,fc,0,fc,3,3,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead3,fc,ec,3,3,fc,0,fc,3);
                medium_ai_getcredit(a,b,c,fc,at_dead3,fc,3,3,3,fc,0,fc,ec);
                //堵住
                //成5
                medium_ai_getcredit(a,b,c,fc,at_make5,fc,3,3,3,fc,fc,fc,3);
                medium_ai_getcredit(a,b,c,fc,at_make5,fc,fc,3,3,fc,fc,3,3);
                medium_ai_getcredit(a,b,c,fc,at_make5,fc,fc,fc,fc,3,3,3,3);
                //活3
                medium_ai_getcredit(a,b,c,fc,at_live3,fc,fc,fc,0,0,3,3,3);
                medium_ai_getcredit(a,b,c,fc,at_live3,fc,0,3,3,fc,fc,0,3);
                medium_ai_getcredit(a,b,c,fc,at_live3,0,fc,0,3,fc,fc,0,3);
                medium_ai_getcredit(a,b,c,fc,at_live3,fc,0,3,3,fc,0,fc,0);
                //活2
                medium_ai_getcredit(a,b,c,fc,at_live2,fc,0,0,3,fc,0,3,3);
                medium_ai_getcredit(a,b,c,fc,at_live2-20,0,fc,fc,0,0,3,3,3);
                medium_ai_getcredit(a,b,c,fc,at_live2,fc,0,3,3,fc,0,0,3);
                medium_ai_getcredit(a,b,c,fc,at_live2,fc,fc,0,0,0,3,3,3);
                medium_ai_getcredit(a,b,c,fc,at_live2,fc,0,fc,0,0,3,3,3);
                //死2
                medium_ai_getcredit(a,b,c,fc,at_dead2,0,fc,3,3,0,fc,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead2,0,0,3,3,fc,fc,ec,3);
                medium_ai_getcredit(a,b,c,fc,at_dead2,fc,0,0,3,fc,ec,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead2,0,3,3,3,fc,0,fc,ec);
                medium_ai_getcredit(a,b,c,fc,at_dead2,fc,0,3,3,0,fc,ec,3);
                medium_ai_getcredit(a,b,c,fc,at_dead2,0,fc,0,3,fc,ec,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead2,fc,0,fc,0,3,3,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead2,fc,3,3,3,0,0,fc,3);
                medium_ai_getcredit(a,b,c,fc,at_dead2,fc,0,0,fc,3,3,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead2,fc,0,fc,0,3,3,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead2,fc,fc,0,ec,3,3,3,3);
                medium_ai_getcredit(a,b,c,fc,at_dead2,0,fc,fc,ec,3,3,3,3);
                //活1
                medium_ai_getcredit(a,b,c,fc,at_live1,fc,0,3,3,0,3,3,3);

                //死1
                medium_ai_getcredit(a,b,c,fc,at_dead1,fc,ec,3,3,0,3,3,3);

            }
            for (int c=1;c<=3;c++)//多棋性判断
            {
                for (int d=c+1;d<=4;d++)
                {
                    if (d==c)
                        continue;
                    //双活2
                    {if ((medium_ai_getqixing(a,b,c,0,3,3,3,fc,fc,0,3)
                          ||medium_ai_getqixing(a,b,c,fc,0,3,3,fc,0,3,3))
                           &&
                         (medium_ai_getqixing(a,b,d,0,3,3,3,fc,fc,0,3)
                         ||medium_ai_getqixing(a,b,d,fc,0,3,3,fc,0,3,3)))//双活2
                           medium_ai_credit[a][b][fc]+=2000;}
                    //3+活2
                    {if ((medium_ai_getqixing(a,b,c,fc,fc,fc,0,3,3,3,3)
                          ||medium_ai_getqixing(a,b,c,fc,fc,fc,3,0,3,3,3)
                          ||medium_ai_getqixing(a,b,c,fc,fc,0,fc,3,3,3,3))&&
                        (medium_ai_getqixing(a,b,d,0,3,3,3,fc,fc,0,3)
                         ||medium_ai_getqixing(a,b,d,fc,0,3,3,fc,0,3,3)))//3+活2
                        medium_ai_credit[a][b][fc]+=at_live3;}
                    //活2+活1
                    {if ((medium_ai_getqixing(a,b,c,0,3,3,3,fc,fc,0,3)
                          ||medium_ai_getqixing(a,b,c,fc,0,3,3,fc,0,3,3))
                             &&
                          (medium_ai_getqixing(a,b,d,fc,0,0,3,0,3,3,3)
                           ||medium_ai_getqixing(a,b,d,fc,0,3,3,0,0,3,3)))//活2+活1
                         medium_ai_credit[a][b][fc]+=1000;}
                    //活1+活1
                    {if (medium_ai_getqixing(a,b,c,fc,0,0,3,0,0,3,3)

                          &&
                         medium_ai_getqixing(a,b,d,fc,0,0,3,0,0,3,3)
                         )//活1+活1
                         medium_ai_credit[a][b][fc]+=150;}
                }

          }
        }
    }
}
void MainWindow::medium_ai_getcredit(int A, int B, int C,int D,int E, int a1, int a2, int a3, int a4, int b1, int b2, int b3, int b4)
{//AB是该棋子坐标C是该棋子方向D是该棋子属于那种类型E是给予的分数 后面就是坐标数
    if (medium_ai_judge(A,B,C,a1,a2,a3,a4,b1,b2,b3,b4)==true
       ||medium_ai_judge(A,B,C,b1,b2,b3,b4,a1,a2,a3,a4)==true)
    {medium_ai_credit[A][B][D]+=E;
    }
}
bool MainWindow::medium_ai_getqixing(int A, int B, int C, int a1, int a2, int a3, int a4, int b1, int b2, int b3, int b4)
{
    if (medium_ai_judge(A,B,C,a1,a2,a3,a4,b1,b2,b3,b4)==true
       ||medium_ai_judge(A,B,C,b1,b2,b3,b4,a1,a2,a3,a4)==true)
       {return true;}
    else
        return false;
}
void MainWindow::medium_ai_down()
{

 memset(medium_ai_all,0,sizeof (medium_ai_all));
 memset(medium_ai_credit,0,sizeof (medium_ai_credit));
 medium_ai_search_han();
 medium_ai_credit_han();
 for (int a=0;a<=14;a++)
 {
     for (int b=1;b<=2;b++)
     {
         medium_ai_credit[0][a][b]-=1;
         medium_ai_credit[14][a][b]-=1;
         medium_ai_credit[a][14][b]-=1;
         medium_ai_credit[14][0][b]-=1;
     }
 }


 int big_x=-1,big_y=-1,big_credit=0;
 for (int a=0;a<=14;a++)
 {   for (int b=0;b<=14;b++)
    {   if (qipan[a][b]!=0)
          continue;
           for (int c=1;c<=2;c++){
            if (medium_ai_credit[a][b][1]+medium_ai_credit[a][b][2]>big_credit)
            {

                big_credit=medium_ai_credit[a][b][1]+medium_ai_credit[a][b][2];
                big_x=a;
                big_y=b;

            }

          }

     }
 }
 for (int a=0;a<=14;a++)
 {
     for (int b=0;b<=14;b++)
     {
         qDebug ()<<a<<b<<medium_ai_credit[a][b][1]<<medium_ai_credit[a][b][2]<<medium_ai_credit[a][b][2]+medium_ai_credit[a][b][1];

     }
 }
 qDebug()<<"big_credit"<<big_credit<<"x"<<big_x<<"y"<<big_y;
 qDebug ()<<"1:"<<medium_ai_credit[big_x][big_y][1];
 qDebug ()<<"2:"<<medium_ai_credit[big_x][big_y][2];

if (big_x!=-1&&big_y!=-1)
{

    if (player_who==1)
    {
     qipan[big_x][big_y]=2;
    }
    if (player_who==2)
    qipan[big_x][big_y]=1;
    back_number++;
    back_number_use=back_number;
    back_qipan[back_number][1]=big_x;
    back_qipan[back_number][2]=big_y;
    medium_ai_last[1]=big_x;
    medium_ai_last[2]=big_y;
    Is_Win(big_x,big_y);
    update();
}
else
{
    if (is_shownumber==false)
    on_shownumber_clicked();
    QMessageBox::information(this, tr("结果！"), tr("平局"));
    if (is_shownumber==true)
    on_shownumber_clicked();
    memset(qipan, 0, 15 * 15 * 4);
    x1=0,x2=0,x3=0,y1=0,y2=0,y3=0,Win=false;
    Killstart(false);
    Haveddrop=false;
    update();

}


}
#endif // AI_MEDIUM_H
////////*******/////////////
