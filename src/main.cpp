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

using std::cin;
using std::cout;
using std::string;


int main(){
    std::vector<string> tokens;
    User_class user_class;
    Book_class book_class;
    while (1){
        tokens = get_tokens();
        if (tokens.empty()) continue;
        output_tokens(tokens);
        string com = tokens[0];
        tokens.erase(tokens.begin(), tokens.begin() + 1);
        //User
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

        if (com == "show"){
            ReturnMode t=book_class.Show(tokens);
            output_ReturnMode(t);
        }
        if (com == "buy"){
            ReturnMode t=book_class.Buy(tokens);
            output_ReturnMode(t);
        }
        if (com == "select"){
            if (tokens.size() != 1){
                output_ReturnMode(ReturnMode::Invalid_Format);
                continue;
            }
            if (!is_ISBN(tokens[0])){
                output_ReturnMode(ReturnMode::Invalid_Format);
                continue;
            }
            if (user_class.now_permission < 3){
                output_ReturnMode(ReturnMode::Lack_Permission);
                continue;
            }
            book_class.find_or_create(tokens[0]);
            user_class.Select(tokens[0]);
            output_ReturnMode(ReturnMode::Correct);
        }
        if (com == "modify"){
            std::pair<ReturnMode, string> _ret;
            _ret=book_class.Modify(tokens, user_class.now_select.output());
            if (_ret.first == ReturnMode::Correct){
                user_class.now_select = string20(_ret.second);
            }
            output_ReturnMode(_ret.first);
        }
        if (com == "import"){
            ReturnMode t=book_class.Import(tokens, user_class.now_select.output());
            output_ReturnMode(t);
        }

        if (com == "quit" || com == "exit"){

            user_class.exit_system();
            break;
        }

    }
    return 0;
}