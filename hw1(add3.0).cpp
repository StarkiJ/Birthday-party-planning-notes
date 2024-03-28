#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class People
{
public:
    People()
    {
        string name = "";
        string relation = "";
        long birth_times = 0;
        long plan_times = 0;
    }
    People(string name, string relation, long birth_times)
    {
        this->name = name;
        this->relation = relation;
        this->birth_times = birth_times;
        this->plan_times = 0;
    }
    string name;
    string relation;
    time_t birth_times;
    time_t plan_times;
};

void getPlan(People &role);
People addRole();
void ShowDate(const tm time);
void ShowRole(const People role);
void ShowAllRoles(vector<People> roles);
bool isLegalDate(string date);
time_t getDate(string date);
void readFile(vector<People> &roles);
void writeFile(vector<People> roles);

int main()
{
    int id;
    People role;
    vector<People> roles;
    readFile(roles); // ���ļ���ʱ������

    cout << "��ã������ǡ����վۻ�ƻ���ǩ��" << endl;

    while (1)
    {
        // �����ǰ������Ϣ
        if (roles.size() != 0)
        {
            cout << "������Ŀǰ������Ϣ��" << endl;
            cout << "���\t\t����\t\t��ϵ\t\t��������\t\t�ƻ�����" << endl;
            for (int i = 0; i < roles.size(); i++)
            {
                cout << "��" << i + 1 << "λ\t\t";
                ShowRole(roles[i]);
            }
            cout << endl;
        }
        else
        {
            cout << "���޼ƻ�����" << endl;
        }
        system("pause");

        // �ƶ��ƻ�
        while (1)
        {
            cout << "��ѡ��Ŀ�����ѣ�������������ţ�������0�����µ����ѣ�" << endl;
            cin >> id;
            /*��������ѡ�����ѻ��������µ�����*/
            // ���ѡ�������µ�����
            if (id == 0)
            {
                role = addRole();
                getPlan(role);
                roles.push_back(role);
            }
            else if (id > 0 && id <= roles.size())
            {
                getPlan(roles[id - 1]);
            }
            else
            {
                cout << "������������������" << endl;
                continue;
            }

            break;
        }

        cout << "---------------------------" << endl;
        cout << "�ƶ��ƻ��ɹ�" << endl;
        cout << "�Ƿ�Ϊ���������ƶ��ƻ���(Y/N)" << endl;
        char choice;
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            cout << "------�ƶ��ƻ���������------" << endl;
            continue;
        }
        else
        {
            cout << "------�ƶ��ƻ��������------" << endl;
            break;
        }
    }

    // ���ȫ�����ƶ��ƻ���������Ϣ
    ShowAllRoles(roles);

    writeFile(roles); // д�ļ���ʱ������

    system("pause");
    return 0;
}

