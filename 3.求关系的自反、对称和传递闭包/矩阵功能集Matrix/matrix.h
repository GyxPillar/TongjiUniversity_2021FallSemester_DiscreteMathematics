#pragma once
// 2053385 高逸轩 //
#ifndef MATRIX_H_
#define MATRIX_H_

#define FOR(i,a,b) for(int i=a;i<b;i++)
#define FOR(j,a,b) for(int j=a;j<b;j++)
#define FOR(k,a,b) for(int k=a;k<b;k++)

// 矩阵 基类
class Matrix
{
public:
    // 默认构造函数
    Matrix(const int x = 0, const int y = 0);

    // 复制构造函数
    Matrix(const Matrix& currentMatrix);

    // 赋值构造函数
    Matrix& operator=(const Matrix& currentMatrix);

    // 析构函数
    ~Matrix();

    // 设置矩阵初始信息
    void SetMatrix();

    // 输出矩阵信息
    void PrintMatrix();
protected:
    // 储存矩阵信息的二维数组指针
    int** nearArray = NULL;
private:
    // 矩阵行
    int row = 0;

    // 矩阵列
    int column = 0;
};

// 关系矩阵 派生类
class RelationMatrix :public Matrix
{
public:
    // 默认构造函数
    RelationMatrix(const int n = 0) :Matrix(n, n), vertexNumber(n) {};

    // 复制构造函数
    RelationMatrix(const RelationMatrix& currentMatrix);

    // 赋值构造函数
    RelationMatrix& operator=(const RelationMatrix& currentMatrix);

    // 析构函数     系统会自动调用基类析构函数释放内存，故不必重写
    ~RelationMatrix() {};

    // 设置矩阵初始信息
    void SetMatrix();

    // 求自反闭包
    RelationMatrix ReflexiveClosure();

    // 求对称闭包
    RelationMatrix SymmetricClosure();

    // 求传递闭包( 朴素复杂度O（n^4），后续实现了Warshall算法 O（n^3）求传递闭包 )
    RelationMatrix TransitiveClosure();

    // *运算符重载，实现合成运算
    RelationMatrix operator*(const RelationMatrix& otherMatrix);

    // Warshall算法求传递闭包
    RelationMatrix Warshall();
private:
    // 顶点数量
    int vertexNumber = 0;
};

#endif