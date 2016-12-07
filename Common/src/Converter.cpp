//
// Created by rezaul on 11/29/16.
//

#include "Converter.h"

namespace Common {

int32_t Converter::ToInt32(std::string &&num)
{
    int32_t n = INT32_MIN;
    sscanf(num.c_str(), "%d", &n);
    return n;
}

std::string Converter::ToStr(int32_t n)
{
    char str[50];
    sprintf(str, "%d", n);
    return str;
}

}