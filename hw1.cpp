#include <iostream>
#include <ctime>
using namespace std;

void getPlan(string birth, string today);
void ShowDate(tm time);
// void ShowDate(const tm *time);

int main()
{
    string birth, today; // �������ڣ����������

    cout << "��ã������ǡ����վۻ�ƻ���ǩ��" << endl;
    system("pause");

    // ����������ںͽ��������
    cout << "������������ڣ����磺20240227����" << endl;
    cin >> birth;
    cout << "�������������ڣ�" << endl;
    cin >> today;

    getPlan(birth, today);

    system("pause");
    return 0;
}

void getPlan(string birth, string today)
{
    int x, n;      // �������
    bool loop = 1; // �Ƿ�����ȷ���ƻ�����

    // ׼��ת����int����
    string year, month, day;
    // ��������Ǹ�ɵ�ģ�����ֵ�������
    tm birth_time={}, today_time={};

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
    if ((birth_time.tm_mon < today_time.tm_mon) || (birth_time.tm_mon == today_time.tm_mon && birth_time.tm_mday <= today_time.tm_mday))
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

    while (loop)
    {
        cout << "�´��������ڣ�";
        ShowDate(birth_time);
        cout << "��������������" << x << "��" << endl;
        cout << "������ϣ����ǰ���������ۻ�ƻ���" << endl;
        cin >> n;

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
            plan_times -= (week * 86400);
        }
        // ��������������ġ������������һ������
        else if (week == 3 || week == 4 || week == 5)
        {
            cout << "�ƻ�����Ϊ��������-��" << week << "������������һ������" << endl;
            plan_times += ((6 - week) * 86400);
        }
        else
        {
            cout << "�ƻ�����Ϊ����" << week << "�����������" << endl;
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

        // ѯ���Ƿ���Ҫ����ȷ���ƻ�
        cout << "�Ƿ�����ȷ���ƻ����ڣ�(Y/N)" << endl;
        char choice;
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            loop = 1;
            cout << "-----����Ϊ���վۻ�ƻ��ƶ�����-----" << endl;
        }
        else
        {
            loop = 0;
            cout << "------���վۻ�ƻ����------" << endl;
            cout << "�����ƶ����ռƻ�������Ϊ��";
            ShowDate(plan_time);
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