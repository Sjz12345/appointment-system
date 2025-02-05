#include <iostream>
#include "identity.h"
#include <fstream>
#include <string>
#include "globalFile.h"
#include "student.h"
#include "manager.h"
#include "teacher.h"
using namespace std;
//�������Ա�Ӳ˵�
void managerMenu(Identity * &manager){
    while(true){
        //���ù���Ա�Ӳ˵�
        manager->operMenu();
         //����ָ��ת��Ϊ����
        Manager* man = (Manager*)manager;
        int select=0;

        cin>>select;
        if(select==1){//����˺�
            man->addPerson();

        }else if(select==2){//�鿴�˺�
            man->showPerson();

        }else if(select==3){//�鿴����
            man->showComputer();

        }else if(select==4){//���ԤԼ
            man->cleanFile();

        }else{
            delete manager;//���ٶ�������
            cout<<"ע���ɹ�"<<endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
//����ѧ���Ӳ˵�
void studentMenu(Identity * &student){
    while(true){
        //���ù���Ա�Ӳ˵�
        student->operMenu();
        //����ָ��ת��Ϊ����
        Student* man = (Student*)student;
        int select=0;

        cin>>select;
        if(select==1){//����ԤԼ
            man->applyOrder();

        }else if(select==2){//�鿴����ԤԼ
            man->showMyOrder();

        }else if(select==3){//�鿴����ԤԼ
            man->showAllOrder();

        }else if(select==4){//ȡ��ԤԼ
            man->cancleOrder();

        }else{
            delete student;//���ٶ�������
            cout<<"ע���ɹ�"<<endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
//�����ʦ�Ӳ˵�
void teacherMenu(Identity * &teacher){
    while(true){
        //���ý�ʦ�Ӳ˵�
        teacher->operMenu();
        //����ָ��ת��Ϊ����
        Teacher* man = (Teacher*)teacher;
        int select=0;

        cin>>select;
        if(select==1){//�鿴����ԤԼ
            man->showAllOrder();

        }else if(select==2){//���ԤԼ
            man->validOrder();

        }else{
            delete teacher;//���ٶ�������
            cout<<"ע���ɹ�"<<endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
//��¼����     ����һ�������ļ���   �������������������
void LoginIN(string fileName,int type){

    //��̬������ָ��ָ���������
     Identity* person =NULL;
    //���ļ�
    ifstream ifs;
    ifs.open(fileName,ios::in);

    if(!ifs.is_open()){
        cout<<"�ļ�������"<<endl;
        ifs.close();
        return ;
    }

    int id=0;
    string name;
    string pwd;

    if(type==1){//ѧ��
        cout<<"����������ѧ��"<<endl;
        cin>>id;
    }else if(type==2){//��ʦ
        cout<<"����������ְ����"<<endl;
        cin>>id;
    }

    cout<<"�������û���"<<endl;
    cin>>name;
    cout<<"����������"<<endl;
    cin>>pwd;

    if(type==1){//ѧ�������֤
        int fId;
        string fName;
        string fPwd;
        while(ifs>>fId&&ifs>>fName&&ifs>>fPwd){
            //cout<<fId<<" "<<fName<<" "<<fPwd<<endl;
            //��洢��Ϣ���бȽ�
            if(fId==id&&fName==name&&fPwd==pwd){
                cout<<"ѧ����֤��¼�ɹ�!"<<endl;
                system("pause");
                system("cls");
                person = new Student(id,name,pwd);
                //����ѧ������Ӳ˵�
                studentMenu(person);
                return;
            }
        }
    }else if(type==2){//��ʦ�����֤
        int fId;
        string fName;
        string fPwd;
        while(ifs>>fId&&ifs>>fName&&ifs>>fPwd){
            //cout<<fId<<" "<<fName<<" "<<fPwd<<endl;
            //��洢��Ϣ���бȽ�
            if(fId==id&&fName==name&&fPwd==pwd){
                cout<<"��ʦ��֤��¼�ɹ�!"<<endl;
                system("pause");
                system("cls");
                person = new Teacher(id,name,pwd);
                //�����ʦ����Ӳ˵�
                teacherMenu(person);
                return;
            }
        }
    }else if(type==3){//����Ա�����֤
        string fName;
        string fPwd;
        while(ifs>>fName&&ifs>>fPwd){
            //cout<<fId<<" "<<fName<<" "<<fPwd<<endl;
            //��洢��Ϣ���бȽ�
            if(fName==name&&fPwd==pwd){
                cout<<"����Ա��֤��¼�ɹ�!"<<endl;
                system("pause");
                system("cls");
                person = new Manager(name,pwd);
                //�������Ա����Ӳ˵�
                managerMenu(person);
                return;
            }
        }
    }

    cout<<"�����֤ʧ��"<<endl;
    system("pause");
    system("cls");
}

int main() {
    int Select;
    while(true){
        cout << "=========================��ӭ�������ԤԼϵͳ=========================" << endl;
        cout << "�������������" << endl;
        cout << "\t\t---------------------------------" << endl;
        cout << "\t\t" << endl;
        cout << "\t\t            1.ѧ������            " << endl;
        cout << "\t\t" << endl;
        cout << "\t\t            2.��ʦ            " << endl;
        cout << "\t\t" << endl;
        cout << "\t\t            3.����Ա            " << endl;
        cout << "\t\t" << endl;
        cout << "\t\t            0.�˳�            " << endl;
        cout << "\t\t---------------------------------" << endl;

        cin>>Select;

        switch (Select) {
            case 1://ѧ����¼
                LoginIN(STUDENT_FILE,1);
                break;
            case 2://��ʦ��¼
                LoginIN(TEACHER_FILE,2);
                break;
            case 3://����Ա��¼
                LoginIN(ADMIN_FILE,3);
                break;
            case 0:
                cout<<"�˳��ɹ�"<<endl;
                system("pause");
                return 0;
            default:
                cout<<"������������������:"<<endl;
                system("pause");
                system("cls");
                break;

        }
    }
}
