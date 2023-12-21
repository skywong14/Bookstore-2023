//
// Created by skywa on 2023/12/21.
//
#ifndef BOOKSTORE_2023_USER_H
#define BOOKSTORE_2023_USER_H
#pragma once
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include "basic_tool.h"
#include "memoryio.h"

using std::string;

//User info
class User_info{
public:
    string id, name;
    int permission;
    long long password;

    User_info() = default;
    User_info(const string& _id, const string& _name, string _password = "", int _permission = 1){
        id = _id;
        name = _name;
        password = get_Hash(_password);
        permission = _permission;
    }
};

class User_class{
private:
    //User_stack
    const string file_name = "../database/User_info";
    std::queue<std::pair<User_info, string> > User_stack;
    string now_User;
    int now_permission;
    string now_select;

    Memory<User_info> User_file;

public:

    User_class();

    void create_root_account();

    void init_User();

    ReturnMode pop_User();
    void push_User(const User_info& _user);

    ReturnMode Su(std::vector<string> tokens);

    ReturnMode Logout();

    ReturnMode Register(std::vector<string> tokens);

};


#endif //BOOKSTORE_2023_USER_H
