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

using std::cin;
using std::cout;
using std::string;

int main(){
//   freopen("../test/complex/testcase1/3.in","r",stdin);
//    freopen("out.out","w",stdout);
    std::vector<string> tokens;
    User_class user_class;
    Book_class book_class;
    Log_class log_class;
    while (1){
        tokens = get_tokens();
        if (tokens.empty()) continue;
        int has_com = 0;
        string com = tokens[0];
        tokens.erase(tokens.begin(), tokens.begin() + 1);
        //User
        if (com == "su"){
            has_com = 1;
            ReturnMode t=user_class.Su(tokens);
            output_ReturnMode(t);
        }
        if (com == "logout"){
            has_com = 1;
            ReturnMode t=user_class.Logout();
            output_ReturnMode(t);
        }
        if (com == "register"){
            has_com = 1;
            ReturnMode t=user_class.Register(tokens);
            output_ReturnMode(t);
        }
        if (com == "passwd"){
            has_com = 1;
            ReturnMode t=user_class.Passwd(tokens);
            output_ReturnMode(t);
        }
        if (com == "useradd"){
            has_com = 1;
            ReturnMode t=user_class.Useradd(tokens);
            output_ReturnMode(t);
        }
        if (com == "delete"){
            has_com = 1;
            ReturnMode t=user_class.Delete(tokens);
            output_ReturnMode(t);
        }

        if (com == "show"){
            has_com = 1;
            if (user_class.now_permission < 1) {
                std::cout<<"Invalid"<<std::endl;
                continue;
            }
            if ((!tokens.empty()) && tokens[0] == "finance"){
                tokens.erase(tokens.begin(), tokens.begin() + 1);
                ReturnMode t=log_class.Show_Finance(tokens);
                output_ReturnMode(t);
            }else{
                ReturnMode t=book_class.Show(tokens);
                output_ReturnMode(t);
            }
        }
        if (com == "buy"){
            has_com = 1;
            std::pair<ReturnMode, std::pair<long long, int> > _ret = book_class.Buy(tokens);;
            if (_ret.first == ReturnMode::Correct) log_class.add_Trade(_ret.second.first, _ret.second.second);
            output_ReturnMode(_ret.first);
        }
        if (com == "select"){
            has_com = 1;
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
            has_com = 1;
            std::pair<ReturnMode, string> _ret;
            _ret=book_class.Modify(tokens, user_class.now_select.output());
            if (_ret.first == ReturnMode::Correct){
                user_class.change_select(user_class.now_select, string20(_ret.second));
                user_class.now_select = string20(_ret.second);
            }
            output_ReturnMode(_ret.first);
        }
        if (com == "import"){
            has_com = 1;
            std::pair<ReturnMode, long long> _ret;
            _ret=book_class.Import(tokens, user_class.now_select.output(), user_class.now_permission);
            if (_ret.first == ReturnMode::Correct)
                log_class.add_Trade( - _ret.second, 1);
            output_ReturnMode(_ret.first);
        }

        if (com == "quit" || com == "exit"){
            user_class.exit_system();
            break;
        }
        if (!has_com) std::cout<<"Invalid"<<std::endl;
    }
    return 0;
}