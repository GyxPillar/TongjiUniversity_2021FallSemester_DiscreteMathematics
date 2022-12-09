// 2053385 高逸轩 //
#include <iostream>
#include <cstring>
#include <iomanip>
#include "matrix.h"
#include "input_tools.h"
using namespace std;

// 进入菜单，选择所求闭包类型，1为自反闭包，2为对称闭包，3为传递闭包，已保证健壮性
const int Menu()
{
    cout << endl << "输入序号选择对应算法：" << endl;
    cout << "1.自反闭包" << endl;
    cout << "2.对称闭包" << endl;
    cout << "3.传递闭包" << endl;
    cout << "请输入：";
    int ret = getint(1, 3, "序号输入错误，请重新输入：");
    return ret;
}
int main()
{
    // 得到关系矩阵顶点个数，通过getint函数保证了健壮性
    cout << "请输入关系矩阵顶点个数(0,1000): ";
    int vertexNumber;
    vertexNumber = getint(1, 999, "顶点个数输入错误，请重新输入:");

    // 设置关系矩阵内部信息，通过SetMatrix函数保证了健壮性
    RelationMatrix m(vertexNumber);
    m.SetMatrix();

    RelationMatrix m1;

    // 进入菜单选择所求闭包
    switch (Menu())
    {
    case 1:
        m1 = m.ReflexiveClosure(); // 1 自反闭包
        break;
    case 2:
        m1 = m.SymmetricClosure(); // 2 对称闭包
        break;
    case 3:
        m1 = m.TransitiveClosure();// 3 传递闭包
        break;
    default:
        cout << "程序运行错误！";
        exit(-1);
    }
    cout << endl << "所求关系闭包为：" << endl;
    m1.PrintMatrix();

    return 0;
}