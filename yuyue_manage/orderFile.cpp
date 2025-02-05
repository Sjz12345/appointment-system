#include "orderFile.h"
#include <iostream>
orderFile::orderFile() {
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);

    string date;//日期
    string interval;//时间段
    string stuId;//学生编号
    string stuName;//学生姓名
    string roomId;//机房编号
    string status;//预约状态

    this->m_Size = 0;

    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status) {

        string key;
        string value;
        map<string, string> m;
        //截取日期
        int pos = date.find(":");
        key = date.substr(0, pos);
        value = date.substr(pos + 1, date.size() - pos - 1);
        m.insert(make_pair(key, value));
        //截取时间段
        pos = interval.find(":");
        key = interval.substr(0, pos);
        value = interval.substr(pos + 1, interval.size() - pos - 1);
        m.insert(make_pair(key, value));
        //截取学号
        pos = stuId.find(":");
        key = stuId.substr(0, pos);
        value = stuId.substr(pos + 1, stuId.size() - pos - 1);
        m.insert(make_pair(key, value));
        //截取姓名
        pos = stuName.find(":");
        key = stuName.substr(0, pos);
        value = stuName.substr(pos + 1, stuName.size() - pos - 1);
        m.insert(make_pair(key, value));
        //截取机房号
        pos = roomId.find(":");
        key = roomId.substr(0, pos);
        value = roomId.substr(pos + 1, roomId.size() - pos - 1);
        m.insert(make_pair(key, value));
        //截取预约状态
        pos = status.find(":");
        key = status.substr(0, pos);
        value = status.substr(pos + 1, status.size() - pos - 1);
        m.insert(make_pair(key, value));

        //将小map容器放入大map容器中
        this->m_Size++;
        this->m_orderData.insert(make_pair(this->m_Size, m));
    }
    ifs.close();
}

void orderFile::updateOrder() {
    if(this->m_Size==0)
        return;

    ofstream ofs(ORDER_FILE,ios::out|ios::trunc);
    for(int i=1;i<=this->m_Size;i++){
        ofs<<"date:"<<this->m_orderData[i]["date"]<<" ";
        ofs<<"interval:"<<this->m_orderData[i]["interval"]<<" ";
        ofs<<"stuID:"<<this->m_orderData[i]["stuID"]<<" ";
        ofs<<"stuName:"<<this->m_orderData[i]["stuName"]<<" ";
        ofs<<"roomID:"<<this->m_orderData[i]["roomID"]<<" ";
        ofs<<"status:"<<this->m_orderData[i]["status"]<<endl;
    }
    ofs.close();
}