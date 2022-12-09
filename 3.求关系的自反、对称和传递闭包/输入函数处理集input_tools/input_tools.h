#pragma once
// 2053385 高逸轩 //
#ifndef INPUT_TOOLS_H_
#define INPUT_TOOLS_H

#include<iostream>

// 得到一个[ minNum，maxNum ]的数字，进行了输入错误处理，保证健壮性
int getint(const int minNum = INT_MIN, const int maxNum = INT_MAX,const std:: string errorTips = "");

#endif