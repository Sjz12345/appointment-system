#include "manager.h"
#include "fstream"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include <algorithm>
Manager::Manager(){}

Manager::Manager(string name, string pwd){
    //初始化
    this->m_Name=name;
    this->m_Pwd=pwd;
    this->initVector();
}

void Manager::operMenu(){
    cout << "欢迎管理员" <<this->m_Name<<"登录"<<endl;
    cout << endl;
    cout << "\t\t---------------------------------" << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            1.添加账号            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            2.查看账号            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            3.查看机房            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            4.清空预约            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            0.注销登录            " << endl;
    cout << "\t\t---------------------------------" << endl;
}

void Manager::addPerson(){

    cout<<"请输入添加账号类型"<<endl;
    cout<<"1.添加学生"<<endl;
    cout<<"2.添加老师"<<endl;

    string fileName;//操作文件名
    string tip;//提示id号
    ofstream ofs;//操作文件对象
    string errorTip;//重复错误提示
    int select=0;
    cin>>select;

    if(select==1){
        //添加学生
        fileName = STUDENT_FILE;
        tip="请输入学号";
        errorTip = "学号重复，请重新输入";

    }else{
        //添加教师
        fileName = TEACHER_FILE;
        tip="请输入职工号";
        errorTip = "职工号重复，请重新输入";
    }
    ofs.open(fileName,ios::out|ios::app);

    int id;//学号或职工号
    string name;//姓名
    string pwd;//密码

    cout<<tip<<endl;
    while(true){
        cin>>id;
        bool ret = checkRepeat(id,select);
        if(ret){
            cout<<errorTip<<endl;
        }else{
            break;
        }
    }
    cout<<"请输入姓名"<<endl;
    cin>>name;
    cout<<"请输入密码"<<endl;
    cin>>pwd;
    if(select==1){
        Student s(id,name,pwd);
        vStu.push_back(s);
    }else{
        Teacher t(id,name,pwd);
        vTea.push_back(t);
    }
    ofs<<id<<" "<<name<<" "<<pwd<<" "<<endl;
    cout<<"添加成功"<<endl;
    system("pause");
    system("cls");
    ofs.close();
}

void Manager::initVector() {

    vStu.clear();
    vTea.clear();
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "学生文件读取失败" << endl;
        return;
    }
    //读取学生信息
    Student s;
    while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
        vStu.push_back(s);
    }
    cout << "当前学生数量为" << vStu.size() << endl;
    ifs.close();

    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "教师文件读取失败" << endl;
        return;
    }
    //读取教师信息
    Teacher t;
    while (ifs >> t.m_Id && ifs >> t.m_Name && ifs >> t.m_Pwd) {
        vTea.push_back(t);
    }
    cout << "当前教师数量为" << vTea.size() << endl;
    ifs.close();

    ifs.open(COMPUTER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "机房文件读取失败" << endl;
        return;
    }
    //读取机房信息
    computerRoom com;
    while(ifs>>com.m_ComId&&ifs>>com.m_MaxNum){
        vCom.push_back(com);
    }
    cout << "当前机房数量为" << vCom.size() << endl;
    ifs.close();
}

bool Manager::checkRepeat(int id, int type) {
    if(type==1){
        //检测学生
        for(auto temp:vStu){
            if(temp.m_Id==id){
                return true;
            }
        }
    }else{
        //检测老师
        for(auto temp:vTea){
            if(temp.m_Id==id){
                return true;
            }
        }
    }
    return false;
}

void Manager::showPerson(){

    cout<<"请选择查看的内容:"<<endl;
    cout<<"1.查看所有学生"<<endl;
    cout<<"2.查看所有教师"<<endl;

    int select=0;
    cin>>select;

    if(select==1){//查看学生
        cout<<"所有学生信息如下:"<<endl;
        for(auto temp:vStu){
            cout<<"学号/职工号: "<<temp.m_Id<<" 姓名: "<<temp.m_Name<<" 密码: "<<temp.m_Pwd<<endl;
        }
    }else{//查看教师
        for(auto temp:vTea){
            cout<<"学号/职工号: "<<temp.m_Id<<" 姓名: "<<temp.m_Name<<" 密码: "<<temp.m_Pwd<<endl;
        }
    }
    system("pause");
    system("cls");
}

void Manager::showComputer(){
    for(vector<computerRoom>::iterator it=vCom.begin();it!=vCom.end();it++){
        cout<<"机房编号: "<<it->m_ComId<<" 机房最大容量: "<<it->m_MaxNum<<endl;
    }
    system("pause");
    system("cls");
}

void Manager::cleanFile(){
    ofstream ofs;
    ofs.open(ORDER_FILE,ios::trunc);
    ofs.close();
    cout<<"预约记录清空成功"<<endl;
    system("pause");
    system("cls");
}
