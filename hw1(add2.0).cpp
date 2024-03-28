#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
using namespace std;

void getPlan(string birth, string today);
void ShowDate(tm time);
// void ShowDate(const tm *time);

// �ò����ɺγ����
int main()
{
    string birth, today; // �������ڣ����������
    int t, a, b, z;      // birth[t],today[t],a��b��ʾ�������ڵĳ���,zΪ year��int��ʽ
    string x, y, year;   // ��ʾ�ա��¡���

    cout << "��ã������ǡ����վۻ�ƻ���ǩ��" << endl;
    system("pause");

    // ����������ںͽ��������

label1: // �����ո�ʽ�������ʱ��ת������
    cout << "������������ڣ����磺20240227����" << endl;
    cin >> birth;

label2: // ���������ڸ�ʽ�������ʱ��ת������
    cout << "�������������ڣ�" << endl;
    cin >> today;

    a = birth.length();
    b = today.length();

    if (a != 8) // ���ڸ�ʽ��Ϊ8λ����
    {
        cout << "�������ڸ�ʽ�������������8λ����" << endl;
        goto label1;
    }

    if (b != 8)
    {
        cout << "�������ڸ�ʽ�������������8λ����" << endl;
        goto label2;
    }

    // �жϳ��������Ƿ���ȷ
    for (t = 0; t < a; t++) // ���ڵ�ÿһ��Ԫ�ص�ASCIIֵ�Ƿ���0-9��������������ȷ
    {
        if (birth[t] < '0' || birth[t] > '9')
        {
            cout << "�������������������������" << endl;
            goto label1;
        }
    }

    x = birth.substr(4, 2); // ��ʾ�·�

    if (x > "12") // �·ݲ����ܴ���12
    {
        cout << "�����·������������������" << endl;
        goto label1;
    }

    y = birth.substr(6, 2);    // ��ʾ����
    year = birth.substr(0, 4); // ��ʾ���

    if (x == "01" || x == "03" || x == "05" || x == "07" || x == "08" || x == "10" || x == "12")
    {
        if (y > "31") // �������ڲ����ܴ���31
        {
            cout << "�����·�Ϊ���£����������������������" << endl;
            goto label1;
        }
    }
    else if (x == "02")
    {
        z = atoi(year.c_str()); // ת����int��
        if (z % 4 == 0 && z % 100 != 0 || z % 400 == 0)
        {
            if (y > "29") // ����2�����ڲ����ܴ���29
            {
                cout << "�����·�Ϊ����2�£����������������������" << endl;
                goto label1;
            }
        }
        else
        {
            if (y > "28") // ƽ��2�����ڲ����ܴ���28
            {
                cout << "�����·�Ϊƽ��2�£����������������������" << endl;
                goto label1;
            }
        }
    }
    else if (y > "30") // С�����ڲ����ܴ���30
    {
        cout << "�����·�ΪС�£����������������������" << endl;
        goto label1;
    }

    // today���ж�ͬbirth
    for (t = 0; t < b; t++)
    {
        if (today[t] < '0' || today[t] > '9')
        {
            cout << "�������������������������" << endl;
            goto label2;
        }
    }

    x = today.substr(4, 2); // �·�

    if (x > "12")
    {
        cout << "���������·������������������" << endl;
        goto label2;
    }

    y = today.substr(6, 2);    // ��ʾ����
    year = today.substr(0, 4); // ��ʾ���

    if (x == "01" || x == "03" || x == "05" || x == "07" || x == "08" || x == "10" || x == "12")
    {
        if (y > "31") // �������ڲ����ܴ���31
        {
            cout << "�������ڴ��£����������������������" << endl;
            goto label2;
        }
    }
    else if (x == "02")
    {
        z = atoi(year.c_str()); // ת����int��
        if (z % 4 == 0 && z % 100 != 0 || z % 400 == 0)
        {
            if (y > "29") // ����2�����ڲ����ܴ���29
            {
                cout << "������������2�£����������������������" << endl;
                goto label2;
            }
        }
        else
        {
            if (y > "28") // ƽ��2�����ڲ����ܴ���28
            {
                cout << "��������ƽ��2�£����������������������" << endl;
                goto label2;
            }
        }
    }
    else if (y > "30") // С�����ڲ����ܴ���30
    {
        cout << "��������С�£����������������������" << endl;
        goto label2;
    }

    getPlan(birth, today);

    system("pause");
    return 0;
}

// �ò����ɽ�׿�����
void getPlan(string birth, string today)
{
    int n;  // ��ǰ����
    long x; // �������

    // ׼��ת����int����
    string year, month, day;
    // ��������Ǹ�ɵ�ģ�����ֵ�������
    tm birth_time = {}, today_time = {};

    // ���������շֶ�
    year = birth.substr(0, 4);
    month = birth.substr(4, 2);
    day = birth.substr(6, 2);
    // ����atoiת����int����
    birth_time.tm_year = atoi(year.c_str()) - 1900;
    birth_time.tm_mon = atoi(month.c_str()) - 1;
    birth_time.tm_mday = atoi(day.c_str());

    // �ʼ���ʩ
    year = today.substr(0, 4);
    month = today.substr(4, 2);
    day = today.substr(6, 2);
    today_time.tm_year = atoi(year.c_str()) - 1900;
    today_time.tm_mon = atoi(month.c_str()) - 1;
    today_time.tm_mday = atoi(day.c_str());

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
        tm *time = localtime(&ad_times);
        tm ad_time = *time;
        cout << "�ƻ�����Ϊ��";
        ShowDate(ad_time);

        // �����ƻ�����
        int week = ad_time.tm_wday;
        time_t plan_times = ad_times;
        tm plan_time;

        // �������һ���ܶ������ǰһ��������
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

        time = localtime(&plan_times);
        plan_time = *time;

        // cout << "ad_times:" << ad_times << endl;
        // cout << "plan_times:" << plan_times << endl;

        cout << "�ƻ�����Ϊ��";
        ShowDate(plan_time);
        system("pause");

        cout << "--------�������ʾ��--------" << endl;
        cout << "�´��������ڣ�";
        ShowDate(birth_time);
        cout << "��������������" << x << "��" << endl;
        cout << "�����´�����ǰ" << n << "������ڣ�";
        ShowDate(ad_time);
        cout << "�ƻ�����Ϊ��";
        ShowDate(plan_time);

        // if(plan_time.tm_mon + 1 > birth_time.tm_mon + 1)
        // {
        // cout << "�ƶ�����ʧ�ܣ��ƻ������ѹ��������ڣ��������ƶ�����" << endl;
        // }

        // if(plan_time.tm_mon + 1 == birth_time.tm_mon + 1 && plan_time.tm_mday > birth_time.tm_mday)
        // {
        // cout << "�ƶ�����ʧ�ܣ��ƻ������ѹ��������ڣ��������ƶ�����" << endl;
        // }

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
            break;
        }
    }
}

// ������ں���
void ShowDate(const tm time)
{
    cout << time.tm_year + 1900 << "." << time.tm_mon + 1 << "." << time.tm_mday << endl;
}
// void ShowDate(const tm *time)
// {
//     cout << time->tm_year + 1900 << "." << time->tm_mon + 1 << "." << time->tm_mday << endl;
// }
