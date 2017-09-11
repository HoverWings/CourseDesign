#include"PersonalTrip.h"
#include"mainwindow.h"


p_Route hRoute=NULL;

//bool create
bool creatRoute()//初始化链表
{
    hRoute=(p_Route)malloc(sizeof(Route));
    hRoute->nextRoute=NULL;
    return true;
}

bool insertRoute(p_Route* curRoute) //当前节点
{
    //bool ini=false;
    if(hRoute==NULL)
    {
        creatRoute();
        //ini = true;
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
        /*
        //msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        //msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret)
        {
          case QMessageBox::Save://覆盖
                if(pre->nextRoute!=NULL)
                {
                    (*curRoute)->nextRoute=(pre)->nextRoute->nextRoute;
                    deleteRoute((*curRoute)->routeNum);
                    (pre)->nextRoute=*curRoute;
                    //free((pre)->nextRoute);
                    //deleterou
                }
                else
                {
                    (pre)->nextRoute=*curRoute;
                }



                return true;
              break;
          case QMessageBox::Discard:
              return false;
              break;
          case QMessageBox::Cancel:
              // Cancel was clicked
              break;
          default:
              // should never be reached
              break;
        }
         /*if(true)
        {
            (*curRoute)->nextRoute=(pre)->nextRoute->nextRoute;
            free((pre)->nextRoute);
            (pre)->nextRoute=*curRoute;
            return true;
        }
        else
        {
            //显示窗口
        }
        */

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


//bool deleteRoute(p_Route cur)//这个是不能用的
//{
//	p_Route p = hRoute;//指向头结点
//	if (hRoute == NULL)
//	{
//		//printf("sd");
//		return false;
//	}
//	p_Route pre = NULL;
//	p_Route tail = NULL;
//	if (findRouteByNum(cur, &pre, &tail))
//	{
//		pre->nextRoute = cur->nextRoute;
//		//处理二级节点
//		free(cur);
//	}
//	else
//	{
//		printf("所删除的节点不存在");
//	}
//}

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

bool deleteRouteByrouteNum(int num)
{
    p_Route p = hRoute;
    if (hRoute->routeNum == num)
    {
        hRoute = hRoute->nextRoute;
        //do sth
    }
    else
    {
        p=findRouteByNum(num);
        //删除某个二级节点
    }
    return true;
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
    //(tail)->nextDayInfo = *cur;
    //(*cur)->nextDayInfo = NULL;
    //(*cur)->hDayEXPInfo = NULL;
    //return true;

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
        //(*cur)-> = NULL;
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
        //(tail)->nextDayInfo = *cur; //此处再说
        //(*cur)->nextDayInfo = NULL;
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
                   p_DayInfo pre_p2=p1->hDayInfo;
                   if(pre_p2->nextDayInfo!=NULL)
                   {
                       if(pre_p2->nextDayInfo->order==p2->order)
                       {
                            pre_p2->nextDayInfo=p2;
                       }
                       else
                       {
                            pre_p2=pre_p2->nextDayInfo;
                            if(pre_p2==NULL)
                            {
                                return false;
                            }
                       }
                   }
                   else
                   {
                        return false;
                   }

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
                }

            }
        }

    }
    return true;
}


bool sortByRouteNum()
{
    p_Route p1=hRoute;
    if(p1==NULL)
    {
        return false;
    }
    while(p1->nextRoute!=NULL)
    {

    }
}

bool sortByOrder();
bool sortBySerialNum();











