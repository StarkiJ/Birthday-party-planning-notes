#include <iostream>
using namespace std;

void getPlan(string birth, string today)
{
    int n; // 差距天数
    // 准备转换成int类型
    string year, month, day;
    int birth_year, birth_month, birth_day, today_year, today_month, today_day;

    // 按照年月日分段
    year = birth.substr(0, 4);
    month = birth.substr(4, 2);
    day = birth.substr(6, 2);
    // 利用atoi转换成int类型
    birth_year = atoi(year.c_str());
    birth_month = atoi(month.c_str());
    birth_day = atoi(day.c_str());

    // 故技重施
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
        // 二月在不在中间
        if ((birth_month < 2 || (birth_month == 2 && birth_day < 29)) && (today_month > 2))
        {
            if (ifLeap(today_year))
            //计算日期差
            
        }
    }
}

bool ifLeap(int year)
{
    return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

int main()
{
    string birth, today; // 出生日期，今天的日期
    int n;               // 今天到下次生日的天数

    cout << "你好，这里是【生日聚会计划便签】" << endl;
    system("pause");

    // 输入出生日期和今天的日期
    cout << "请输入出生日期（例如：20240227）：" << endl;
    cin >> birth;
    cout << "请输入今天的日期：" << endl;
    cin >> today;

    getPlan(birth, today);

    system("pause");
    return 0;
}