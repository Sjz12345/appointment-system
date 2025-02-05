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

    //��ʼ��������Ϣ
    ifstream ifs;
    ifs.open(COMPUTER_FILE,ios::in);

    computerRoom com;
    while(ifs>>com.m_ComId&&ifs>>com.m_MaxNum){
        //���ļ��е���Ϣ��ȡ��������
        vCom.push_back(com);
    }
}

void Student:: operMenu(){
    cout << "��ӭѧ��" <<this->m_Name<<"��¼"<<endl;
    cout << endl;
    cout << "\t\t---------------------------------" << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            1.����ԤԼ            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            2.�鿴����ԤԼ            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            3.�鿴����ԤԼ            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            4.ȡ��ԤԼ            " << endl;
    cout << "\t\t" << endl;
    cout << "\t\t            0.ע����¼            " << endl;
    cout << "\t\t---------------------------------" << endl;
}

void Student::applyOrder(){
    cout<<"��������ʱ��Ϊ��һ������"<<endl;
    cout<<"����������ԤԼ��ʱ��: "<<endl;
    cout<<"1.��һ"<<endl;
    cout<<"2.�ܶ�"<<endl;
    cout<<"3.����"<<endl;
    cout<<"4.����"<<endl;
    cout<<"5.����"<<endl;

    int date=0;//����
    int interval=0;//ʱ���
    int room=0;//����

    while(true){
        cin>>date;
        if(date>=1&&date<=5)
            break;
        cout<<"��������,����������"<<endl;
    }

    cout<<"������ԤԼʱ���"<<endl;
    cout<<"1.����"<<endl;
    cout<<"2.����"<<endl;

    while(true){
        cin>>interval;
        if(interval>=1&&interval<=2)
            break;
        cout<<"��������,����������"<<endl;
    }

    cout<<"��ѡ�����:"<<endl;
    for(int i=0;i<vCom.size();i++){
        cout<<vCom[i].m_ComId<<"�Ż�������Ϊ: "<<vCom[i].m_MaxNum<<endl;
    }
    while(true){
        cin>>room;
        if(room>=1&&room<=vCom.size())
            break;
    }

    cout<<"ԤԼ�ύ�ɹ�!�����"<<endl;

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
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }

    for(int i=1;i<=of.m_Size;i++){
        if(atoi(of.m_orderData[i]["stuID"].c_str())==this->m_Id){
            cout<<"ԤԼʱ��: ��"<<of.m_orderData[i]["date"];
            cout<<" ʱ��: "<<(of.m_orderData[i]["interval"]=="1"?"����":"����");
            cout<<" ����: "<<of.m_orderData[i]["roomID"];
            string status = " ״̬: ";//0-ȡ����ԤԼ  1-�����  2-��ԤԼ  -1-ԤԼʧ��
            if(of.m_orderData[i]["status"]=="1"){

                status+="�����";

            }else if(of.m_orderData[i]["status"]=="2"){

                status+="ԤԼ�ɹ�";

            }else if(of.m_orderData[i]["status"]=="-1"){

                status+="ԤԼʧ��";

            }else{

                status+="ԤԼ��ȡ��";

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
            cout<<"��ԤԼ��¼"<<endl;
            system("pause");
            system("cls");
            return;
        }
    for(int i=1;i<=of.m_Size;i++){
            cout<<"ѧ��: "<<of.m_orderData[i]["stuID"]<<" "<<"����: "<<of.m_orderData[i]["stuName"]<<" ";
            cout<<"ԤԼʱ��: ��"<<of.m_orderData[i]["date"];
            cout<<" ʱ��: "<<(of.m_orderData[i]["interval"]=="1"?"����":"����");
            cout<<" ����: "<<of.m_orderData[i]["roomID"];
            string status = " ״̬: ";//0-ȡ����ԤԼ  1-�����  2-��ԤԼ  -1-ԤԼʧ��
            if(of.m_orderData[i]["status"]=="1"){

                status+="�����";

            }else if(of.m_orderData[i]["status"]=="2"){

                status+="ԤԼ�ɹ�";

            }else if(of.m_orderData[i]["status"]=="-1"){

                status+="ԤԼʧ��";

            }else{

                status+="ԤԼ��ȡ��";

            }
            cout<<status<<endl;
    }
    system("pause");
    system("cls");
}

void Student::cancleOrder(){
    orderFile of;
    if(of.m_Size==0){
        cout<<"��ԤԼ��¼"<<endl;
        system("pause");
        system("cls");
        return;
    }
    cout<<"����л�ԤԼ�ɹ��ļ�¼����ȡ��,������ȡ���ļ�¼"<<endl;
    vector<int>v;//�������������е��±���
    int index=1;
    for(int i=1;i<=of.m_Size;i++){
        //���ж�������ѧ��
        if(this->m_Id==atoi(of.m_orderData[i]["stuID"].c_str())){
            //��ɸѡ״̬  ����л�ԤԼ�ɹ�
            if(of.m_orderData[i]["status"]=="1"||of.m_orderData[i]["status"]=="2"){
                v.push_back(i);
                cout<<index++<<"��";
                cout<<"ԤԼʱ��: ��"<<of.m_orderData[i]["date"];
                cout<<" ʱ���: "<<(of.m_orderData[i]["interval"]=="1"?"����":"����");
                cout<<" �������: "<<of.m_orderData[i]["roomID"];
                string status = " ״̬: ";
                if(of.m_orderData[i]["status"]=="1"){
                    status+="�����";
                }else if(of.m_orderData[i]["status"]=="2"){
                    status+="ԤԼ�ɹ�";
                }
                cout<<status<<endl;
            }
        }
    }
    cout<<"������ȡ���ļ�¼, 0������"<<endl;
    int select=0;

    while(true){

        cin>>select;

        if(select>=0&&select<=v.size()){
            if(select==0){
                break;
            }else{
                of.m_orderData[v[select-1]]["status"]="0";
                of.updateOrder();
                cout<<"ԤԼ��ȡ��"<<endl;
                break;
            }
        }
        cout<<"��������,����������"<<endl;
    }
    system("pause");
    system("cls");
}