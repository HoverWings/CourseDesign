﻿#include"PersonalTrip.h"
#include"mainwindow.h"


p_Route hRoute=NULL;


bool creatRoute()//初始化链表
{
    hRoute=(p_Route)malloc(sizeof(Route));
    hRoute->nextRoute=NULL;
    return true;
}

bool insertRoute(p_Route* curRoute) //当前节点
{
    if(hRoute==NULL)
    {
        creatRoute();
        hRoute = *curRoute;
        (*curRoute)->nextRoute = NULL;
        (*curRoute)->hDayInfo = NULL;
        return true;
    }
    p_Route pre=NULL;
    p_Route tail = NULL;
    if(findRouteByNum(*curRoute,&pre,&tail))//通过行程编号删除
    {
        QMessageBox msgBox;
        msgBox.setText("当前节点已经存在");
        msgBox.setInformativeText("请直接修改");
        msgBox.exec();
        return false;
    }
    else
    {
        (tail)->nextRoute=*curRoute;
        (*curRoute)->nextRoute= NULL;
        (*curRoute)->hDayInfo = NULL;
    }
    return true;
}
//查找当前链表的前置位 然后插入

bool deleteRoute(int routeNum)//reuturn 的问题
{
    p_Route p = hRoute;
    if (p == NULL)
    {
         return false;
    }
    if (p->routeNum == routeNum)//头节点情况下
    {
        hRoute = p->nextRoute; //一级节点指针处理
        //处理二级节点
        p_DayInfo p2 = p->hDayInfo;
        p_DayInfo temp2;
        while (p2 != NULL)
        {
            temp2 = p2;

            //处理三级节点
            p_DayEXPInfo p3=p2->hDayEXPInfo;
            p_DayEXPInfo temp3;
            while (p3 != NULL)
            {
                temp3 = p3;
                p3 = p3->nextDayEXPInfo;
                free(temp3);
            }
            p2 = p2->nextDayInfo;
            free(temp2);

        }
        free(p);
        return true;
    }
    else
    {
        p_Route pre;
        while (p->routeNum!=routeNum)
        {
            pre = p;//记录p的前驱
            p = p->nextRoute;
            if (p == NULL)
            {
                return false;//没有找到
            }
        }
        pre->nextRoute = p->nextRoute;//一级节点指针处理
        //二级节点处理
        p_DayInfo p2 = p->hDayInfo;
        p_DayInfo temp2;
        while (p2 != NULL)
        {
            temp2 = p2;

            //处理三级节点
            p_DayEXPInfo p3 = p2->hDayEXPInfo;
            p_DayEXPInfo temp3;
            while (p3 != NULL)
            {
                temp3 = p3;
                p3 = p3->nextDayEXPInfo;
                free(temp3);
            }
            p2 = p2->nextDayInfo;
            free(temp2);

        }
        free(p);
        return true;

    }
}


//通过行程编号找到
bool findRouteByNum(p_Route cur,p_Route* pre, p_Route* tail)//cur为需要查找是否重复的节点 pre用来记录前驱 tail用来记录整个链表尾部 返回的bool
{
    p_Route p=hRoute;//指向头结点 默认不为空的额情况下来找
    *tail=p;//记录p的前驱
    while (p != NULL)//需要改变指针的指向 需要传二级指针
    {
        if (p->routeNum==cur->routeNum)
        {
            *pre=*tail;
            return true;
        }
        *tail=p;//记录p的前驱
        p = p->nextRoute;//NULL这里出的问题
    }
    return false;
}

p_Route findRouteByNum(int num)//返回所要找的route 用于查询
{
    p_Route p = hRoute;//指向头结点 默认不为空的额情况下来找
    while (p != NULL)//需要改变指针的指向 需要传二级指针
    {
        if (p->routeNum == num)
        {
            return p;
        }
        p = p->nextRoute;
    }
    return NULL;
}

