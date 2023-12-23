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
bool is_alnum30(const string& str);
bool is_ascii30(const string& str);
bool is_Double(const string& str);

long long get_Hash(const string& str1);

class string30{
private:
    char ch[31]{};
public:
    string30();
    string30(const string& _str);
    string output() const;
    bool operator<(const string30& other) const;
    bool operator>(const string30& other) const;
    bool operator<=(const string30& other) const;
    bool operator>=(const string30& other) const;
    bool operator==(const string30& other) const;
    bool operator!=(const string30& other) const;
};

class string20{
private:
    char ch[21]{};
public:
    string20();
    string20(const std::string& _str);
    string output() const;
    bool operator<(const string20& other) const;
    bool operator>(const string20& other) const;
    bool operator<=(const string20& other) const;
    bool operator>=(const string20& other) const;
    bool operator==(const string20& other) const;
    bool operator!=(const string20& other) const;
};

class string60{
private:
    char ch[61]{};
public:
    string60();
    string60(const std::string& _str);
    string output() const;
    bool operator<(const string60& other) const;
    bool operator>(const string60& other) const;
    bool operator<=(const string60& other) const;
    bool operator>=(const string60& other) const;
    bool operator==(const string60& other) const;
    bool operator!=(const string60& other) const;
};



enum class ReturnMode{
    Correct, Lack_Permission, Invalid_Format, Out_Of_Range, Wrong_Value, Invalid_Operation, Other_Error
};

#endif //BOOKSTORE_2023_BASIC_TOOL_H
