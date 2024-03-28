#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <vector>
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

int main()
{
    int id;
    People role;
    vector<People> roles;

    cout << "你好，这里是【生日聚会计划便签】" << endl;

    while (1)
    { // 输出当前亲友信息
        cout << "以下是目前亲友信息：" << endl;
        cout << "序号\t\t姓名\t\t关系\t\t生日\t\t计划日期" << endl;
        for (int i = 0; i < roles.size(); i++)
        {
            cout << "第" << i + 1 << "位\t\t";
            ShowRole(roles[i]);
        }
        cout << endl;
        system("pause");

        // 制定计划
        while (1)
        {
            cout << "请选择目标亲友（请输入亲友序号，或输入0增加新的亲友）" << endl;
            cin >> id;
            /*根据输入选择亲友或者增加新的亲友*/
            // 如果选择增加新的亲友
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
                cout << "输入有误，请重新输入" << endl;
                continue;
            }

            break;
        }

        cout << "---------------------------" << endl;
        cout << "制定计划成功" << endl;
        cout << "是否为其他亲友制定计划？(Y/N)" << endl;
        char choice;
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            cout << "------制定计划程序重启------" << endl;
            continue;
        }
        else
        {
            cout << "------制定计划程序结束------" << endl;
            break;
        }
    }

    // 输出全部已制定计划的亲友信息
    ShowAllRoles(roles);

    system("pause");
    return 0;
}

// 该部分由蒋卓鑫完成
// 制定生日计划
void getPlan(People &role)
{
    int n;  // 提前天数
    long x; // 差距天数
    string today;

    tm birth_time = *localtime(&role.birth_times);
    tm today_time = {};

    // 输入当前日期
    while (1)
    {
        cout << "请输入今天的日期：" << endl;
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

    // 判断下次生日在今年还是明年
    birth_time.tm_year = today_time.tm_year;
    if ((birth_time.tm_mon < today_time.tm_mon) ||
        (birth_time.tm_mon == today_time.tm_mon && birth_time.tm_mday <= today_time.tm_mday))
    {
        birth_time.tm_year++;
    }

    // 计算时间差
    time_t birth_times = mktime(&birth_time);
    time_t today_times = mktime(&today_time);

    x = difftime(birth_times, today_times) / 86400;

    // cout << "birth_times:" << birth_times << endl;
    // cout << "today_times:" << today_times << endl;

    cout << "今天到下次生日还有" << x << "天" << endl;
    cout << "-----准备为生日聚会计划制定日期-----" << endl;
    system("pause");

    while (1)
    {
        cout << "下次生日日期：";
        ShowDate(birth_time);
        cout << endl;
        cout << "距离今天的天数：" << x << "天" << endl;
        cout << "请问您希望提前多少天做聚会计划？" << endl;
        cin >> n;
        if (n > x)
        {
            cout << "！计划日期不能早于当前日期，请重新计划！" << endl;
            continue;
        }

        // 计算初步计划日期
        time_t ad_times = birth_times - n * 86400;
        // tm *ad_time = localtime(&ad_times);
        tm ad_time = *localtime(&ad_times);
        cout << "计划日期为：";
        ShowDate(ad_time);
        cout << endl;

        // 调整计划日期
        int week = ad_time.tm_wday;
        time_t plan_times = ad_times;
        tm plan_time;

        // 如果在劳动节假期或国庆假期
        if (ad_time.tm_mon == 4 && ad_time.tm_mday >= 1 && ad_time.tm_mday <= 3)
        {
            cout << "计划时间处于劳动节假期，无需调整" << endl;
        }
        else if (ad_time.tm_mon == 9 && ad_time.tm_mday >= 1 && ad_time.tm_mday <= 7)
        {
            cout << "计划时间处于国庆节假期，无需调整" << endl;
        }
        else
        { // 如果是周一、周二则调到前一个的周六
            if (week == 1 || week == 2)
            {
                cout << "计划日期为【工作日-周" << week << "】，调整到前一个周六" << endl;
                plan_times -= ((week + 1) * 86400);
            }
            // 如果是周三、周四、周五则调到后一个周六
            else if (week == 3 || week == 4 || week == 5)
            {
                cout << "计划日期为【工作日-周" << week << "】，调整到后一个周六" << endl;
                plan_times += ((6 - week) * 86400);
            }
            else if (week == 0)
            {
                cout << "计划日期为【周日】，无需调整" << endl;
            }
            else
            {
                cout << "计划日期为【周6】，无需调整" << endl;
            }
        }

        // 判断计划日期时间是否被调整到了生日以后
        if (plan_times > birth_times)
        {
            cout << "计划日期在生日以后，调整到生日前" << endl;
            plan_times -= 7 * 86400;
        }

        // 这里有坑，用断点找到地方之后百思不得其解,琢磨良久后放弃，在网上找到了解答：
        /*连续使用localtime()的结果就是返回相同的时间，不会得到你想要的两个不同的时间。
          localtime()返回id指针会指向同一个区域，所以你不管调几次都是返回该指针指向的区域，不会变的。*/
        // tm *plan_time = localtime(&plan_times);

        plan_time = *localtime(&plan_times);

        // cout << "ad_times:" << ad_times << endl;
        // cout << "plan_times:" << plan_times << endl;

        cout << "计划日期为：";
        ShowDate(plan_time);
        cout << endl;
        system("pause");

        // 结果显示界面
        cout << "-------------------------------" << endl;
        cout << "----------【结果显示】----------" << endl;
        cout << "-------------------------------" << endl;
        cout << "姓名：" << role.name << endl;
        cout << "关系：" << role.relation << endl;
        cout << "出生日期：";
        ShowDate(*localtime(&role.birth_times));
        cout << endl;
        cout << "下次生日日期：";
        ShowDate(birth_time);
        cout << endl;
        cout << "距离今天的天数：" << x << "天" << endl;
        cout << "距离下次生日前" << n << "天的日期：";
        ShowDate(ad_time);
        cout << endl;
        cout << "计划日期为：";
        ShowDate(plan_time);
        cout << endl;
        cout << endl;

        // 询问是否需要重新确定计划
        cout << "是否重新确定计划日期？(Y/N)" << endl;
        char choice;
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            cout << "-----重新为生日聚会计划制定日期-----" << endl;
            continue;
        }
        else
        {
            cout << "------生日聚会计划完成------" << endl;
            cout << "最终制定生日计划的日期为：";
            ShowDate(plan_time);
            cout << endl;
            role.plan_times = plan_times;
            break;
        }
    }
}

