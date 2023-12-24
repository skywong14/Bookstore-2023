//
// Created by skywa on 2023/12/22.
//

#ifndef BOOKSTORE_2023_FORMAT_H
#define BOOKSTORE_2023_FORMAT_H
#pragma once
#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>

using string_pair = std::pair<std::string, std::string>;

bool is_Modify_format(const std::string& str);

bool noQuotationMarks60(const std::string& str);
bool hasQuotationMarks60(const std::string& str);//有双引号

bool same_KeyWord(const std::string& str);

bool is_alnum30(const std::string& str);
bool is_ISBN(const std::string& str); //ascii20
bool is_ascii30(const std::string& str);

bool is_Int(const std::string& str);
bool is_Double(const std::string& str);
long long double_to_longlong(const std::string &_str);
std::string longlong_to_strdouble(long long _val);



std::vector<std::string> get_tokens();
void output_tokens(const std::vector<std::string>& tokens);

string_pair split_equal(const std::string& token); //按照第一个等号分割
std::vector<std::string> split_pipe(const std::string& _str);//按照“|”分割

#endif //BOOKSTORE_2023_FORMAT_H
