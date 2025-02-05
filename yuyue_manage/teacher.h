#pragma once
#include<iostream>
using namespace std;
#include "identity.h"

//教师类
class Teacher : public Identity{
public:

    Teacher();//默认构造

    Teacher(int id, string name, string pwd);//有参构造

    void operMenu();//菜单界面


    void showAllOrder();//查看所有预约

    void validOrder();//审核预约

    int m_Id;//教师编号
};