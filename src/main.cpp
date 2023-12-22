//
// Created by skywa on 2023/12/21.
//
#pragma once
#include "user.h"
#include "bookinfo.h"
#include "format.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <sstream>

using std::cin;
using std::cout;
using std::string;


//test user.h
std::vector<string> get_tokens() {
    cout<<"test..."<<std::endl;
    std::vector<string> tokens;
    string str;
    std::getline(std::cin, str);
    std::istringstream iss(str); // 创建字符串流
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return std::move(tokens);
}
void output_ReturnMode(ReturnMode ret){
    if (ret == ReturnMode::Correct) cout<<"Correct"<<std::endl;
    else cout<<"Invalid!"<<std::endl;
}

class Number{
public:
    char num;
    char c[60];
    Number():num(),c() {}
    Number(char ss):num(ss),c() {}
    bool operator <(const Number &other) const{ return (*this).num<other.num; }
    bool operator >(const Number &other) const{ return (*this).num>other.num; }
    bool operator ==(const Number &other) const{ return (*this).num==other.num; }
    bool operator <=(const Number &other) const{ return (*this).num<=other.num; }
    bool operator >=(const Number &other) const{ return (*this).num>=other.num; }
    bool operator !=(const Number &other) const{ return (*this).num!=other.num; }
};


int main(){
    std::vector<string> tokens;
    User_class user_class;

    const string file_names = "../database/User_info";
    Memory<Number> memory;
    memory.initialise(file_names);
    return 0;


    cout<<"test..."<<std::endl;
    while (1){
        tokens = get_tokens();
        if (tokens.empty()) continue;
        string com = tokens[0];
        cout<<"test..."<<com<<std::endl;
        tokens.erase(tokens.begin(), tokens.begin() + 1);
        if (com == "su"){
            ReturnMode t=user_class.Su(tokens);
            output_ReturnMode(t);
        }
        if (com == "logout"){
            ReturnMode t=user_class.Logout();
            output_ReturnMode(t);
        }
        if (com == "register"){
            ReturnMode t=user_class.Register(tokens);
            output_ReturnMode(t);
        }
        if (com == "passwd"){
            ReturnMode t=user_class.Passwd(tokens);
            output_ReturnMode(t);
        }
        if (com == "useradd"){
            ReturnMode t=user_class.Useradd(tokens);
            output_ReturnMode(t);
        }
        if (com == "delete"){
            ReturnMode t=user_class.Delete(tokens);
            output_ReturnMode(t);
        }
        if (com == "quit"){
            user_class.exit_system();
            break;
        }
    }
    return 0;
}