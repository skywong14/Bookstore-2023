//
// Created by skywa on 2023/12/21.
//
//main code for Bookstore_prework
//
// Created by skywa on 2023/12/10.
//
/*
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include "memoryio.h"
#include "basic_tool.h"

int main(){
    Memory<string30> memory;
    memory.initialise("test_for_string");
    int T;
    std::string s1,s2,x;
    std::cin>>T;
    while (T--){
        std::cin>>s1;
        if (s1 == "insert"){
            std::cin>>s2>>x;
            string30 a(x);
            memory.insert_Atom(s2,a);
        }else if (s1 == "delete"){
            std::cin>>s2>>x;
            string30 a(x);
            memory.delete_Atom(s2,a);
        }else if (s1 == "find"){
            std::cin>>s2;
            std::vector<string30> val = memory.search_Atom(s2);
            if (!val.empty()){
                for (auto i:val){
                    std::cout<<i.output()<<' ';
                }
                std::cout<<std::endl;
            }else{
                std::cout<<"null"<<std::endl;
            }
        }
    }
    return 0;
}



class Number{
private:
    int num;
public:
    Number():num(0) {}
    Number(int b):num(b) {}
    bool operator <(const Number &other) const{ return (*this).num<other.num; }
    bool operator >(const Number &other) const{ return (*this).num>other.num; }
    bool operator ==(const Number &other) const{ return (*this).num==other.num; }
    bool operator <=(const Number &other) const{ return (*this).num<=other.num; }
    bool operator >=(const Number &other) const{ return (*this).num>=other.num; }
    bool operator !=(const Number &other) const{ return (*this).num!=other.num; }
};*/

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
void output_tokens(const std::vector<string>& tokens){
    for (auto i:tokens){
        std::cout<<i<<',';
    }
    std::cout<<std::endl;
}

int main(){
    std::vector<string> tokens;
    User_class user_class;
    cout<<"test..."<<std::endl;
    while (1){
        tokens = get_tokens();
        if (tokens.empty()) continue;
        output_tokens(tokens);
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