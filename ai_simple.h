#ifndef MEDIUM_AI_H
#define MEDIUM_AI_H
#include <mainwindow.h>
void MainWindow::simple_ai_search_han()
{
    for (int a=0;a<=14;a++)//黑棋搜索
    {
     for (int b=0;b<=14;b++)
     {
        if (qipan[a][b]==0)
        {

            int i=1;
            //横 ————————————————————————————
            while (qipan[a+i][b]==1 && a+i<=14 )//横
            {

                simple_ai_Cqizinumber[a][b][1][1]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a+i][b][1][1]=qipan[a+i][b];
            }
            i=1;
            while (qipan[a-i][b]==1 && a-i>=0 )
            {
                simple_ai_Cqizinumber[a][b][1][1]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a-i][b][1][2]=qipan[a-i][b];
            }
            i=1;
            //竖——————————————————————————————
            while (qipan[a][b+i]==1 && b+i<=14)
            {
                simple_ai_Cqizinumber[a][b][1][2]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a][b+i][1][3]=qipan[a][b+i];
            }
            i=1;
            while (qipan[a][b-i]==1 && b-i>=0)
            {
                simple_ai_Cqizinumber[a][b][1][2]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a][b-i][1][4]=qipan[a][b-i];
            }
            i=1;
            //左上右下————————————————————————
            while (qipan[a-i][b-i]==1 && a-i>=0 && b-i>=0)
            {
                simple_ai_Cqizinumber[a][b][1][3]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a-i][b-i][1][5]=qipan[a-i][b-i];
            }
            i=1;
            while (qipan[a+i][b+i]==1 && a+i<=14 && b+i<=14)
            {
                simple_ai_Cqizinumber[a][b][1][3]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a+i][b+i][1][6]=qipan[a+i][b+i];
            }
            i=1;
            //左下右上——————————————————————————————————
            while (qipan[a-i][b+i]==1 && a-i>=0 && b+i<=14)
            {
               simple_ai_Cqizinumber[a][b][1][4]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a-i][b+i][1][7]=qipan[a-i][b+i];
            }
            i=1;
            while (qipan[a+i][b-i]==1 && a+i<=14 && b-i>=0)
            {
                simple_ai_Cqizinumber[a][b][1][4]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a+i][b-i][1][8]=qipan[a+i][b+i];
            }
            i=1;


        }
     }
    }
    for (int a=0;a<=14;a++)//白棋搜索
    {
     for (int b=0;b<=14;b++)
     {
        if (qipan[a][b]==0)
        {

            int i=1;
            //横 ————————————————————————————

            while (qipan[a+i][b]==2 && a+i<=14 )//横
            {
                simple_ai_Cqizinumber[a][b][2][1]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a+i][b][2][1]=qipan[a+i][b];
            }
            i=1;
            while (qipan[a-i][b]==2 && a-i>=0 )
            {
                simple_ai_Cqizinumber[a][b][2][1]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a-i][b][2][2]=qipan[a-i][b];
            }
            i=1;
            //竖——————————————————————————————
            while (qipan[a][b+i]==2 && b+i<=14)
            {
                simple_ai_Cqizinumber[a][b][2][2]++;
                i++;
                if (i==4)
                   simple_ai_livethree[a][b+i][2][3]=qipan[a][b+i];
            }
            i=1;
            while (qipan[a][b-i]==2 && b-i>=0)
            {
                simple_ai_Cqizinumber[a][b][2][2]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a][b-i][2][4]=qipan[a][b-i];
            }
            i=1;
            //左上右下————————————————————————
            while (qipan[a-i][b-i]==2 && a-i>=0 && b-i>=0)
            {
                simple_ai_Cqizinumber[a][b][2][3]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a-i][b-i][2][5]=qipan[a-i][b-i];
            }
            i=1;
            while (qipan[a+i][b+i]==2 && a+i<=14 && b+i<=14)
            {
                simple_ai_Cqizinumber[a][b][2][3]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a+i][b+i][2][6]=qipan[a+i][b+i];
            }
            i=1;
            //左下右上——————————————————————————————————
            while (qipan[a-i][b+i]==2 && a-i>=0 && b+i<=14)
            {
                simple_ai_Cqizinumber[a][b][2][4]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a-i][b+i][2][7]=qipan[a-i][b+i];
            }
            i=1;
            while (qipan[a+i][b-i]==2 && a+i<=14 && b-i>=0)
            {
                simple_ai_Cqizinumber[a][b][2][4]++;
                i++;
                if (i==4)
                    simple_ai_livethree[a+i][b-i][2][8]=qipan[a+i][b-i];
            }
            i=1;


        }
     }
    }
}
void MainWindow::simple_ai_credit_han()
{

    for (int a=0;a<=14;a++)//黑棋打分
    {
        for (int b=0;b<=14;b++)
            for (int c=1;c<=4;c++)
            {
                if (qipan[a][b]!=0)
                    continue;
                if (simple_ai_Cqizinumber[a][b][1][c]>=4&&simple_ai_Cqizinumber[a][b][1][c]<=8)
                   {simple_ai_credit[a][b][1]+=10000000;}
                else if (simple_ai_Cqizinumber[a][b][1][c]==3)
                    {
                            for (int z=0;z<=8;z++)
                            {
                                if (simple_ai_livethree[a][b][1][z]==0)
                                {
                                    simple_ai_credit[a][b][1]+=200000;
                                }
                            }
                        simple_ai_credit[a][b][1]+=200000;
                    }
                else if (simple_ai_Cqizinumber[a][b][1][c]==2)
                   {
                    simple_ai_credit[a][b][1]+=1000;}
                else if (simple_ai_Cqizinumber[a][b][1][c]==1)
                     {
                    simple_ai_credit[a][b][1]+=10;}
            }
    }
    for (int a=0;a<=14;a++)//白棋打分
    {
        for (int b=0;b<=14;b++)
            for (int c=1;c<=4;c++)
            {
                if (qipan[a][b]!=0)
                    continue;
                if (simple_ai_Cqizinumber[a][b][2][c]>=4&&simple_ai_Cqizinumber[a][b][2][c]<=8)
                   {
                    simple_ai_credit[a][b][2]+=1000000000;
                    }
                else if (simple_ai_Cqizinumber[a][b][2][c]==3)
                    {
                          for (int z=0;z<=8;z++)
                          {
                             if (simple_ai_livethree[a][b][2][z]==0)
                             {
                               simple_ai_credit[a][b][2]+=1000000;
                             }
                          }
                          simple_ai_credit[a][b][2]+=1000000;

                    }
                else if (simple_ai_Cqizinumber[a][b][2][c]==2)
                   {
                    simple_ai_credit[a][b][2]+=1000;
                    }
                else if (simple_ai_Cqizinumber[a][b][2][c]==1)
                     {
                    simple_ai_credit[a][b][2]+=10;
                    }
            }
    }
}
void MainWindow::simple_ai_down()
{
    memset(simple_ai_livethree,5,sizeof (simple_ai_livethree));
    memset(simple_ai_Cqizinumber, 0, sizeof(simple_ai_Cqizinumber));
    memset(simple_ai_credit,0,sizeof (simple_ai_credit));
    simple_ai_search_han();
    simple_ai_credit_han();
    int big_x=0,big_y=0,big_credit=0;
    for (int a=0;a<=14;a++)
    {   for (int b=0;b<=14;b++)
       {   if (qipan[a][b]!=0)
             continue;
           if(a==14&&b==14)
             continue;
           for (int c=1;c<=2;c++)
            {

               if (simple_ai_credit[a][b][c]>big_credit)
               {

                   big_credit=simple_ai_credit[a][b][c];
                   big_x=a;
                   big_y=b;


               }
            }
       }
    }
    if (player_who==1)
    qipan[big_x][big_y]=2;
    if (player_who==2)
    qipan[big_x][big_y]=1;
    qDebug ()<<"xia"<<big_credit<<"x"<<big_x<<"y"<<big_y;
    back_number++;
    back_number_use=back_number;
    back_qipan[back_number][1]=big_x;
    back_qipan[back_number][2]=big_y;
    medium_ai_last[1]=big_x;
    medium_ai_last[2]=big_y;
    Is_Win(big_x,big_y);
    update();
}


#endif // MEDIUM_AI_H
