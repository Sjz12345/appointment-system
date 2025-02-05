#pragma once
#include<iostream>
#include <vector>
#include "identity.h"
#include "computerRoom.h"
using namespace std;

//学生类
class Student : public Identity{
public:

    Student();//默认构造

    Student(int id, string name, string pwd);//有参构造

    void operMenu();//菜单界面

    void applyOrder();//申请预约

    void showMyOrder();//查看自身预约

    void showAllOrder();//查看所有预约

    void cancleOrder();//取消预约

    int m_Id;//学生学号

    vector<computerRoom>vCom;//机房容器
};