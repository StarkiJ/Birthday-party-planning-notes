#include <iostream>
using namespace std;

void getPlan(string birth, string today)
{
    int n; // �������
    // ׼��ת����int����
    string year, month, day;
    int birth_year, birth_month, birth_day, today_year, today_month, today_day;

    // ���������շֶ�
    year = birth.substr(0, 4);
    month = birth.substr(4, 2);
    day = birth.substr(6, 2);
    // ����atoiת����int����
    birth_year = atoi(year.c_str());
    birth_month = atoi(month.c_str());
    birth_day = atoi(day.c_str());

    // �ʼ���ʩ
    year = today.substr(0, 4);
    month = today.substr(4, 2);
    day = today.substr(6, 2);
    today_year = atoi(year.c_str());
    today_month = atoi(month.c_str());
    today_day = atoi(day.c_str());

    cout << birth_year << "." << birth_month << "." << birth_day << endl;
    cout << today_year << "." << today_month << "." << today_day << endl;

    if (birth_month < today_month)
    {
        // �����ڲ����м�
        if ((birth_month < 2 || (birth_month == 2 && birth_day < 29)) && (today_month > 2))
        {
            if (ifLeap(today_year))
            //�������ڲ�
            
        }
    }
}

bool ifLeap(int year)
{
    return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

int main()
{
    string birth, today; // �������ڣ����������
    int n;               // ���쵽�´����յ�����

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