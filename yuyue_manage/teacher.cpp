#include "teacher.h"
#include "orderFile.h"
#include <iostream>
#include <vector>
using namespace std;
Teacher::Teacher(){}

Teacher::Teacher(int id, string name, string pwd){
    //��ʼ������
    this->m_Id=id;
    this->m_Name=name;
    this->m_Pwd=pwd;
}

void Teacher:: operMenu(){
    cout << "��ӭ��ʦ" <<this->m_Name<<"��¼"<<endl;
    cout << endl;
    cout << "\t\t---------------------------------" << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            1.�鿴����ԤԼ            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            2.���ԤԼ            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            0.ע����¼            " << endl;
    cout << "\t\t---------------------------------" << endl;
}

void Teacher::showAllOrder(){
    orderFile of;
    if(of.m_Size==0){
        cout<<"��ԤԼ��¼"<<endl;
        system("pause");
        system("cls");
        return;
    }
    for(int i=1;i<=of.m_Size;i++){
        cout<<i<<"��";
        cout<<"ԤԼ����: ��"<<of.m_orderData[i]["date"];
        cout<<" ʱ��: "<<(of.m_orderData[i]["interval"]=="1"?"����":"����");
        cout<<" ѧ��: "<<of.m_orderData[i]["stuID"];
        cout<<" ����: "<<of.m_orderData[i]["stuName"];
        cout<<" ����: "<<of.m_orderData[i]["roomID"];
        string status = " ״̬: ";
        if(of.m_orderData[i]["status"]=="1"){
            status+="�����";
        }else if(of.m_orderData[i]["status"]=="2"){
            status+="ԤԼ�ɹ�";
        }else if(of.m_orderData[i]["status"]=="-1"){
            status+="���δͨ��,ԤԼʧ��";
        }else{
            status+="ԤԼ��ȡ��";
        }
        cout<<status<<endl;
    }
    system("pause");
    system("cls");
}

void Teacher::validOrder(){
    orderFile of;
    if(of.m_Size==0){
        cout<<"��ԤԼ��¼"<<endl;
        system("pause");
        system("cls");
        return;
    }
    cout<<"�����ԤԼ��¼����: "<<endl;

    vector<int>v;
    int index=1;
    for(int i=1;i<=of.m_Size;i++){
        if(of.m_orderData[i]["status"]=="1"){
            v.push_back(i);
            cout<<index++<<"�� ";
            cout<<"ԤԼʱ��: ��"<<of.m_orderData[i]["date"];
            cout<<" ʱ��: "<<(of.m_orderData[i]["interval"]=="1"?"����":"����");
            cout<<" ����: "<<of.m_orderData[i]["roomID"];
            string status = "״̬: ";
            if(of.m_orderData[i]["status"]=="1"){
                status+="�����";
            }else if(of.m_orderData[i]["status"]=="1"){
                status+="ԤԼ�ɹ�";
            }else if(of.m_orderData[i]["status"]=="1"){
                status+="���δͨ��,ԤԼʧ��";
            }else{
                status+="ԤԼ��ȡ��";
            }
            cout<<status<<endl;
        }
    }
    cout<<"��������˵�ԤԼ��¼,0������"<<endl;
    int select = 0;
    int ret = 0;
    while(true){
        cin>>select;
        if(select>=0&&select<=of.m_Size){
            if(select==0){
                break;
            }else{
                cout<<"��������˽��"<<endl;
                cout<<"1��ͨ��"<<endl;
                cout<<"2����ͨ��"<<endl;\
                cin>>ret;
                if(ret==1){
                    of.m_orderData[v[select-1]]["status"]="2";
                }else{
                    of.m_orderData[v[select-1]]["status"]="-1";
                }
                of.updateOrder();
                cout<<"������!"<<endl;
                break;
            }
        }
        cout<<"��������,����������"<<endl;
    }
    system("pause");
    system("cls");
}