// �ò����ɽ�׿�����
// �ƶ����ռƻ�
void getPlan(People &role)
{
    int n;  // ��ǰ����
    long x; // �������
    string today;

    tm birth_time = *localtime(&role.birth_times);
    tm today_time = {};

    // ���뵱ǰ����
    while (1)
    {
        cout << "�������������ڣ�" << endl;
        cin >> today;
        if (isLegalDate(today))
        {
            time_t today_times = getDate(today);
            today_time = *localtime(&today_times);
            break;
        }
        else
        {
            continue;
        }
    }

    // cout << birth_time.tm_year + 1900 << "." << birth_time.tm_mon + 1 << "." << birth_time.tm_mday << endl;
    // cout << today_time.tm_year + 1900 << "." << today_time.tm_mon + 1 << "." << today_time.tm_mday << endl;

    // �ж��´������ڽ��껹������
    birth_time.tm_year = today_time.tm_year;
    if ((birth_time.tm_mon < today_time.tm_mon) ||
        (birth_time.tm_mon == today_time.tm_mon && birth_time.tm_mday <= today_time.tm_mday))
    {
        birth_time.tm_year++;
    }

    // ����ʱ���
    time_t birth_times = mktime(&birth_time);
    time_t today_times = mktime(&today_time);

    x = difftime(birth_times, today_times) / 86400;

    // cout << "birth_times:" << birth_times << endl;
    // cout << "today_times:" << today_times << endl;

    cout << "���쵽�´����ջ���" << x << "��" << endl;
    cout << "-----׼��Ϊ���վۻ�ƻ��ƶ�����-----" << endl;
    system("pause");

    while (1)
    {
        cout << "�´��������ڣ�";
        ShowDate(birth_time);
        cout << endl;
        cout << "��������������" << x << "��" << endl;
        cout << "������ϣ����ǰ���������ۻ�ƻ���" << endl;
        cin >> n;
        if (n > x)
        {
            cout << "���ƻ����ڲ������ڵ�ǰ���ڣ������¼ƻ���" << endl;
            continue;
        }

        // ��������ƻ�����
        time_t ad_times = birth_times - n * 86400;
        // tm *ad_time = localtime(&ad_times);
        tm ad_time = *localtime(&ad_times);
        cout << "�ƻ�����Ϊ��";
        ShowDate(ad_time);
        cout << endl;

        // �����ƻ�����
        int week = ad_time.tm_wday;
        time_t plan_times = ad_times;
        tm plan_time;

        // ������Ͷ��ڼ��ڻ�������
        if (ad_time.tm_mon == 4 && ad_time.tm_mday >= 1 && ad_time.tm_mday <= 3)
        {
            cout << "�ƻ�ʱ�䴦���Ͷ��ڼ��ڣ��������" << endl;
        }
        else if (ad_time.tm_mon == 9 && ad_time.tm_mday >= 1 && ad_time.tm_mday <= 7)
        {
            cout << "�ƻ�ʱ�䴦�ڹ���ڼ��ڣ��������" << endl;
        }
        else
        { // �������һ���ܶ������ǰһ��������
            if (week == 1 || week == 2)
            {
                cout << "�ƻ�����Ϊ��������-��" << week << "����������ǰһ������" << endl;
                plan_times -= ((week + 1) * 86400);
            }
            // ��������������ġ������������һ������
            else if (week == 3 || week == 4 || week == 5)
            {
                cout << "�ƻ�����Ϊ��������-��" << week << "������������һ������" << endl;
                plan_times += ((6 - week) * 86400);
            }
            else if (week == 0)
            {
                cout << "�ƻ�����Ϊ�����ա����������" << endl;
            }
            else
            {
                cout << "�ƻ�����Ϊ����6�����������" << endl;
            }
        }

        // �жϼƻ�����ʱ���Ƿ񱻵������������Ժ�
        if (plan_times > birth_times)
        {
            cout << "�ƻ������������Ժ󣬵���������ǰ" << endl;
            plan_times -= 7 * 86400;
        }

        // �����пӣ��öϵ��ҵ��ط�֮���˼�������,��ĥ���ú�������������ҵ��˽��
        /*����ʹ��localtime()�Ľ�����Ƿ�����ͬ��ʱ�䣬����õ�����Ҫ��������ͬ��ʱ�䡣
          localtime()����idָ���ָ��ͬһ�����������㲻�ܵ����ζ��Ƿ��ظ�ָ��ָ������򣬲����ġ�*/
        // tm *plan_time = localtime(&plan_times);

        plan_time = *localtime(&plan_times);

        // cout << "ad_times:" << ad_times << endl;
        // cout << "plan_times:" << plan_times << endl;

        cout << "�ƻ�����Ϊ��";
        ShowDate(plan_time);
        cout << endl;
        system("pause");

        // �����ʾ����
        cout << "-------------------------------" << endl;
        cout << "----------�������ʾ��----------" << endl;
        cout << "-------------------------------" << endl;
        cout << "������" << role.name << endl;
        cout << "��ϵ��" << role.relation << endl;
        cout << "�������ڣ�";
        ShowDate(*localtime(&role.birth_times));
        cout << endl;
        cout << "�´��������ڣ�";
        ShowDate(birth_time);
        cout << endl;
        cout << "��������������" << x << "��" << endl;
        cout << "�����´�����ǰ" << n << "������ڣ�";
        ShowDate(ad_time);
        cout << endl;
        cout << "�ƻ�����Ϊ��";
        ShowDate(plan_time);
        cout << endl;
        cout << endl;

        // ѯ���Ƿ���Ҫ����ȷ���ƻ�
        cout << "�Ƿ�����ȷ���ƻ����ڣ�(Y/N)" << endl;
        char choice;
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            cout << "-----����Ϊ���վۻ�ƻ��ƶ�����-----" << endl;
            continue;
        }
        else
        {
            cout << "------���վۻ�ƻ����------" << endl;
            cout << "�����ƶ����ռƻ�������Ϊ��";
            ShowDate(plan_time);
            cout << endl;
            role.plan_times = plan_times;
            break;
        }
    }
}

// �����µ�����
People addRole()
{
    string name, relation, birth; // ��������ϵ������
    cout << "���������ѵ�������" << endl;
    cin >> name;

    cout << "���������������Ĺ�ϵ��" << endl;
    cin >> relation;

    // �����������
    while (1)
    {
        cout << "���������ѵ����գ����磺20240227����" << endl;
        cin >> birth;
        if (isLegalDate(birth))
        {
            // ��������
            People role(name, relation, getDate(birth));
            // ��Ӷ���
            return role;
        }
        else
        {
            continue;
        }
    }
}