bool printRoute()
{
    p_Route p=hRoute;
    if(hRoute==NULL)
    {
        return false;
    }
    else
    {
        p = p->nextRoute;
        while (p != NULL)
        {

            printf("%d\n", p->routeNum);
            p = p->nextRoute;
        }
        return true;
    }
}



bool findDayInfoByOrder(p_Route route, p_DayInfo cur, p_DayInfo* pre, p_DayInfo* tail)//删除第几天
{
    if (route == NULL)
    {
        printf("一级节点不存在");
        return false;
    }
    if (route->hDayInfo == NULL)
    {
        printf("二级链表为空");
    }
    p_DayInfo p = route->hDayInfo;
    while (p != NULL)//需要改变指针的指向 需要传二级指针
    {
        if (p->order==cur->order)
        {
            *pre = *tail;
            return true;
        }
        *tail = p;//记录p的前驱
        p = p->nextDayInfo;
    }
    return false;
}

bool insertDayInfo(p_Route* route, p_DayInfo* cur)
{
    p_DayInfo p = (*route)->hDayInfo;
    if (p == NULL)
    {
        (*route)->hDayInfo = *cur;
        (*cur)->nextDayInfo = NULL;
        (*cur)->hDayEXPInfo = NULL;
        return true;
    }
    p_DayInfo pre=(*route)->hDayInfo;//改变这两个
    p_DayInfo tail=(*route)->hDayInfo;
    if (findDayInfoByOrder(*route, *cur, &pre, &tail))
    {
        //是否覆盖
        QMessageBox msgBox;
        msgBox.setText("当前节点已经存在");
        msgBox.setInformativeText("请直接修改");
        msgBox.exec();
        return false;
    }
    else
    {
        (tail)->nextDayInfo = *cur;
        (*cur)->nextDayInfo = NULL;
        (*cur)->hDayEXPInfo = NULL;
        return true;
    }

}

bool insertDayInfo(p_DayInfo* cur)
{
    p_Route p1 = findRouteByNum((*cur)->routeNum);
    if(p1==NULL)
    {
        return false;
    }
    p_DayInfo p2=p1->hDayInfo;
    if (p2 == NULL)
    {
        p1->hDayInfo = *cur;//改变的是p1；
        p2=p1->hDayInfo;
        (*cur)->nextDayInfo = NULL;
        (*cur)->hDayEXPInfo = NULL;
        return true;
    }
    p_DayInfo pre=p1->hDayInfo;//改变这两个
    p_DayInfo tail=p1->hDayInfo;
    if (findDayInfoByOrder(p1, *cur, &pre, &tail))
    {
        //如果找到是否覆盖
        QMessageBox msgBox;
        msgBox.setText("当前节点已经存在");
        msgBox.setInformativeText("请直接修改");
        msgBox.exec();
        return false;
    }
    else
    {
        (tail)->nextDayInfo = *cur;
        (*cur)->nextDayInfo = NULL;
        (*cur)->hDayEXPInfo = NULL;
        return true;
    }
}


bool printDayInfo(p_Route route)
{
    if (route == NULL)
    {
        printf("Error\n");
        return false;
    }
    if (route->hDayInfo == NULL)
    {
        printf("Error\n");
        return false;
    }
    p_DayInfo p = route->hDayInfo;
    while (p!=NULL)
    {
        printf("%d",p->order);
        p = p->nextDayInfo;
        if (p != NULL)
        {
            printf("->");
        }
    }
    printf("\n");
    return true;

}

p_DayInfo findDayInfoByOrder(p_Route* route, int order)// 二级链表 通过和行程编号序号找到 用于查询
{
    if (*route == NULL)
    {
        return NULL;
    }
    if ((*route)->hDayInfo == NULL)
    {
        return NULL;
    }
    p_DayInfo p = (*route)->hDayInfo;
    while (p!=NULL)
    {
        if (p->order == order)
        {
            return p;
        }
        p = p->nextDayInfo;
    }
    return NULL;
}

