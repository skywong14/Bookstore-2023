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
    int line_number = 0;
//    freopen("../test/complex/testcase3/1.in","r",stdin);
//    freopen("out.out","w",stdout);
    std::vector<string> tokens;
    User_class user_class;
    Book_class book_class;
    Log_class log_class;
    while (1){
        line_number++;
//        std::cout<<line_number<<':';
        auto [Now_user, Now_permission] = user_class.get_Now();
        tokens = get_tokens();
        if (tokens.empty()) continue;
        int has_com = 0;
        string com = tokens[0];
        tokens.erase(tokens.begin(), tokens.begin() + 1);
        //User
        if (com == "su"){
            has_com = 1;
            ReturnMode t = user_class.Su(tokens);
            output_ReturnMode(t, "su");
            if (t == ReturnMode::Correct){
                log_class.add_Log(0, Now_user, Now_permission, "su", "user_login:" + tokens[0] );
            }
        }
        if (com == "logout"){
            has_com = 1;
            ReturnMode t = user_class.Logout();
            output_ReturnMode(t, "logout");
            if (t == ReturnMode::Correct){
                log_class.add_Log(0, Now_user, Now_permission, "logout", "user_logout:" + Now_user );
            }
        }
        if (com == "register"){
            has_com = 1;
            ReturnMode t=user_class.Register(tokens);
            output_ReturnMode(t, "register");
            if (t == ReturnMode::Correct){
                log_class.add_Log(0, Now_user, Now_permission, "register", "register_user:" + tokens[0] );
            }
        }
        if (com == "passwd"){
            has_com = 1;
            if (user_class.now_permission < 1){
                output_ReturnMode(ReturnMode::Lack_Permission, "passwd");
                continue;
            }
            ReturnMode t=user_class.Passwd(tokens);
            output_ReturnMode(t);
            if (t == ReturnMode::Correct){
                log_class.add_Log(0, Now_user, Now_permission, "passwd", "modify_user:" + tokens[0] );
            }
        }
        if (com == "useradd"){
            has_com = 1;
            ReturnMode t=user_class.Useradd(tokens);
            output_ReturnMode(t, "useradd");
            if (t == ReturnMode::Correct){
                log_class.add_Log(2, Now_user, Now_permission, "useradd", "add_user:" + tokens[0], "privilege:" + tokens[2]);
            }
        }
        if (com == "delete"){
            has_com = 1;
            ReturnMode t=user_class.Delete(tokens);
            output_ReturnMode(t, "delete");
            if (t == ReturnMode::Correct){
                log_class.add_Log(2, Now_user, Now_permission, "delete", "delete_user:" + tokens[0]);
            }
        }

        if (com == "show"){
            has_com = 1;
            if ((!tokens.empty()) && tokens[0] == "finance"){
                if (user_class.now_permission < 7) {
                    output_ReturnMode(ReturnMode::Lack_Permission, "show finance");
                    continue;
                }
                tokens.erase(tokens.begin(), tokens.begin() + 1);
                ReturnMode t=log_class.Show_Finance(tokens);
                output_ReturnMode(t, "show finance");
                if (t == ReturnMode::Correct){
                    log_class.add_Log(0, Now_user, Now_permission, "show_finance");
                }
            }else{
                if (user_class.now_permission < 1){
                    output_ReturnMode(ReturnMode::Lack_Permission, "show");
                    continue;
                }
                ReturnMode t=book_class.Show(tokens);
                output_ReturnMode(t, "show");
                if (t == ReturnMode::Correct){
                    log_class.add_Log(0, Now_user, Now_permission, "show", "show_some_books");
                }
            }
        }
        if (com == "buy"){
            has_com = 1;
            if (user_class.now_permission < 1){
                output_ReturnMode(ReturnMode::Lack_Permission, "buy."+std::to_string(user_class.now_permission));
                continue;
            }
            std::pair<ReturnMode, std::pair<long long, int> > _ret = book_class.Buy(tokens);
            if (_ret.first == ReturnMode::Correct) log_class.add_Trade(_ret.second.first, _ret.second.second);
            output_ReturnMode(_ret.first, "buy "+std::to_string(user_class.now_permission));
            if (_ret.first == ReturnMode::Correct){
                log_class.add_Log(1, Now_user, Now_permission, "buy", "book_ISBN:" + tokens[0], "trade_num:" + tokens[2]);
            }
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
                output_ReturnMode(ReturnMode::Lack_Permission, "select");
                continue;
            }
            book_class.find_or_create(tokens[0]);
            user_class.Select(tokens[0]);
            output_ReturnMode(ReturnMode::Correct);
            log_class.add_Log(0, Now_user, Now_permission, "select", "book_ISBN:" + tokens[0]);
        }
        if (com == "modify"){
            has_com = 1;
            if (user_class.now_permission < 3){
                output_ReturnMode(ReturnMode::Lack_Permission, "modify."+std::to_string(user_class.now_permission));
                continue;
            }
            std::pair<ReturnMode, string> _ret;
            _ret=book_class.Modify(tokens, user_class.now_select.output());
            if (_ret.first == ReturnMode::Correct){
                user_class.change_select(user_class.now_select, string20(_ret.second));
                user_class.now_select = string20(_ret.second);
            }
            output_ReturnMode(_ret.first, "modify "+std::to_string(user_class.now_permission));
            if (_ret.first == ReturnMode::Correct){
                log_class.add_Log(0, Now_user, Now_permission, "modify", "book_ISBN:" + user_class.now_select.output());
            }
        }
        if (com == "import"){
            has_com = 1;
            std::pair<ReturnMode, long long> _ret;
            _ret=book_class.Import(tokens, user_class.now_select.output(), user_class.now_permission);
            if (_ret.first == ReturnMode::Correct)
                log_class.add_Trade( - _ret.second, 1);
            output_ReturnMode(_ret.first, "import");
            if (_ret.first == ReturnMode::Correct){
                log_class.add_Log(3, Now_user, Now_permission, "import", "Quantity:"+tokens[0], "Cost:"+tokens[1]);
            }
        }
        if (com == "log"){
            has_com = 1;
            if (!tokens.empty() || Now_permission < 7){
                std::cout<<"Invalid"<<std::endl;
                continue;
            }
            log_class.Log();
        }
        if (com == "report"){
            has_com = 1;
            if (tokens.size() == 1 && Now_permission == 7){
                if (tokens[0] == "finance"){
                    log_class.Report_Finance();
                    continue;
                }
                if (tokens[0] == "employee"){
                    log_class.Report_Employee();
                    continue;
                }
            }
            std::cout<<"Invalid"<<std::endl;
            continue;
        }


        if (com == "quit" || com == "exit"){
            user_class.exit_system();
            log_class.add_Log(0, "", 0, "quit_system");
            break;
        }
        if (!has_com) std::cout<<"Invalid"<<std::endl;
    }
    return 0;
}