// ��string����ת��Ϊtime_t����
time_t getDate(string date)
{
    // ׼��ת����int����
    string year, month, day;
    // ��������Ǹ�ɵ�ģ�����ֵ�������
    tm date_time = {};

    // ���������շֶ�
    year = date.substr(0, 4);
    month = date.substr(4, 2);
    day = date.substr(6, 2);
    // ����atoiת����int����
    date_time.tm_year = atoi(year.c_str()) - 1900;
    date_time.tm_mon = atoi(month.c_str()) - 1;
    date_time.tm_mday = atoi(day.c_str());

    // ��tmת��Ϊtime_t����
    time_t date_times = mktime(&date_time);

    return date_times;
}

// ������ں���
void ShowDate(const tm time)
{
    cout << time.tm_year + 1900 << "."
         << time.tm_mon + 1 << "."
         << time.tm_mday << "\t\t";
}

// ���������Ϣ
void ShowRole(const People role)
{
    cout << left << setw(16) << role.name << setw(16) << role.relation;
    ShowDate(*localtime(&role.birth_times));
    if (role.plan_times != 0)
    {
        ShowDate(*localtime(&role.plan_times));
    }
    cout << endl;
}

// ����������ƶ��ƻ���������Ϣ
void ShowAllRoles(vector<People> roles)
{
    cout << "-------------------------" << endl;
    cout << "�Ѿ�ȷ���ˡ��ƶ����վۻ�ƻ����ڡ����������ѵ���Ϣ" << endl;
    cout << "���\t\t����\t\t��ϵ\t\t��������\t\t�ƻ�����" << endl;
    for (int i = 0; i < roles.size(); i++)
    {
        if (roles[i].plan_times != 0)
        {
            cout << "��" << i + 1 << "λ\t\t";
            ShowRole(roles[i]);
        }
    }
}

// �ò����ɺγ����
bool isLegalDate(string date)
{
    int a = date.length();
    if (date.length() != 8) // ���ڸ�ʽ��Ϊ8λ����
    {
        cout << "���ڸ�ʽ�������������8λ����" << endl;
        return 0;
    }

    string day = date.substr(6, 2);   // ��ʾ����
    string month = date.substr(4, 2); // ��ʾ�·�
    string year = date.substr(0, 4);  // ��ʾ���
    int z;

    // �жϳ��������Ƿ���ȷ
    for (int t = 0; t < a; t++) // ���ڵ�ÿһ��Ԫ�ص�ASCIIֵ�Ƿ���0-9��������������ȷ
    {
        if (date[t] < '0' || date[t] > '9')
        {
            cout << "���������������������" << endl;
            return 0;
        }
    }

    if (month > "12") // �·ݲ����ܴ���12
    {
        cout << "�·������������������" << endl;
        return 0;
    }

    if (month == "01" || month == "03" || month == "05" || month == "07" || month == "08" || month == "10" || month == "12")
    {
        if (day > "31") // �������ڲ����ܴ���31
        {
            cout << "�·�Ϊ���£����������������������" << endl;
            return 0;
        }
    }
    else if (month == "02")
    {
        z = atoi(year.c_str()); // ת����int��
        if (z % 4 == 0 && z % 100 != 0 || z % 400 == 0)
        {
            if (day > "29") // ����2�����ڲ����ܴ���29
            {
                cout << "�·�Ϊ����2�£����������������������" << endl;
                return 0;
            }
        }
        else
        {
            if (day > "28") // ƽ��2�����ڲ����ܴ���28
            {
                cout << "�·�Ϊƽ��2�£����������������������" << endl;
                return 0;
            }
        }
    }
    else if (day > "30") // С�����ڲ����ܴ���30
    {
        cout << "�·�ΪС�£����������������������" << endl;
        return 0;
    }

    return 1;
}

void readFile(vector<People> &roles) // ��ȡ�洢�ļƻ�
{
    ifstream ifs;
    ifs.open("plan.txt", ios::in);
    int n = 0; // ��������������ŵ�ֵ
    ifs >> n;
    if (n != 0)
    {
        for (int i = 0; i < n; i++)
        {
            People s;
            ifs >> s.name >> s.relation >> s.birth_times >> s.plan_times;
            roles.push_back(s);
        }
    }
    else
    {
        cout << "����¼����Ϣ" << endl;
    }
    ifs.close();
}

void writeFile(vector<People> roles) // �����ƶ��õļƻ�
{
    ofstream ofs("plan.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open("plan.txt", ios::out | ios::app);
    if (!ofs.is_open())
    {
        cout << "���ļ�ʧ��" << endl;
    }
    ofs << roles.size() << endl; // ��д����������
    for (int i = 0; i < roles.size(); i++)
    {
        ofs << roles[i].name << " " << roles[i].relation << " " << roles[i].birth_times
            << " " << roles[i].plan_times << endl;
    }
    ofs.close();
}