// 增加新的亲友
People addRole()
{
    string name, relation, birth; // 姓名，关系，生日
    cout << "请输入亲友的姓名：" << endl;
    cin >> name;

    cout << "请输入亲友与您的关系：" << endl;
    cin >> relation;

    // 输入出生日期
    while (1)
    {
        cout << "请输入亲友的生日（例如：20240227）：" << endl;
        cin >> birth;
        if (isLegalDate(birth))
        {
            // 创建对象
            People role(name, relation, getDate(birth));
            // 添加对象
            return role;
        }
        else
        {
            continue;
        }
    }
}

// 将string日期转换为time_t日期
time_t getDate(string date)
{
    // 准备转换成int类型
    string year, month, day;
    // 这玩意儿是个傻的，不赋值会出问题
    tm date_time = {};

    // 按照年月日分段
    year = date.substr(0, 4);
    month = date.substr(4, 2);
    day = date.substr(6, 2);
    // 利用atoi转换成int类型
    date_time.tm_year = atoi(year.c_str()) - 1900;
    date_time.tm_mon = atoi(month.c_str()) - 1;
    date_time.tm_mday = atoi(day.c_str());

    // 将tm转换为time_t返回
    time_t date_times = mktime(&date_time);

    return date_times;
}

// 输出日期函数
void ShowDate(const tm time)
{
    cout << time.tm_year + 1900 << "."
         << time.tm_mon + 1 << "."
         << time.tm_mday << "\t\t";
}

// 输出亲友信息
void ShowRole(const People role)
{
    cout << role.name << "\t\t" << role.relation << "\t\t";
    ShowDate(*localtime(&role.birth_times));
    if (role.plan_times != 0)
    {
        ShowDate(*localtime(&role.plan_times));
    }
    cout << endl;
}

// 输出所有已制定计划的亲友信息
void ShowAllRoles(vector<People> roles)
{
    cout << "-------------------------" << endl;
    cout << "已经确定了“制定生日聚会计划日期”的所有亲友的信息" << endl;
    cout << "序号\t\t姓名\t\t关系\t\t生日\t\t计划日期" << endl;
    for (int i = 0; i < roles.size(); i++)
    {
        if (roles[i].plan_times != 0)
        {
            cout << "第" << i + 1 << "位\t\t";
            ShowRole(roles[i]);
        }
    }
}

// 该部分由何成完成
bool isLegalDate(string date)
{
    int a = date.length();
    string day = date.substr(6, 2);   // 表示几号
    string month = date.substr(4, 2); // 表示月份
    string year = date.substr(0, 4);  // 表示年份
    int z;

    if (a != 8) // 日期格式定为8位数字
    {
        cout << "日期格式输入错误，请输入8位数字" << endl;
        return 0;
    }

    // 判断出生日期是否正确
    for (int t = 0; t < a; t++) // 日期的每一个元素的ASCII值是否在0-9，如果是则初步正确
    {
        if (date[t] < '0' || date[t] > '9')
        {
            cout << "日期输入错误，请输入数字" << endl;
            return 0;
        }
    }

    if (month > "12") // 月份不可能大于12
    {
        cout << "月份输入错误，请重新输入" << endl;
        return 0;
    }

    if (month == "01" || month == "03" || month == "05" || month == "07" || month == "08" || month == "10" || month == "12")
    {
        if (day > "31") // 大月日期不可能大于31
        {
            cout << "月份为大月，日期输入错误，请重新输入" << endl;
            return 0;
        }
    }
    else if (month == "02")
    {
        z = atoi(year.c_str()); // 转换成int类
        if (z % 4 == 0 && z % 100 != 0 || z % 400 == 0)
        {
            if (day > "29") // 闰年2月日期不可能大于29
            {
                cout << "月份为闰年2月，日期输入错误，请重新输入" << endl;
                return 0;
            }
        }
        else
        {
            if (day > "28") // 平年2月日期不可能大于28
            {
                cout << "月份为平年2月，日期输入错误，请重新输入" << endl;
                return 0;
            }
        }
    }
    else if (day > "30") // 小月日期不可能大于30
    {
        cout << "月份为小月，日期输入错误，请重新输入" << endl;
        return 0;
    }

    return 1;
}