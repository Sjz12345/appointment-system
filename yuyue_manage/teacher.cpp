#include "teacher.h"
#include "orderFile.h"
#include <iostream>
#include <vector>
using namespace std;
Teacher::Teacher(){}

Teacher::Teacher(int id, string name, string pwd){
    //初始化属性
    this->m_Id=id;
    this->m_Name=name;
    this->m_Pwd=pwd;
}

void Teacher:: operMenu(){
    cout << "欢迎教师" <<this->m_Name<<"登录"<<endl;
    cout << endl;
    cout << "\t\t---------------------------------" << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            1.查看所有预约            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            2.审核预约            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            0.注销登录            " << endl;
    cout << "\t\t---------------------------------" << endl;
}

void Teacher::showAllOrder(){
    orderFile of;
    if(of.m_Size==0){
        cout<<"无预约记录"<<endl;
        system("pause");
        system("cls");
        return;
    }
    for(int i=1;i<=of.m_Size;i++){
        cout<<i<<"、";
        cout<<"预约日期: 周"<<of.m_orderData[i]["date"];
        cout<<" 时段: "<<(of.m_orderData[i]["interval"]=="1"?"上午":"下午");
        cout<<" 学号: "<<of.m_orderData[i]["stuID"];
        cout<<" 姓名: "<<of.m_orderData[i]["stuName"];
        cout<<" 机房: "<<of.m_orderData[i]["roomID"];
        string status = " 状态: ";
        if(of.m_orderData[i]["status"]=="1"){
            status+="审核中";
        }else if(of.m_orderData[i]["status"]=="2"){
            status+="预约成功";
        }else if(of.m_orderData[i]["status"]=="-1"){
            status+="审核未通过,预约失败";
        }else{
            status+="预约已取消";
        }
        cout<<status<<endl;
    }
    system("pause");
    system("cls");
}

void Teacher::validOrder(){
    orderFile of;
    if(of.m_Size==0){
        cout<<"无预约记录"<<endl;
        system("pause");
        system("cls");
        return;
    }
    cout<<"待审核预约记录如下: "<<endl;

    vector<int>v;
    int index=1;
    for(int i=1;i<=of.m_Size;i++){
        if(of.m_orderData[i]["status"]=="1"){
            v.push_back(i);
            cout<<index++<<"、 ";
            cout<<"预约时间: 周"<<of.m_orderData[i]["date"];
            cout<<" 时段: "<<(of.m_orderData[i]["interval"]=="1"?"上午":"下午");
            cout<<" 机房: "<<of.m_orderData[i]["roomID"];
            string status = "状态: ";
            if(of.m_orderData[i]["status"]=="1"){
                status+="审核中";
            }else if(of.m_orderData[i]["status"]=="1"){
                status+="预约成功";
            }else if(of.m_orderData[i]["status"]=="1"){
                status+="审核未通过,预约失败";
            }else{
                status+="预约已取消";
            }
            cout<<status<<endl;
        }
    }
    cout<<"请输入审核的预约记录,0代表返回"<<endl;
    int select = 0;
    int ret = 0;
    while(true){
        cin>>select;
        if(select>=0&&select<=of.m_Size){
            if(select==0){
                break;
            }else{
                cout<<"请输入审核结果"<<endl;
                cout<<"1、通过"<<endl;
                cout<<"2、不通过"<<endl;\
                cin>>ret;
                if(ret==1){
                    of.m_orderData[v[select-1]]["status"]="2";
                }else{
                    of.m_orderData[v[select-1]]["status"]="-1";
                }
                of.updateOrder();
                cout<<"审核完毕!"<<endl;
                break;
            }
        }
        cout<<"输入有误,请重新输入"<<endl;
    }
    system("pause");
    system("cls");
}