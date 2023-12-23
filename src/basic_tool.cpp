//
// Created by skywa on 2023/12/23.
//
#pragma once
#include "basic_tool.h"

bool string_size(const string& _str, int _size){
    if (_str.size() > _size) return false;
    return true;
}

bool is_Int(const std::string& str){
    try{
        std::stoi(str);
        return true;
    }catch (const std::invalid_argument&){
        return false;
    }catch (const std::out_of_range&){
        return false;
    }
}

bool is_alnum30(const string& str){
    if (str.size() > 30)
        return false;
    for (char c : str)
        if (!std::isalnum(c) && c != ' ')
            return false;
    return true;
}
bool is_ascii30(const string& str){
    if (str.size() > 30)
        return false;
    for (char c : str)
        if (c < 32 || c > 126) return false;
    return true;
}

bool is_Double(const string& str){
    try{
        std::stod(str);
        return true;
    }catch (const std::invalid_argument&){
        return false;
    }catch (const std::out_of_range&){
        return false;
    }
}

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