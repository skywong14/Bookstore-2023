//
// Created by skywa on 2023/12/21.
//

#pragma once
#ifndef BOOKSTORE_2023_BASIC_TOOL_H
#define BOOKSTORE_2023_BASIC_TOOL_H
#include <iostream>
#include <cstring>

using std::string;

bool string_size(const string& _str, int _size);

bool is_Int(const std::string& str);
bool is_char30(const string& str);
bool is_ascii30(const string& str);
bool is_Double(const string& str);

long long get_Hash(const string& str1);

enum class ReturnMode{
    Correct, Lack_Permission, Invalid_Format, Out_Of_Range, Wrong_Value, Invalid_Operation, Other_Error
};

#endif //BOOKSTORE_2023_BASIC_TOOL_H