p_DayInfo findDayInfoByOrder(int routeNum, int order)// 二级链表 通过和行程编号序号找到 用于查询
{
    p_Route route = findRouteByNum(routeNum);
    if (route == NULL)
    {
        return NULL;
    }
    p_DayInfo dayinfo = findDayInfoByOrder(&route, order);
    if (dayinfo == NULL)
    {
        return NULL;
    }
    return dayinfo;
}

bool deleteDayInfo(int routeNum, int order)//单个删除
{
    //我要找前驱
    p_Route route = findRouteByNum(routeNum);
    if (route == NULL)
    {
        return NULL;
    }
    p_DayInfo p = route->hDayInfo;
    if (p->order == order)//删除头结点
    {
        if (p->nextDayInfo == NULL)
        {
            route->hDayInfo = NULL;
            //处理三级节点
            p_DayEXPInfo temp;
            p_DayEXPInfo p3;
            p3 = p->hDayEXPInfo;
            while (p3 != NULL)
            {
                temp = p3;                    //那么它存在的必要是什么呢？
                p3 = p3->nextDayEXPInfo;
                free(temp);
            }
            free(p);
            return true;
        }
        else
        {
            route->hDayInfo = p->nextDayInfo;
            //处理三级节点
            p_DayEXPInfo temp;
            p_DayEXPInfo p3;
            p3 = p->hDayEXPInfo;
            while (p3 != NULL)
            {
                temp = p3;                    //那么它存在的必要是什么呢？
                p3 = p3->nextDayEXPInfo;
                free(temp);
            }
            free(p);
            return true;
        }
    }
    else
    {
        p_DayInfo pre;
        while (p->order != order)
        {
            if (p->nextDayInfo == NULL)
            {
                return false;//没找到
            }
            pre = p;//记录前驱
            p = p->nextDayInfo;
        }
        pre->nextDayInfo = p->nextDayInfo;

        //处理三级节点
        p_DayEXPInfo temp;
        p_DayEXPInfo p3;
        p3 = p->hDayEXPInfo;
        while (p3 != NULL)
        {
            temp = p3;                    //那么它存在的必要是什么呢？
            p3 = p3->nextDayEXPInfo;
            free(temp);
        }

        free(p);
        return true;
    }
}


bool insertDayEXPInfo(p_Route* route, p_DayInfo* dayinfo, p_DayEXPInfo* cur)//需要写一些重载
{
    if (*dayinfo == NULL)
    {
        return false;
    }
    if ((*dayinfo)->hDayEXPInfo == NULL)
    {
        (*dayinfo)->hDayEXPInfo = *cur;
        (*cur)->nextDayEXPInfo = NULL;
        return true;
    }
    p_DayEXPInfo pre;//改变这两个
    p_DayEXPInfo tail;
    if (findDayEXPInfoByserialNum(*dayinfo, *cur, &pre, &tail))
    {
        //是否覆盖
        QMessageBox msgBox;
        msgBox.setText("当前节点已经存在");
        msgBox.setInformativeText("请直接修改");
        msgBox.exec();
        return false;
    }
    else
    {
        tail->nextDayEXPInfo = *cur;
        (*cur)->nextDayEXPInfo = NULL;
        return true;
    }

}


bool findDayEXPInfoByserialNum(p_DayInfo dayinfo, p_DayEXPInfo cur, p_DayEXPInfo* pre, p_DayEXPInfo* tail)//用于插入和删除
{
    if (dayinfo == NULL)
    {
        printf("");
        return false;
    }
    if (dayinfo->hDayEXPInfo == NULL)//判定不为空才找的
    {
        printf("三级链表为空");
    }
    p_DayEXPInfo p = dayinfo->hDayEXPInfo;
    while (p != NULL)//需要改变指针的指向 需要传二级指针
    {
        if (p->serialNum == cur->serialNum)
        {
            *pre = *tail;
            return true;
        }
        *tail = p;//记录p的前驱
        p = p->nextDayEXPInfo;
    }
    return false;
}


