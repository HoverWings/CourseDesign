#ifndef PERSONALTRIP_H
#define PERSONALTRIP_H
#pragma once
//进行相关结构体的声明
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>//其中内含wingdi
#include<wingdi.h>
#include<stdbool.h> //使得bool合法


#define _CRT_SECURE_NO_WARNINGS


typedef struct DressingIndex //穿衣指数结构体
{
    int minT;
    int maxT;
    char recommendedDressing[20];//推荐的着装//出行期温度及穿衣指数
}DressingIndex;


typedef struct Route //行程一级链表结构体
{
    int routeNum;//行程编号
    char routeName[20];//主要目的地名称
    char routeCountry[20];//目的地所属国家/省份
    DressingIndex dressingIndex;
    char bigTrans[20];//大交通 主要交通
    char mainScene[200];//主要景点
    char remoteNum[10];//异地办理手续行程编号 此处更改为char
                  //如需异地面签或提交材料，给出异地办手续的行程编号，否则为空
    char beginDate[20];//出发日期
    char arriveDate[20];//返回到达日期
    int totalTime;//行程总天数
    int totalNum;//行程总人数
    float totalPrice;//行程总费用
    struct DayInfo* hDayInfo;//行程具体信息头指针
    struct Route* nextRoute;//链表next指针
}Route, *p_Route;

typedef struct DayInfo //行程具体信息结构体
{
    int routeNum;//所属行程编号
    int order;//序号 2代表第二天  存成int
    char breakfastLoc[50];//早餐地点
    char morningScene[50];//上午景点
    char LunchLoc[50];//午餐地点
    char afternoonScene[50];//下午景点
    char dinnerLoc[50];//晚餐地点
    char transInfo[200];//小交通
    char residence[50];//住宿地点
    struct DayEXPInfo* hDayEXPInfo;
    struct DayInfo* nextDayInfo;//链表next指针
}DayInfo, *p_DayInfo;

typedef struct DayEXPInfo //每天消费信息
{
    int routeNum;
    int order;//序号 2代表第二天
    int serialNum;//顺序号
    char TxTime[20];//交易时间
    char TxKind[16];//交易种类
    float TxAmount;//交易金额
    char isPrepayment[10];//是否预支付
    char payment[10];//支付方式
    char explain[50];//说明
    struct DayEXPInfo* nextDayEXPInfo;
}DayEXPInfo, *p_DayEXPInfo;

extern p_Route hRoute;//声明为静态变量

//函数声明
bool creatRoute();//初始化链表
bool insertRoute(p_Route* curRoute); //当前节点
bool findRouteByNum(p_Route cur, p_Route* pre, p_Route* tail);//用于插入 cur为需要查找是否重复的节点 pre用来记录前驱 tail用来记录整个链表尾部
p_Route findRouteByNum(int num);//用于查询
bool printRoute();//打印以及链表
//打印整个链表
bool deleteRoute(int routeNum);


bool insertDayInfo(p_Route* route, p_DayInfo* cur);
bool insertDayInfo(p_DayInfo* cur);
bool findDayInfoByOrder(p_Route route, p_DayInfo cur, p_DayInfo* pre, p_DayInfo* tail);//删除第几天
p_DayInfo findDayInfoByOrder(p_Route* route, int order);// 二级链表 通过和行程编号序号找到 用于查询
p_DayInfo findDayInfoByOrder(int routeNum, int order);// 二级链表 通过和行程编号序号找到 用于查询 用节点的封装
bool printDayInfo(p_Route route);//打印二级链表
bool deleteDayInfo(int routeNum, int order);//单个删除



bool insertDayEXPInfo(p_Route* route, p_DayInfo* dayinfo,p_DayEXPInfo* cur);
bool insertDayEXPInfo(p_DayEXPInfo* cur);
bool findDayEXPInfoByserialNum(p_DayInfo dayinfo, p_DayEXPInfo cur, p_DayEXPInfo* pre, p_DayEXPInfo* tail);//用于插入
p_DayEXPInfo findDayEXPInfoByserialNum(int routeNum, int order, int serialNum);//用于查询
bool printDayEXPInfo(int routeNum, int order, int serialNum);//打印三级链表
bool deleteDayEXPInfo(int routeNum, int order, int serialNum);//单个删除

//save opreation
bool saveToFile();
bool loadFromFile();

bool printAll();

void sortRouteByNum(p_Route * pHead);//由于没有头结点，所以链表的头结点可能被更改
void sawpRoutePf(p_Route A, p_Route B,p_Route* head);
int GetRouteLength(p_Route pHead);

void sortDayInfoByOrder(p_DayInfo * pHead);//由于没有头结点，所以链表的头结点可能被更改
void sawpDayInfoPf(p_DayInfo A, p_DayInfo B,p_DayInfo* head);
int GetDayInfoLength(p_DayInfo pHead);

void sortDayEXPInfoBySerial(p_DayEXPInfo * pHead);//由于没有头结点，所以链表的头结点可能被更改
void sawpDayEXPInfoPf(p_DayEXPInfo A, p_DayEXPInfo B,p_DayEXPInfo* head);
int GetDayEXPInfoLength(p_DayEXPInfo pHead);

p_DayInfo findTransInfoByScene(char Scene[50]);
float findEXPByResidence(char Residence[50]);

#endif // PERSONALTRIP_H
