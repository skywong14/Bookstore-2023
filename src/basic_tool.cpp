//
// Created by skywa on 2023/12/23.
//
#pragma once
#include "basic_tool.h"


const long long BASE = 197, MOD = 1e9 + 7;
long long get_Hash(const string& str1){
    long long ha = 0;
    for (int i = 0; i < str1.length(); i++)
        ha = (ha * BASE + (long long)(str1[i]) ) % MOD;
    return ha;
}


string20::string20(){ memset(ch, 0, sizeof(ch)); }
string20::string20(const std::string& _str){
    strncpy(ch, _str.c_str(), sizeof(ch) - 1);
    ch[sizeof(ch) - 1] = '\0';
}
string string20::output() const{
    return ch;
}
bool string20::operator<(const string20& other) const{ return std::strcmp(ch, other.ch) < 0; }
bool string20::operator>(const string20& other) const{ return std::strcmp(ch, other.ch) > 0; }
bool string20::operator<=(const string20& other) const{ return std::strcmp(ch, other.ch) <= 0; }
bool string20::operator>=(const string20& other) const{ return std::strcmp(ch, other.ch) >= 0; }
bool string20::operator==(const string20& other) const{ return std::strcmp(ch, other.ch) == 0; }
bool string20::operator!=(const string20& other) const { return std::strcmp(ch, other.ch) != 0; }

string30::string30(){ memset(ch, 0, sizeof(ch)); }
string30::string30(const std::string& _str){
    strncpy(ch, _str.c_str(), sizeof(ch) - 1);
    ch[sizeof(ch) - 1] = '\0';
}
string string30::output() const{
    return ch;
}
bool string30::operator<(const string30& other) const{ return std::strcmp(ch, other.ch) < 0; }
bool string30::operator>(const string30& other) const{ return std::strcmp(ch, other.ch) > 0; }
bool string30::operator<=(const string30& other) const{ return std::strcmp(ch, other.ch) <= 0; }
bool string30::operator>=(const string30& other) const{ return std::strcmp(ch, other.ch) >= 0; }
bool string30::operator==(const string30& other) const{ return std::strcmp(ch, other.ch) == 0; }
bool string30::operator!=(const string30& other) const { return std::strcmp(ch, other.ch) != 0; }

string60::string60(){ memset(ch, 0, sizeof(ch)); }
string60::string60(const std::string& _str){
    strncpy(ch, _str.c_str(), sizeof(ch) - 1);
    ch[sizeof(ch) - 1] = '\0';
}
string string60::output() const{
    return ch;
}
bool string60::operator<(const string60& other) const{ return std::strcmp(ch, other.ch) < 0; }
bool string60::operator>(const string60& other) const{ return std::strcmp(ch, other.ch) > 0; }
bool string60::operator<=(const string60& other) const{ return std::strcmp(ch, other.ch) <= 0; }
bool string60::operator>=(const string60& other) const{ return std::strcmp(ch, other.ch) >= 0; }
bool string60::operator==(const string60& other) const{ return std::strcmp(ch, other.ch) == 0; }
bool string60::operator!=(const string60& other) const { return std::strcmp(ch, other.ch) != 0; }

void output_ReturnMode(ReturnMode ret, int Mode){
//    if (ret == ReturnMode::Correct) std::cout<<"Correct"<<std::endl;
    if (ret != ReturnMode::Correct) std::cout<<"Invalid"<<std::endl;
    if (Mode){
        if (ret == ReturnMode::Invalid_Format) std::cout<<"Invalid_Format"<<std::endl;
        if (ret == ReturnMode::Wrong_Value) std::cout<<"Wrong_Value"<<std::endl;
        if (ret == ReturnMode::Invalid_Operation) std::cout<<"Invalid_Operation"<<std::endl;
        if (ret == ReturnMode::Lack_Permission) std::cout<<"Lack_Permission"<<std::endl;
        if (ret == ReturnMode::Out_Of_Range) std::cout<<"Out_Of_Range"<<std::endl;
        if (ret == ReturnMode::Other_Error) std::cout<<"Other_Error"<<std::endl;
    }
}