p_DayEXPInfo findDayEXPInfoByserialNum(int routeNum,int order,int serialNum)//用于查询
{
    p_Route route = findRouteByNum(routeNum);
    if (route == NULL)
    {
        return NULL;
    }
    p_DayInfo dayinfo = findDayInfoByOrder(&route, order);
    if (dayinfo == NULL)
    {
        return NULL;
    }
    p_DayEXPInfo p = dayinfo->hDayEXPInfo;
    while (p != NULL)//需要改变指针的指向 需要传二级指针
    {
        if (p->serialNum == serialNum)
        {
            return p;
        }
        p = p->nextDayEXPInfo;
    }
    return NULL;
}

bool printDayEXPInfo(int routeNum, int order, int serialNum)//打印三级链表
{
    p_DayEXPInfo p = findDayEXPInfoByserialNum(routeNum, order, serialNum);
    if (p == NULL)
    {
        return false;
    }
    //输出信息
    printf("%d\n", p->routeNum);
    printf("%d\n", p->order);
    printf("%d\n", p->serialNum);
    return true;
}

bool deleteDayEXPInfo(int routeNum, int order, int serialNum)//单个删除
{
    //我要找前驱
    p_Route route = findRouteByNum(routeNum);
    if (route == NULL)
    {
        return NULL;
    }
    p_DayInfo dayinfo = findDayInfoByOrder(&route, order);
    if (dayinfo == NULL)
    {
        return NULL;
    }
    p_DayEXPInfo p = dayinfo->hDayEXPInfo;
    if (p->serialNum == serialNum)//删除头结点
    {
        if (p->nextDayEXPInfo == NULL)
        {
            dayinfo->hDayEXPInfo = NULL;
            free(p);
        }
        else
        {
            dayinfo->hDayEXPInfo = p->nextDayEXPInfo;
            free(p);
        }
        return true;
    }
    else
    {
        p_DayEXPInfo pre;
        while (p->serialNum != serialNum)
        {
            if (p->nextDayEXPInfo != NULL)
            {
                return false;
            }
            pre = p;//记录前驱
            p = p->nextDayEXPInfo;
        }
        pre->nextDayEXPInfo = p->nextDayEXPInfo;
        free(p);
        return true;
    }
}


bool printAll()
{
    p_Route p1= hRoute;
    if (hRoute == NULL)
    {
        return false;
    }
    while (p1!=NULL)
    {
        printf("%d\n",p1->routeNum);
        p_DayInfo p2 = p1->hDayInfo;
        while (p2!=NULL)
        {
            printf("\t%d\n", p2->order);
            p_DayEXPInfo p3 = p2->hDayEXPInfo;
            while (p3 != NULL)
            {
                printf("\t\t%d\n", p3->serialNum);
                p3 = p3->nextDayEXPInfo;
            }
            p2 = p2->nextDayInfo;
        }
        p1 = p1->nextRoute;
    }
    return true;
}

