// 2053385 高逸轩 //
#include <iostream>
#include <cstring>
#include <iomanip>
#include "matrix.h"
#include "input_tools.h"
using namespace std;
/* 基类Matrix函数实现 */

// 默认构造函数，根据给出的行列数为二维数组开辟空间，同时初始化为0
Matrix::Matrix(const int n, const int m) :row(n), column(m)
{
    nearArray = new int* [row];                         // 为二维数组指针申请一维空间

    FOR(i, 0, row)
    {
        nearArray[i] = new int[column];                 // 为每个一维数组开辟空间
        memset(nearArray[i], 0, sizeof(int) * column);  // 矩阵初始值设为0
    }
}

// 复制构造函数
Matrix::Matrix(const Matrix& currentMatrix)
{
    if (currentMatrix.nearArray == nearArray) return;   // 复制对象为本身

    row = currentMatrix.row;                            // 行列复制
    column = currentMatrix.column;

    nearArray = new int* [row];                         // 申请空间，深构造
    FOR(i, 0, row)
        nearArray[i] = new int[column];

    FOR(i, 0, row)                                      // 内部信息复制
        FOR(j, 0, column)
        nearArray[i][j] = currentMatrix.nearArray[i][j];
}

// 赋值构造函数
Matrix& Matrix::operator=(const Matrix& currentMatrix)
{
    if (currentMatrix.nearArray == nearArray) return *this;

    // 在赋值前先将原来的空间释放，避免发生内存丢失错误
    FOR(i, 0, row)
        delete[] nearArray[i];

    delete[] nearArray;

    row = currentMatrix.row;                                // 行列赋值
    column = currentMatrix.column;

    nearArray = new int* [row];                             // 空间申请
    FOR(i, 0, row)
        nearArray[i] = new int[column];


    FOR(i, 0, row)
        FOR(j, 0, column)
        nearArray[i][j] = currentMatrix.nearArray[i][j];// 内部信息复制

    return *this;
}

// 析构函数
Matrix::~Matrix()
{
    // 释放申请的空间，避免发生内存丢失错误
    FOR(i, 0, row)
        delete[] nearArray[i];

    delete[] nearArray;
}

// 设置初始信息
void Matrix::SetMatrix()
{
    cout << endl << "请输入矩阵：" << endl;
    FOR(i, 0, row)
    {
        cout << endl << "请输入矩阵第" << i << "行(以空格分隔)：" << endl;
        FOR(j, 0, column)
        {
            string errorTips = "第";
            errorTips += char(i + '0');
            errorTips += "行";
            errorTips += char(j + '0');
            errorTips += "列输入错误，请从此处开始重新输入本行元素:";
            errorTips += '\n';// 得到当前矩阵元素输入错误对应提示
            FOR(k, 0, j)
            {
                errorTips += char(nearArray[i][k] + '0');
                errorTips += ' ';
            }
            nearArray[i][j] = getint(INT_MIN, INT_MAX, errorTips);        // 关系矩阵中的值为0/1，通过设置getint自定义函数参数控制
        }
    }
    cout << endl << "设置结束，当前矩阵为：" << endl;
    this->PrintMatrix();
}

// 输出矩阵信息
void Matrix::PrintMatrix()
{
    FOR(i, 0, row)
    {
        FOR(j, 0, column)
            cout << setiosflags(ios::left) << setw(2) << nearArray[i][j];
        cout << endl;
    }
}




/* 派生类Relation函数实现 */

// 复制构造函数
RelationMatrix::RelationMatrix(const RelationMatrix& currentMatrix) :Matrix(currentMatrix)
{
    vertexNumber = currentMatrix.vertexNumber;    // 顶点个数复制，其他成员已通过基类复制
}

// 赋值构造函数
RelationMatrix& RelationMatrix::operator=(const RelationMatrix& currentMatrix)
{
    Matrix::operator=(currentMatrix);             // 首先显示调用基类赋值构造函数，复制其他成员

    vertexNumber = currentMatrix.vertexNumber;    // 顶点个数复制，其他成员已通过基类复制

    return *this;
}

// 设置初始信息
void RelationMatrix::SetMatrix()
{
    cout << endl << "请输入关系矩阵：" << endl;
    FOR(i, 0, vertexNumber)
    {
        cout << endl << "请输入矩阵第" << i << "行(以空格分隔)：" << endl;
        FOR(j, 0, vertexNumber)
        {
            string errorTips = "第";
            errorTips += char(i + '0');
            errorTips += "行";
            errorTips += char(j + '0');
            errorTips += "列输入错误，请从此处开始重新输入本行元素:";
            errorTips += '\n';// 得到当前矩阵元素输入错误对应提示
            FOR(k, 0, j)
            {
                errorTips += char(nearArray[i][k] + '0');
                errorTips += ' ';
            }
            nearArray[i][j] = getint(0, 1, errorTips);        // 关系矩阵中的值为0/1，通过设置getint自定义函数参数控制
        }
    }
    cout << endl << "设置结束，当前矩阵为：" << endl;
    this->PrintMatrix();
}
// 求自反闭包
RelationMatrix RelationMatrix::ReflexiveClosure()
{
    RelationMatrix ret = *this;

    FOR(i, 0, vertexNumber)
        ret.nearArray[i][i] = 1;    // 求自反闭包，将关系矩阵对角线置为1

    return ret;
}

// 求对称闭包
RelationMatrix RelationMatrix::SymmetricClosure()
{
    RelationMatrix ret = *this;

    FOR(i, 0, vertexNumber)
        FOR(j, 0, vertexNumber)
        ret.nearArray[i][j] = ret.nearArray[i][j] | ret.nearArray[j][i];// 求对称闭包，将关系矩阵和其转置矩阵做逻辑加运算

    return ret;
}

// 求传递闭包( 朴素算法复杂度O（n^4），后续实现了Warshall算法 O（n^3）求传递闭包 )
RelationMatrix RelationMatrix::TransitiveClosure()
{
    RelationMatrix ret = *this;
    RelationMatrix currentDegree = *this;          // 记录当前关系矩阵R的x次方

    FOR(k, 0, vertexNumber)
    {
        FOR(i, 0, vertexNumber)
            FOR(j, 0, vertexNumber)
            ret.nearArray[i][j] = ret.nearArray[i][j] | currentDegree.nearArray[i][j];// ret = ret + R^k ,其中 + 为逻辑加

        currentDegree = currentDegree * (*this);   // currentDegree =  currentDegree * R ,记录为 R^k ，其中 * 操作为合成操作
    }
    return ret;
}

// 重载*运算符，实现关系矩阵合成运算
RelationMatrix RelationMatrix::operator*(const RelationMatrix& otherMatrix)
{
    RelationMatrix ret(vertexNumber);

    FOR(i, 0, vertexNumber)
        FOR(j, 0, vertexNumber)
        FOR(k, 0, vertexNumber)
        ret.nearArray[i][j] = ret.nearArray[i][j] | nearArray[i][k] & otherMatrix.nearArray[k][j];

    return ret;
}

// Warshall算法O（n^3）求传递闭包
RelationMatrix RelationMatrix::Warshall()
{
    RelationMatrix ret = *this;

    FOR(j, 0, vertexNumber)             // 第j列
        FOR(i, 0, vertexNumber)         // 第i行
        if (ret.nearArray[i][j])    // 若第j列第i行元素为真
        {
            FOR(k, 0, vertexNumber) // 使得任意k在[0,vertexNumber)上，做下面的运算
                ret.nearArray[i][k] = ret.nearArray[i][k] | ret.nearArray[j][k];
        }

    return ret;
}