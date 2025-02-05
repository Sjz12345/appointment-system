#include "student.h"
#include "globalFile.h"
#include "computerRoom.h"
#include "orderFile.h"
#include <fstream>
using namespace std;
Student::Student(){}

Student::Student(int id, string name, string pwd){
    this->m_Id=id;
    this->m_Name=name;
    this->m_Pwd=pwd;

    //初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE,ios::in);

    computerRoom com;
    while(ifs>>com.m_ComId&&ifs>>com.m_MaxNum){
        //将文件中的信息读取到容器中
        vCom.push_back(com);
    }
}

void Student:: operMenu(){
    cout << "欢迎学生" <<this->m_Name<<"登录"<<endl;
    cout << endl;
    cout << "\t\t---------------------------------" << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            1.申请预约            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            2.查看个人预约            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            3.查看所有预约            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            4.取消预约            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            0.注销登录            " << endl;
    cout << "\t\t---------------------------------" << endl;
}

void Student::applyOrder(){
    cout<<"机房开放时间为周一至周五"<<endl;
    cout<<"请输入申请预约的时间: "<<endl;
    cout<<"1.周一"<<endl;
    cout<<"2.周二"<<endl;
    cout<<"3.周三"<<endl;
    cout<<"4.周四"<<endl;
    cout<<"5.周五"<<endl;

    int date=0;//日期
    int interval=0;//时间段
    int room=0;//机房

    while(true){
        cin>>date;
        if(date>=1&&date<=5)
            break;
        cout<<"输入有误,请重新输入"<<endl;
    }

    cout<<"请输入预约时间段"<<endl;
    cout<<"1.上午"<<endl;
    cout<<"2.下午"<<endl;

    while(true){
        cin>>interval;
        if(interval>=1&&interval<=2)
            break;
        cout<<"输入有误,请重新输入"<<endl;
    }

    cout<<"请选择机房:"<<endl;
    for(int i=0;i<vCom.size();i++){
        cout<<vCom[i].m_ComId<<"号机房容量为: "<<vCom[i].m_MaxNum<<endl;
    }
    while(true){
        cin>>room;
        if(room>=1&&room<=vCom.size())
            break;
    }

    cout<<"预约提交成功!审核中"<<endl;

    ofstream ofs;
    ofs.open(ORDER_FILE,ios::app);

    ofs<<"date:"<<date<<" ";
    ofs<<"interval:"<<interval<<" ";
    ofs<<"stuID:"<<this->m_Id<<" ";
    ofs<<"stuName:"<<this->m_Name<<" ";
    ofs<<"roomID:"<<room<<" ";
    ofs<<"status:"<<1<<endl;

    ofs.close();
    system("pause");
    system("cls");
}

void Student::showMyOrder(){
    orderFile of;
    if(of.m_Size==0) {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }

    for(int i=1;i<=of.m_Size;i++){
        if(atoi(of.m_orderData[i]["stuID"].c_str())==this->m_Id){
            cout<<"预约时间: 周"<<of.m_orderData[i]["date"];
            cout<<" 时段: "<<(of.m_orderData[i]["interval"]=="1"?"上午":"下午");
            cout<<" 机房: "<<of.m_orderData[i]["roomID"];
            string status = " 状态: ";//0-取消的预约  1-审核中  2-已预约  -1-预约失败
            if(of.m_orderData[i]["status"]=="1"){

                status+="审核中";

            }else if(of.m_orderData[i]["status"]=="2"){

                status+="预约成功";

            }else if(of.m_orderData[i]["status"]=="-1"){

                status+="预约失败";

            }else{

                status+="预约已取消";

            }
            cout<<status<<endl;
        }
    }
    system("pause");
    system("cls");
}

void Student::showAllOrder(){
        orderFile of;
        if(of.m_Size==0) {
            cout<<"无预约记录"<<endl;
            system("pause");
            system("cls");
            return;
        }
    for(int i=1;i<=of.m_Size;i++){
            cout<<"学号: "<<of.m_orderData[i]["stuID"]<<" "<<"姓名: "<<of.m_orderData[i]["stuName"]<<" ";
            cout<<"预约时间: 周"<<of.m_orderData[i]["date"];
            cout<<" 时段: "<<(of.m_orderData[i]["interval"]=="1"?"上午":"下午");
            cout<<" 机房: "<<of.m_orderData[i]["roomID"];
            string status = " 状态: ";//0-取消的预约  1-审核中  2-已预约  -1-预约失败
            if(of.m_orderData[i]["status"]=="1"){

                status+="审核中";

            }else if(of.m_orderData[i]["status"]=="2"){

                status+="预约成功";

            }else if(of.m_orderData[i]["status"]=="-1"){

                status+="预约失败";

            }else{

                status+="预约已取消";

            }
            cout<<status<<endl;
    }
    system("pause");
    system("cls");
}

void Student::cancleOrder(){
    orderFile of;
    if(of.m_Size==0){
        cout<<"无预约记录"<<endl;
        system("pause");
        system("cls");
        return;
    }
    cout<<"审核中或预约成功的记录可以取消,请输入取消的记录"<<endl;
    vector<int>v;//存放在最大容器中的下标编号
    int index=1;
    for(int i=1;i<=of.m_Size;i++){
        //先判断是自身学号
        if(this->m_Id==atoi(of.m_orderData[i]["stuID"].c_str())){
            //再筛选状态  审核中或预约成功
            if(of.m_orderData[i]["status"]=="1"||of.m_orderData[i]["status"]=="2"){
                v.push_back(i);
                cout<<index++<<"、";
                cout<<"预约时间: 周"<<of.m_orderData[i]["date"];
                cout<<" 时间段: "<<(of.m_orderData[i]["interval"]=="1"?"上午":"下午");
                cout<<" 机房编号: "<<of.m_orderData[i]["roomID"];
                string status = " 状态: ";
                if(of.m_orderData[i]["status"]=="1"){
                    status+="审核中";
                }else if(of.m_orderData[i]["status"]=="2"){
                    status+="预约成功";
                }
                cout<<status<<endl;
            }
        }
    }
    cout<<"请输入取消的记录, 0代表返回"<<endl;
    int select=0;

    while(true){

        cin>>select;

        if(select>=0&&select<=v.size()){
            if(select==0){
                break;
            }else{
                of.m_orderData[v[select-1]]["status"]="0";
                of.updateOrder();
                cout<<"预约已取消"<<endl;
                break;
            }
        }
        cout<<"输入有误,请重新输入"<<endl;
    }
    system("pause");
    system("cls");
}