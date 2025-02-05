#include <iostream>
#include "identity.h"
#include <fstream>
#include <string>
#include "globalFile.h"
#include "student.h"
#include "manager.h"
#include "teacher.h"
using namespace std;
//进入管理员子菜单
void managerMenu(Identity * &manager){
    while(true){
        //调用管理员子菜单
        manager->operMenu();
         //父类指针转化为子类
        Manager* man = (Manager*)manager;
        int select=0;

        cin>>select;
        if(select==1){//添加账号
            man->addPerson();

        }else if(select==2){//查看账号
            man->showPerson();

        }else if(select==3){//查看机房
            man->showComputer();

        }else if(select==4){//清空预约
            man->cleanFile();

        }else{
            delete manager;//销毁堆区对象
            cout<<"注销成功"<<endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
//进入学生子菜单
void studentMenu(Identity * &student){
    while(true){
        //调用管理员子菜单
        student->operMenu();
        //父类指针转化为子类
        Student* man = (Student*)student;
        int select=0;

        cin>>select;
        if(select==1){//申请预约
            man->applyOrder();

        }else if(select==2){//查看自身预约
            man->showMyOrder();

        }else if(select==3){//查看所有预约
            man->showAllOrder();

        }else if(select==4){//取消预约
            man->cancleOrder();

        }else{
            delete student;//销毁堆区对象
            cout<<"注销成功"<<endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
//进入教师子菜单
void teacherMenu(Identity * &teacher){
    while(true){
        //调用教师子菜单
        teacher->operMenu();
        //父类指针转化为子类
        Teacher* man = (Teacher*)teacher;
        int select=0;

        cin>>select;
        if(select==1){//查看所有预约
            man->showAllOrder();

        }else if(select==2){//审核预约
            man->validOrder();

        }else{
            delete teacher;//销毁堆区对象
            cout<<"注销成功"<<endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
//登录功能     参数一：操作文件名   参数二：操作身份类型
void LoginIN(string fileName,int type){

    //多态，父类指针指向子类对象
     Identity* person =NULL;
    //读文件
    ifstream ifs;
    ifs.open(fileName,ios::in);

    if(!ifs.is_open()){
        cout<<"文件不存在"<<endl;
        ifs.close();
        return ;
    }

    int id=0;
    string name;
    string pwd;

    if(type==1){//学生
        cout<<"请输入您的学号"<<endl;
        cin>>id;
    }else if(type==2){//老师
        cout<<"请输入您的职工号"<<endl;
        cin>>id;
    }

    cout<<"请输入用户名"<<endl;
    cin>>name;
    cout<<"请输入密码"<<endl;
    cin>>pwd;

    if(type==1){//学生身份验证
        int fId;
        string fName;
        string fPwd;
        while(ifs>>fId&&ifs>>fName&&ifs>>fPwd){
            //cout<<fId<<" "<<fName<<" "<<fPwd<<endl;
            //与存储信息进行比较
            if(fId==id&&fName==name&&fPwd==pwd){
                cout<<"学生验证登录成功!"<<endl;
                system("pause");
                system("cls");
                person = new Student(id,name,pwd);
                //进入学生身份子菜单
                studentMenu(person);
                return;
            }
        }
    }else if(type==2){//老师身份验证
        int fId;
        string fName;
        string fPwd;
        while(ifs>>fId&&ifs>>fName&&ifs>>fPwd){
            //cout<<fId<<" "<<fName<<" "<<fPwd<<endl;
            //与存储信息进行比较
            if(fId==id&&fName==name&&fPwd==pwd){
                cout<<"教师验证登录成功!"<<endl;
                system("pause");
                system("cls");
                person = new Teacher(id,name,pwd);
                //进入教师身份子菜单
                teacherMenu(person);
                return;
            }
        }
    }else if(type==3){//管理员身份验证
        string fName;
        string fPwd;
        while(ifs>>fName&&ifs>>fPwd){
            //cout<<fId<<" "<<fName<<" "<<fPwd<<endl;
            //与存储信息进行比较
            if(fName==name&&fPwd==pwd){
                cout<<"管理员验证登录成功!"<<endl;
                system("pause");
                system("cls");
                person = new Manager(name,pwd);
                //进入管理员身份子菜单
                managerMenu(person);
                return;
            }
        }
    }

    cout<<"身份验证失败"<<endl;
    system("pause");
    system("cls");
}

int main() {
    int Select;
    while(true){
        cout << "=========================欢迎进入机房预约系统=========================" << endl;
        cout << "请输入您的身份" << endl;
        cout << "\t\t---------------------------------" << endl;
        cout << "\t\t" << endl;
        cout << "\t\t            1.学生代表            " << endl;
        cout << "\t\t" << endl;
        cout << "\t\t            2.老师            " << endl;
        cout << "\t\t" << endl;
        cout << "\t\t            3.管理员            " << endl;
        cout << "\t\t" << endl;
        cout << "\t\t            0.退出            " << endl;
        cout << "\t\t---------------------------------" << endl;

        cin>>Select;

        switch (Select) {
            case 1://学生登录
                LoginIN(STUDENT_FILE,1);
                break;
            case 2://老师登录
                LoginIN(TEACHER_FILE,2);
                break;
            case 3://管理员登录
                LoginIN(ADMIN_FILE,3);
                break;
            case 0:
                cout<<"退出成功"<<endl;
                system("pause");
                return 0;
            default:
                cout<<"输入有误，请重新输入:"<<endl;
                system("pause");
                system("cls");
                break;

        }
    }
}
