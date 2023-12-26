//
// Created by skywa on 2023/12/24.
//

#ifndef BOOKSTORE_2023_LOG_H
#define BOOKSTORE_2023_LOG_H
#include "format.h"
#include "basic_tool.h"
#include "liner_memoryio.h"
#pragma once
#include <cstring>
#include <iostream>
#include <vector>

class Trade_info{
public:
    int mode; //1: +  2: -
    long long value; //double as long long
    Trade_info(){
        mode = 1;
        value = 0;
    }
    Trade_info(long long _val){
        if (_val < 0){
            value = -_val;
            mode = 2;
        }else{
            mode = 1;
            value = _val;
        }
    }
};

class Operation{
    int mode, user_permission;
    string60 user;
    string tt;
};

class Log_class{
    const string file_name = "_log.txt";
    MemoryRiver<Trade_info> log_file;
public:
    void init();
    Log_class();
    ReturnMode Show_Finance(const std::vector<string>& tokens);
    void Report_Finance();
    void Report_Employee();
    void Log();
    void add_Trade(long long _price, int _num);
};



#endif //BOOKSTORE_2023_LOG_H
