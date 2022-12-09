// 2053385 高逸轩 //
#include <iostream>
#include <cstring>
#include "input_tools.h"
using namespace std;

// 得到一个[ minNum，maxNum ]的数字，进行了输入错误处理，保证健壮性
int getint(const int minNum, const int maxNum, const string errorTips)
{
    int retNum = INT_MIN;
    while (1)
    {
        cin >> retNum;
        if (cin.fail() || retNum < minNum || retNum > maxNum) // 若输入变量类型不同或数字不在要求范围内
        {
            cin.clear();
            cin.ignore(1024, '\n');                           // 清除缓存区
            cout << errorTips;                                // 给出错误输入的提示
            continue;
        }
        break;
    }
    return retNum;
}