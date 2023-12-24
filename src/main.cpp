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
//    freopen("../test/basic/testcase4.in","r",stdin);
    std::vector<string> tokens;
    User_class user_class;
    Book_class book_class;
    Log_class log_class;
    while (1){
        tokens = get_tokens();
        if (tokens.empty()) continue;
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
            std::pair<ReturnMode, std::pair<long long, int> > _ret = book_class.Buy(tokens);;
            if (_ret.first == ReturnMode::Correct) log_class.add_Trade(_ret.second.first, _ret.second.second);
            output_ReturnMode(_ret.first);
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

    }
    return 0;
}