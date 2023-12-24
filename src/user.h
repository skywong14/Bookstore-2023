//
// Created by skywa on 2023/12/21.
//
#pragma once
#ifndef BOOKSTORE_2023_USER_H
#define BOOKSTORE_2023_USER_H
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include "basic_tool.h"
#include "memoryio.h"
#include "format.h"

using std::string;

//User info
class User_info{
public:
    string30 id, name;
    int permission;
    long long password;

    User_info(){
        id = string30(); name = string30();
        permission = 0; password = 0;
    }
    User_info(const string& _id, const string& _name, const string& _password = "", int _permission = 1){
        id = string30(_id);
        name = string30(_name);
        password = get_Hash(_password);
        permission = _permission;
    }
    bool operator<(const User_info& other) const{
        return id < other.id;
    }
    bool operator>(const User_info& other) const{ return other < (*this); }
    bool operator<=(const User_info& other) const{ return !(other > (*this)); }
    bool operator>=(const User_info& other) const{ return !(other < (*this)); }
    bool operator==(const User_info& other) const{ return (!((*this) < other) && !((*this) > other)); }
    bool operator!=(const User_info& other) const{ return !((*this) == other); }
};

class User_class{
private:
    //User_stack
//    const string file_name = "../database/User_info";
    const string file_name = "_User_info";
    std::queue<std::pair<User_info, string20> > User_stack;
    string30 now_User;

    Memory<User_info> User_file;
    std::map<string30, int> User_online;
public:
    int now_permission;
    string20 now_select;

    User_class();

    void create_root_account();

    void init_User();

    ReturnMode pop_User();
    void push_User(const User_info& _user);

    void register_User(const User_info& _info);

    ReturnMode Su(std::vector<string> tokens);

    ReturnMode Logout();

    ReturnMode Register(std::vector<string> tokens);

    ReturnMode Passwd(std::vector<string> tokens);

    ReturnMode Delete(std::vector<string> tokens);

    ReturnMode Useradd(std::vector<string> tokens);

    void Select(const string& _ISBN);

    void exit_system(); //退出系统时退出User子系统

    ~User_class(); //default
};


#endif //BOOKSTORE_2023_USER_H