//再封装一次
bool insertDayEXPInfo(p_DayEXPInfo* cur)
{
    p_Route p1 = findRouteByNum((*cur)->routeNum);
    if (p1 == NULL)
    {
        return false;
    }
    p_DayInfo p2 = findDayInfoByOrder(&p1,(*cur)->order);
    if (p2 == NULL)
    {
        return false;
    }
    if (insertDayEXPInfo(&p1,&p2, cur))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool saveToFile()
{
    FILE *out1, *out2, *out3;
    p_Route p1 = hRoute;// load head node
    p_DayInfo p2 = NULL;
    p_DayEXPInfo p3 = NULL;
    if ((out1 = fopen("Data\\Route.dat", "wb")) == NULL)
        return false;
    if ((out2 = fopen("Data\\DayInfo.dat", "wb")) == NULL)
        return false;
    if ((out3 = fopen("Data\\DayEXPInfo.dat", "wb")) == NULL)
        return false;
    while (p1 != NULL)
    {
        fwrite(p1, sizeof(Route), 1, out1);
        p2 = p1->hDayInfo;
        while (p2)
        {
            fwrite(p2, sizeof(DayInfo), 1, out2);
            p3 = p2->hDayEXPInfo;
            while (p3)
            {
                fwrite(p3, sizeof(DayEXPInfo), 1, out3);
                p3 = p3->nextDayEXPInfo;
            }
            p2 = p2->nextDayInfo;
        }
        p1 = p1->nextRoute;
    }
    fclose(out1);
    fclose(out2);
    fclose(out3);
    return true;
}

bool loadFromFile()
{
    FILE*in1, *in2, *in3;
    p_Route  p1 = NULL;
    p_DayInfo p2;
    p_DayEXPInfo p3;
    if ((in1 = fopen("Data\\Route.dat", "rb")) == NULL)
        return false;
    if ((in2 = fopen("Data\\DayInfo.dat", "rb")) == NULL)
        return false;
    if ((in3 = fopen("Data\\DayExpInfo.dat", "rb")) == NULL)
        return false;
    p_Route pre_p1=NULL;
    bool isFirst=true;
    while (!feof(in1))//load the first-class list
    {
        if(isFirst)
        {
            p1 = (p_Route)malloc(sizeof(Route));
            p1->routeNum=-1;
            fread(p1, sizeof(Route), 1, in1);
            if(p1->routeNum==-1)
            {
                free(p1);
                break;
            }
            p1->hDayInfo=NULL;
            p1->nextRoute = NULL;
            hRoute=p1;// the head pointer is aimed at the p1
            pre_p1=p1;
            isFirst=false;
        }
        else
        {
            p_Route p1 = (p_Route)malloc(sizeof(Route));
            p1->routeNum=-1;
            fread(p1, sizeof(Route), 1, in1);
            if(p1->routeNum==-1)
            {
                free(p1);
                break;
            }
            p1->hDayInfo=NULL;
            p1->nextRoute = NULL;
            pre_p1->nextRoute=p1;
            pre_p1=p1;
        }
    }

    while (!feof(in2))/*将存储站点链的文件调入内存*/
    {
        p2 = (p_DayInfo)malloc(sizeof(DayInfo));
        p2->order=-1;
        fread(p2, sizeof(DayInfo), 1, in2);
        if(p2->order==-1)
        {
            free(p2);
            break;
        }
        p2->nextDayInfo=NULL;
        p2->hDayEXPInfo=NULL;
        p1=hRoute;
        while (p1 != NULL)
        {
            if (p1->routeNum==p2->routeNum)
            {
               if(p1->hDayInfo==NULL)
               {
                   p1->hDayInfo=p2;
                   break;
               }
               else
               {
                   p_DayInfo tp2=p1->hDayInfo;
                   p_DayInfo pre=p1->hDayInfo;
                   while(tp2->nextDayInfo!=NULL)
                   {
                       pre=tp2;
                       tp2=tp2->nextDayInfo;
                   }
                    pre->nextDayInfo=p2;
                    break;
               }
            }
            else
            {
                p1=p1->nextRoute;
            }
        }
    }

    while (!feof(in3))/*将存储车辆信息链的文件调入内存*/
    {
        p3 = (p_DayEXPInfo)malloc(sizeof(DayEXPInfo));
        p3->serialNum=-1;
        fread(p3, sizeof(DayEXPInfo), 1, in3);
        if(p3->serialNum==-1)
        {
            free(p3);
            break;
        }
        p3->nextDayEXPInfo=NULL;
        p1=hRoute;
        while (p1 != NULL)
        {
            if (p1->routeNum==p3->routeNum)
            {
                p_DayInfo tp2=p1->hDayInfo;
                if(tp2->order==p3->order)
                {
                    p_DayEXPInfo tp3=tp2->hDayEXPInfo;
                    if(tp3==NULL)
                    {
                           tp2->hDayEXPInfo=p3;
                           break;
                    }
                    else
                    {
                          if(tp3->nextDayEXPInfo==NULL)
                          {
                                tp3->nextDayEXPInfo=p3;
                          }
                          else
                          {
                              p_DayEXPInfo pre=NULL;
                                while(tp3->nextDayEXPInfo!=NULL)
                                {
                                    pre=tp3;
                                    tp3=tp3->nextDayEXPInfo;

                                }
                                pre->nextDayEXPInfo=p3;
                                 break;
                          }
                    }


                }
                else
                {
                    tp2=tp2->nextDayInfo;
                    if(tp2==NULL)
                    {
                        return false;
                    }
                }

            }
            p1=p1->nextRoute;
        }

    }
    return true;
}


p_DayInfo findTransInfoByScene(char Scene[50])
{
    p_Route p1=hRoute;
    if(hRoute==NULL)
    {
        return NULL;
    }
    while(p1!=NULL)
    {
        p_DayInfo p2=p1->hDayInfo;
        while(p2!=NULL)
        {
            if(strcmp(p2->morningScene, Scene)==0||strcmp(p2->afternoonScene, Scene)==0)
            {
                return p2;
            }
            p2=p2->nextDayInfo;
        }
        p1=p1->nextRoute;
    }
    return NULL;
}

float findEXPByResidence(char Residence[50])
{
    p_Route p1=hRoute;
    float residenceEXP=-1;
    if(hRoute==NULL)
    {
        return residenceEXP;
    }
    while(p1!=NULL)
    {
        p_DayInfo p2=p1->hDayInfo;
        while(p2!=NULL)
        {
            if(strcmp(p2->residence, Residence)==0)
            {
                p_DayEXPInfo p3=p2->hDayEXPInfo;
                while(p3!=NULL)
                {
                    if(strcmp(p3->TxKind, "住宿")==0)
                    {
                         residenceEXP+=p3->TxAmount;
                    }
                    p3=p3->nextDayEXPInfo;
                }

            }
            p2=p2->nextDayInfo;
        }
        p1=p1->nextRoute;
    }
    return residenceEXP;
}


bool sortByRouteNum()//quick sort
{
    p_Route p1=hRoute;
    p_Route pre_p1=hRoute;
    if(p1==NULL)
    {
        return false;
    }
    while(p1->nextRoute != NULL)
    {
        p_Route p;
        p_Route pt=p1->nextRoute;
        if((p1->routeNum)>(pt->routeNum))
        {
            p_Route p2=p1->nextRoute;
            p_Route p3=p1->nextRoute;
            pre_p1->nextRoute=p2;
            p2->nextRoute=p1;
            p1->nextRoute=p3;
            pre_p1=p2;
        }
        p1=p1->nextRoute;  //p再前进一个节点
        pre_p1=pre_p1->nextRoute;
    }
    return true;
}


void sortRouteByNum(p_Route * pHead)//由于没有头结点，所以链表的头结点可能被更改
{
    if((* pHead)==NULL)
    {
        return;
    }
    int length = GetRouteLength(*pHead);
    p_Route  pMove=(*pHead);
    for (int i = 0; i < length; i++) //需要进行(n-1)次遍历,控制次数
    {
        if(pMove!=NULL)
        {
            while (pMove!=NULL&&pMove->nextRoute != NULL)
            {
                if (pMove->routeNum > pMove->nextRoute->routeNum)
                {
                    sawpRoutePf(pMove, pMove->nextRoute,pHead);
                    printRoute();
                }
                pMove = pMove->nextRoute;
            }
        }
        //每次遍历结束，pMove重新移动到链表头部
        pMove=(*pHead);
    }
}

int GetRouteLength(p_Route pHead)
{
    int Length = 0;
    while (pHead != NULL)
    {
        ++Length;
        pHead = pHead->nextRoute;
    }
    return Length;
}

void sawpRoutePf(p_Route A, p_Route B,p_Route* head)
{
    p_Route t_head=(*head);
    p_Route temp;
    p_Route pre_A;
    p_Route pre_B;
    if(A->routeNum==(*head)->routeNum)
    {
        if(A->nextRoute==B)
        {
             (*head)=B;//B的前指针
             A->nextRoute=B->nextRoute;
             B->nextRoute=A;
             return;
        }
        while (t_head != NULL)
        {
            if (t_head->nextRoute == A)
            {
                pre_A = t_head;
            }
            if (t_head->nextRoute == B)
            {
                pre_B = t_head;
            }
            t_head = t_head->nextRoute;
        }
        temp = B->nextRoute;
        (*head)=B;//B的前指针
        B->nextRoute=A->nextRoute;//B的后指针
        pre_B->nextRoute=A;//A的前指针
        A->nextRoute = temp;
    }

    while (t_head != NULL)
    {
        if (t_head->nextRoute == A)
        {
            pre_A = t_head;
        }
        if (t_head->nextRoute == B)
        {
            pre_B = t_head;
        }
        t_head = t_head->nextRoute;
    }
    if(A->nextRoute==B)
    {
         pre_A->nextRoute = B;//B的前节点
         A->nextRoute=B->nextRoute;
         B->nextRoute=A;
         return;
    }
    temp = B->nextRoute;
    pre_A->nextRoute = B;//B的前节点
    B->nextRoute = A->nextRoute;//B的后节点
    pre_B->nextRoute = A;//A的前节点
    A->nextRoute = temp;//A的前节点
}



void sortDayInfoByOrder(p_DayInfo * pHead)//由于没有头结点，所以链表的头结点可能被更改
{
    if((* pHead)==NULL)
    {
        return;
    }
    int length = GetDayInfoLength(*pHead);
    p_DayInfo  pMove=(*pHead);
    for (int i = 0; i < length; i++) //需要进行(n-1)次遍历,控制次数
    {
        if(pMove!=NULL)
        {
            while (pMove!=NULL&&pMove->nextDayInfo != NULL)
            {
                if (pMove->order > pMove->nextDayInfo->order)
                {
                    sawpDayInfoPf(pMove, pMove->nextDayInfo,pHead);
                    printRoute();
                }
                pMove = pMove->nextDayInfo;
            }
        }
        //每次遍历结束，pMove重新移动到链表头部
        pMove=(*pHead);
    }
}

int GetDayInfoLength(p_DayInfo pHead)
{
    int Length = 0;
    while (pHead != NULL)
    {
        ++Length;
        pHead = pHead->nextDayInfo;
    }
    return Length;
}

void sawpDayInfoPf(p_DayInfo A, p_DayInfo B,p_DayInfo* head)
{
    p_DayInfo t_head=(*head);
    p_DayInfo temp;
    p_DayInfo pre_A;
    p_DayInfo pre_B;
    if(A->order==(*head)->order)
    {
        if(A->nextDayInfo==B)
        {
             (*head)=B;//B的前指针
             A->nextDayInfo=B->nextDayInfo;
             B->nextDayInfo=A;
             return;
        }
        while (t_head != NULL)
        {
            if (t_head->nextDayInfo == A)
            {
                pre_A = t_head;
            }
            if (t_head->nextDayInfo == B)
            {
                pre_B = t_head;
            }
            t_head = t_head->nextDayInfo;
        }
        temp = B->nextDayInfo;
        (*head)=B;//B的前指针
        B->nextDayInfo=A->nextDayInfo;//B的后指针
        pre_B->nextDayInfo=A;//A的前指针
        A->nextDayInfo = temp;
    }

    while (t_head != NULL)
    {
        if (t_head->nextDayInfo == A)
        {
            pre_A = t_head;
        }
        if (t_head->nextDayInfo == B)
        {
            pre_B = t_head;
        }
        t_head = t_head->nextDayInfo;
    }
    if(A->nextDayInfo==B)
    {
         pre_A->nextDayInfo = B;//B的前节点
         A->nextDayInfo=B->nextDayInfo;
         B->nextDayInfo=A;
         return;
    }
    temp = B->nextDayInfo;
    pre_A->nextDayInfo = B;//B的前节点
    B->nextDayInfo = A->nextDayInfo;//B的后节点
    pre_B->nextDayInfo = A;//A的前节点
    A->nextDayInfo = temp;//A的前节点
    printf("\n");
}


void sortDayEXPInfoBySerial(p_DayEXPInfo * pHead)//由于没有头结点，所以链表的头结点可能被更改
{
    if((* pHead)==NULL)
    {
        return;
    }
    int length = GetDayEXPInfoLength(*pHead);
    p_DayEXPInfo  pMove=(*pHead);
    for (int i = 0; i < length; i++) //需要进行(n-1)次遍历,控制次数
    {
        if(pMove!=NULL)
        {
            while (pMove!=NULL&&pMove->nextDayEXPInfo != NULL)
            {
                if (pMove->serialNum > pMove->nextDayEXPInfo->serialNum)
                {
                    sawpDayEXPInfoPf(pMove, pMove->nextDayEXPInfo,pHead);
                    printRoute();
                }
                pMove = pMove->nextDayEXPInfo;
            }
        }
        //每次遍历结束，pMove重新移动到链表头部
        pMove=(*pHead);
    }
}

int GetDayEXPInfoLength(p_DayEXPInfo pHead)
{
    int Length = 0;
    while (pHead != NULL)
    {
        ++Length;
        pHead = pHead->nextDayEXPInfo;
    }
    return Length;
}

void sawpDayEXPInfoPf(p_DayEXPInfo A, p_DayEXPInfo B,p_DayEXPInfo* head)
{
    p_DayEXPInfo t_head=(*head);
    p_DayEXPInfo temp;
    p_DayEXPInfo pre_A;
    p_DayEXPInfo pre_B;
    if(A->serialNum==(*head)->serialNum)
    {
        if(A->nextDayEXPInfo==B)
        {
             (*head)=B;//B的前指针
             A->nextDayEXPInfo=B->nextDayEXPInfo;
             B->nextDayEXPInfo=A;
             return;
        }
        while (t_head != NULL)
        {
            if (t_head->nextDayEXPInfo == A)
            {
                pre_A = t_head;
            }
            if (t_head->nextDayEXPInfo == B)
            {
                pre_B = t_head;
            }
            t_head = t_head->nextDayEXPInfo;
        }
        temp = B->nextDayEXPInfo;
        (*head)=B;//B的前指针
        B->nextDayEXPInfo=A->nextDayEXPInfo;//B的后指针
        pre_B->nextDayEXPInfo=A;//A的前指针
        A->nextDayEXPInfo = temp;
    }

    while (t_head != NULL)
    {
        if (t_head->nextDayEXPInfo == A)
        {
            pre_A = t_head;
        }
        if (t_head->nextDayEXPInfo == B)
        {
            pre_B = t_head;
        }
        t_head = t_head->nextDayEXPInfo;
    }
    if(A->nextDayEXPInfo==B)
    {
         pre_A->nextDayEXPInfo = B;//B的前节点
         A->nextDayEXPInfo=B->nextDayEXPInfo;
         B->nextDayEXPInfo=A;
         return;
    }
    temp = B->nextDayEXPInfo;
    pre_A->nextDayEXPInfo = B;//B的前节点
    B->nextDayEXPInfo = A->nextDayEXPInfo;//B的后节点
    pre_B->nextDayEXPInfo = A;//A的前节点
    A->nextDayEXPInfo = temp;//A的前节点
    printf("\n");
}




