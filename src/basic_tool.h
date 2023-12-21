//
// Created by skywa on 2023/12/21.
//

#ifndef BOOKSTORE_2023_BASIC_TOOL_H
#define BOOKSTORE_2023_BASIC_TOOL_H
#pragma once
#include <iostream>
#include <cstring>

using std::string;


const long long BASE = 197, MOD = 1e9 + 7;
long long get_Hash(const string& str1){
    long long ha = 0;
    for (int i = 0; i < str1.length(); i++)
        ha = (ha * BASE + (long long)(str1[i]) ) % MOD;
    return ha;
}

enum class ReturnMode{
    Correct, Lack_Permission, Invalid_Format, Out_Of_Range, Wrong_Value, Invalid_Operation, Other_Error
};

#endif //BOOKSTORE_2023_BASIC_TOOL_H
