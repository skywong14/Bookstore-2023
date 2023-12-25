//
// Created by skywa on 2023/12/22.
//

#pragma once
#ifndef BOOKSTORE_2023_BOOKINFO_H
#define BOOKSTORE_2023_BOOKINFO_H
#include "memoryio.h"
#include "format.h"
#include "basic_tool.h"
#include "log.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
using std::string;

class Book_info{
public:
    string20 ISBN;
    string60 BookName, Author, Keyword; //其中Keyword保留分隔符
    int Quantity;//库存
    long long Price; //单价
    Book_info();
    Book_info(const string& _strISBN, const string& _strBookName = "", const string& _strAuthor = "",
                         const string& _strKeyword = "", const string& _strPrice = "0");
    bool operator<(const Book_info& other) const{ return ISBN < other.ISBN; }//meaningless just need and operator
    bool operator>(const Book_info& other) const{ return other < (*this); }
    bool operator<=(const Book_info& other) const{ return !(other > (*this)); }
    bool operator>=(const Book_info& other) const{ return !(other < (*this)); }
    bool operator==(const Book_info& other) const{ return (!((*this) < other) && !((*this) > other)); }
    bool operator!=(const Book_info& other) const{ return !((*this) == other); }
};



class Book_class{
private:
    const string file_name = "_Book_info";
    const string BookName_file_name = "_BookName";
    const string Author_file_name = "_Author";
    const string KeyWord_file_name = "_KeyWord";
    Memory<Book_info> Book_file;
    Memory<string20> BookName_file, Author_file, KeyWord_file;
public:
    void init_Book();

    Book_class();

    void find_or_create(const string& _str);

    ReturnMode Show(std::vector<string> tokens);
    //show (-ISBN=[ISBN] | -name="[BookName]" | -author="[Author]" | -keyword="[Keyword]")?

    std::pair<ReturnMode, std::pair<long long, int> > Buy(std::vector<string> tokens);
    //buy [ISBN] [Quantity]

    std::pair<ReturnMode, string> Modify(const std::vector<string>& tokens, const string& now_select);
    //modify (-ISBN=[ISBN] | -name="[BookName]" | -author="[Author]" | -keyword="[Keyword]" | -price=[Price])+

    std::pair<ReturnMode, long long> Import(std::vector<string> tokens, const string& now_select, int now_permission);
    //import [Quantity] [TotalCost]
};

#endif //BOOKSTORE_2023_BOOKINFO_H
