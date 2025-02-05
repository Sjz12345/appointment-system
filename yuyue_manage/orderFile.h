#pragma once
#include <iostream>
using namespace std;
#include <map>
#include "globalFile.h"
#include <fstream>
#include <string>
class orderFile{
public:

    //构造函数
    orderFile();

    //更新预约记录
    void updateOrder();

    //储存信息的map容器,key记录条数
    map<int,map<string,string>> m_orderData;

    //记录预约条数
    int m_Size;
};