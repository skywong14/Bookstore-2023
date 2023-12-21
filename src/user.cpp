//
// Created by skywa on 2023/12/21.
//



#pragma once
#include "user.h"
#include "memoryio.h"
#include "basic_tool.h"
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using std::string;



User_class::User_class(){
    init_User();
}

void User_class::create_root_account(){

}

void User_class::init_User(){
    User_stack = {};
    now_User = "";
    now_permission = 0;
    now_select = "";
    User_file.initialise(file_name);
}


ReturnMode User_class::pop_User(){
    if (User_stack.empty()) return ReturnMode::Invalid_Operation;
    User_stack.pop();
    if (User_stack.empty()){
        now_permission = 0;
        now_User = "";
        now_select = "";
        return ReturnMode::Correct;
    }
    now_permission = User_stack.back().first.permission;
    now_User = User_stack.back().first.id;
    now_select = User_stack.back().second;
    return ReturnMode::Correct;
}

void User_class::push_User(const User_info& _user){
    User_stack.push( std::make_pair(_user, "") );
    now_permission = _user.permission;
    now_User = _user.id;
    now_select = "";
}

ReturnMode User_class::Su(std::vector<string> tokens){
    if (tokens.size() > 2 || tokens.empty()){
        return ReturnMode::Invalid_Format;
    }
    string _id = tokens[0];
    std::vector<User_info> _user = User_file.search_Atom(_id);
    if (_user.empty()){
        return ReturnMode::Out_Of_Range;
    }
    if (tokens.size() == 1){
        if (now_permission > _user[0].permission){
            push_User(_user[0]);
        }else
            return ReturnMode::Lack_Permission;
    }else{
        if (_user[0].password == get_Hash(tokens[1])){
            push_User(_user[0]);
        }else
            return ReturnMode::Wrong_Value;
    }
    return ReturnMode::Correct;
} //token: [UserID] ([Password])?

ReturnMode User_class::Logout(){
    return pop_User();
}

ReturnMode User_class::Register(std::vector<string> tokens){
    if (tokens.size() != 3)
        return ReturnMode::Invalid_Format;
    string _userid = tokens[0], _psw = tokens[1], userName = tokens[2];

    //TODO

    return ReturnMode::Correct;
}//token: [UserID] [Password] [Username]