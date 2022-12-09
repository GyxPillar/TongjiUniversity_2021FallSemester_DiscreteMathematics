// 2053385 高逸轩 //
#include <iostream>
#include <cstring>
#include <iomanip>
#include "matrix.h"
#include "input_tools.h"
using namespace std;

int main()
{
    // 得到关系矩阵顶点个数，通过getint函数保证了健壮性
    cout << "请输入关系矩阵顶点个数(0,1000): ";
    int vertexNumber;
    vertexNumber = getint(1, 999, "顶点个数输入错误，请重新输入:");

    // 设置关系矩阵内部信息，通过SetMatrix函数保证了健壮性
    RelationMatrix m(vertexNumber);
    m.SetMatrix();

    // 通过Warshall算法求传递闭包并输出
    RelationMatrix m1 = m.Warshall();
    cout << endl << "传递闭包对应的关系矩阵为:" << endl;
    m1.PrintMatrix();

    return 0;
}