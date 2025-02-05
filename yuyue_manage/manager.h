#pragma once
#include<iostream>
#include <vector>
#include <fstream>
#include "student.h"
#include "teacher.h"
#include "identity.h"
#include "computerRoom.h"
using namespace std;


//管理人员类
class Manager : public Identity{
public:

    Manager();//默认构造

    Manager(string name, string pwd);//有参构造

    void initVector();//初始化容器

    vector <Student> vStu;//学生容器

    vector <Teacher> vTea;//教师容器

    vector <computerRoom> vCom;//机房容器

    void operMenu();//菜单界面

    void addPerson();//添加账号

    void showPerson();//查看账号

    void showComputer();//查看机房信息

    void cleanFile();//清空预约记录

    bool checkRepeat(int id,int type);//检测重复 1.学号或职工号 2.检测类型
};