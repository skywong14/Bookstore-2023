//
// Created by skywa on 2023/12/21.
//
#pragma once
#include "user.h"

using std::string;

User_class::User_class(){
    init_User();
}

void User_class::create_root_account(){
    User_info _admin("root", "root", "sjtu", 7);
    User_file.insert_Atom(_admin.id.output(), _admin);
}

void User_class::init_User(){
    User_stack = {};
    now_User = string30();
    now_permission = 0;
    now_select = string20();
    User_online.clear();
    int flag = User_file.initialise(file_name);
    if (flag) create_root_account();
}


ReturnMode User_class::pop_User(){
    if (User_stack.empty()) return ReturnMode::Invalid_Operation;
    User_online[now_User]--;
    User_stack.pop();
    if (User_stack.empty()){
        now_permission = 0;
        now_User = string30();
        now_select = string20();
        return ReturnMode::Correct;
    }
    now_permission = User_stack.back().first.permission;
    now_User = User_stack.back().first.id;
    now_select = User_stack.back().second;
    return ReturnMode::Correct;
}

void User_class::push_User(const User_info& _user){
    User_stack.push( std::make_pair(_user, string20()) );
    now_permission = _user.permission;
    now_User = _user.id;
    now_select = string20();
    User_online[now_User]++;
}

ReturnMode User_class::Su(std::vector<string> tokens){
    if (tokens.size() > 2 || tokens.empty())
        return ReturnMode::Invalid_Format;
    if (!(is_alnum30(tokens[0]) && is_alnum30(tokens.back())) )
        return ReturnMode::Invalid_Format;
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

void User_class::register_User(const User_info& _info){
    User_file.insert_Atom(_info.id.output(), _info);
}

ReturnMode User_class::Register(std::vector<string> tokens){
    if (tokens.size() != 3) return ReturnMode::Invalid_Format;
    if (!(is_alnum30(tokens[0]) && is_alnum30(tokens[1]) && is_ascii30(tokens[2])))
        return ReturnMode::Invalid_Format;
    if (!User_file.search_Atom(tokens[0]).empty())
        return ReturnMode::Wrong_Value;

    User_info _info(tokens[0], tokens[2], tokens[1], 1);
    register_User(_info);

    return ReturnMode::Correct;
}//token: [UserID] [Password] [Username]


ReturnMode User_class::Passwd(std::vector<string> tokens){
    if (tokens.size() < 2 || tokens.size() > 3)
        return ReturnMode::Invalid_Format;
    if ( !(is_alnum30(tokens[0]) && is_alnum30(tokens[1]) && is_alnum30(tokens.back()) ))
        return ReturnMode::Invalid_Format;
    //校验密码
    std::vector<User_info> _users = User_file.search_Atom(tokens[0]);
    User_info _user = _users[0];
    string _new_psw = tokens.back();
    if (tokens.size() == 2 && now_permission != 7)
        return ReturnMode::Lack_Permission;
    if (tokens.size() == 3 && (_user.password != get_Hash(tokens[1])))
        return ReturnMode::Lack_Permission;
    // 密码/权限正确
    _user.password = get_Hash(tokens.back());
    User_file.delete_Atom(_user.id.output(), _user);
    User_file.insert_Atom(_user.id.output(), _user);

    return ReturnMode::Correct;
}//tokens: [UserID] ([CurrentPassword])? [NewPassword]

ReturnMode User_class::Delete(std::vector<string> tokens){
    if (tokens.size() != 1)
        return ReturnMode::Invalid_Format;
    if (!is_alnum30(tokens[0])) return ReturnMode::Invalid_Format;
    std::vector<User_info> _user =User_file.search_Atom(tokens[0]);
    if (User_online[tokens[0]] > 0 || _user.empty())
        return ReturnMode::Invalid_Operation;
    User_file.delete_Atom(_user[0].id.output(), _user[0]);
    return ReturnMode::Correct;
}//tokens: [UserID]

ReturnMode User_class::Useradd(std::vector<string> tokens){
    if (tokens.size() != 4)
        return ReturnMode::Invalid_Format;
    if (!is_Int(tokens[2])) return ReturnMode::Invalid_Format;
    if (std::stoi(tokens[2]) != 1 && std::stoi(tokens[2]) != 3)
        return ReturnMode::Invalid_Format;
    if ( !(is_ascii30(tokens[3]) && is_alnum30(tokens[0]) && is_alnum30(tokens[1])) )
        return ReturnMode::Invalid_Format;
    if (now_permission < 3 || now_permission <= std::stoi(tokens[2]))
        return ReturnMode::Lack_Permission;
    if (!User_file.search_Atom(tokens[0]).empty())
        return ReturnMode::Wrong_Value;

    User_info _user(tokens[0], tokens[3], tokens[1], std::stoi(tokens[2]));
    User_file.insert_Atom(_user.id.output(), _user);

    return ReturnMode::Correct;
}// [UserID] [Password] [Privilege] [Username]

void User_class::Select(const string& _str){
    User_stack.back().second = _str;
    now_select = _str;
}

void User_class::exit_system(){
    while (!User_stack.empty())
        User_stack.pop();
}

User_class::~User_class() = default;