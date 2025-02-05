#include "manager.h"
#include "fstream"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include <algorithm>
Manager::Manager(){}

Manager::Manager(string name, string pwd){
    //��ʼ��
    this->m_Name=name;
    this->m_Pwd=pwd;
    this->initVector();
}

void Manager::operMenu(){
    cout << "��ӭ����Ա" <<this->m_Name<<"��¼"<<endl;
    cout << endl;
    cout << "\t\t---------------------------------" << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            1.����˺�            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            2.�鿴�˺�            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            3.�鿴����            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            4.���ԤԼ            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            0.ע����¼            " << endl;
    cout << "\t\t---------------------------------" << endl;
}

void Manager::addPerson(){

    cout<<"����������˺�����"<<endl;
    cout<<"1.���ѧ��"<<endl;
    cout<<"2.�����ʦ"<<endl;

    string fileName;//�����ļ���
    string tip;//��ʾid��
    ofstream ofs;//�����ļ�����
    string errorTip;//�ظ�������ʾ
    int select=0;
    cin>>select;

    if(select==1){
        //���ѧ��
        fileName = STUDENT_FILE;
        tip="������ѧ��";
        errorTip = "ѧ���ظ�������������";

    }else{
        //��ӽ�ʦ
        fileName = TEACHER_FILE;
        tip="������ְ����";
        errorTip = "ְ�����ظ�������������";
    }
    ofs.open(fileName,ios::out|ios::app);

    int id;//ѧ�Ż�ְ����
    string name;//����
    string pwd;//����

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
    cout<<"����������"<<endl;
    cin>>name;
    cout<<"����������"<<endl;
    cin>>pwd;
    if(select==1){
        Student s(id,name,pwd);
        vStu.push_back(s);
    }else{
        Teacher t(id,name,pwd);
        vTea.push_back(t);
    }
    ofs<<id<<" "<<name<<" "<<pwd<<" "<<endl;
    cout<<"��ӳɹ�"<<endl;
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
        cout << "ѧ���ļ���ȡʧ��" << endl;
        return;
    }
    //��ȡѧ����Ϣ
    Student s;
    while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
        vStu.push_back(s);
    }
    cout << "��ǰѧ������Ϊ" << vStu.size() << endl;
    ifs.close();

    ifs.open(TEACHER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "��ʦ�ļ���ȡʧ��" << endl;
        return;
    }
    //��ȡ��ʦ��Ϣ
    Teacher t;
    while (ifs >> t.m_Id && ifs >> t.m_Name && ifs >> t.m_Pwd) {
        vTea.push_back(t);
    }
    cout << "��ǰ��ʦ����Ϊ" << vTea.size() << endl;
    ifs.close();

    ifs.open(COMPUTER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "�����ļ���ȡʧ��" << endl;
        return;
    }
    //��ȡ������Ϣ
    computerRoom com;
    while(ifs>>com.m_ComId&&ifs>>com.m_MaxNum){
        vCom.push_back(com);
    }
    cout << "��ǰ��������Ϊ" << vCom.size() << endl;
    ifs.close();
}

bool Manager::checkRepeat(int id, int type) {
    if(type==1){
        //���ѧ��
        for(auto temp:vStu){
            if(temp.m_Id==id){
                return true;
            }
        }
    }else{
        //�����ʦ
        for(auto temp:vTea){
            if(temp.m_Id==id){
                return true;
            }
        }
    }
    return false;
}

void Manager::showPerson(){

    cout<<"��ѡ��鿴������:"<<endl;
    cout<<"1.�鿴����ѧ��"<<endl;
    cout<<"2.�鿴���н�ʦ"<<endl;

    int select=0;
    cin>>select;

    if(select==1){//�鿴ѧ��
        cout<<"����ѧ����Ϣ����:"<<endl;
        for(auto temp:vStu){
            cout<<"ѧ��/ְ����: "<<temp.m_Id<<" ����: "<<temp.m_Name<<" ����: "<<temp.m_Pwd<<endl;
        }
    }else{//�鿴��ʦ
        for(auto temp:vTea){
            cout<<"ѧ��/ְ����: "<<temp.m_Id<<" ����: "<<temp.m_Name<<" ����: "<<temp.m_Pwd<<endl;
        }
    }
    system("pause");
    system("cls");
}

void Manager::showComputer(){
    for(vector<computerRoom>::iterator it=vCom.begin();it!=vCom.end();it++){
        cout<<"�������: "<<it->m_ComId<<" �����������: "<<it->m_MaxNum<<endl;
    }
    system("pause");
    system("cls");
}

void Manager::cleanFile(){
    ofstream ofs;
    ofs.open(ORDER_FILE,ios::trunc);
    ofs.close();
    cout<<"ԤԼ��¼��ճɹ�"<<endl;
    system("pause");
    system("cls");
}
