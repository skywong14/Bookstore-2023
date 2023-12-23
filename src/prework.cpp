//main code for Bookstore_prework
//
// Created by skywa on 2023/12/10.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include "memoryio.h"
/*
class Number{
public:
    int num;
    Number():num(0) {}
    Number(int b):num(b) {}
    bool operator <(const Number &other) const{ return (*this).num<other.num; }
    bool operator >(const Number &other) const{ return (*this).num>other.num; }
    bool operator ==(const Number &other) const{ return (*this).num==other.num; }
    bool operator <=(const Number &other) const{ return (*this).num<=other.num; }
    bool operator >=(const Number &other) const{ return (*this).num>=other.num; }
    bool operator !=(const Number &other) const{ return (*this).num!=other.num; }
};
 */
class String{
public:
    char num[60];
    String() {
        num[0] = '\0';
    }
    String(string ss){
        strncpy(num, ss.c_str(), 60-1);
        num[60-1] = '\0';
    }
    bool operator <(const String &other) const{ return (*this).num<other.num; }
    bool operator>(const String& other) const{ return other < (*this); }
    bool operator<=(const String& other) const{ return !(other > (*this)); }
    bool operator>=(const String& other) const{ return !(other < (*this)); }
    bool operator==(const String& other) const{ return (!((*this) < other) && !((*this) > other)); }
    bool operator!=(const String& other) const{ return !((*this) == other); }
};



int main(){
    Memory<String> memory;
    memory.initialise("test",0);
    int T;
    std::string s1,s2,x;
    char ss[60];
    std::cin>>T;
    while (T--){
        std::cin>>s1;
        if (s1 == "insert"){
            std::cin>>s2>>x;
            String a(x);
            memory.insert_Atom(s2,a);
        }else if (s1 == "delete"){
            std::cin>>s2>>x;
            String a(x);
            memory.delete_Atom(s2,a);
        }else if (s1 == "find"){
            std::cin>>s2;
            std::vector<String> val = memory.search_Atom(s2);
            if (!val.empty()){
                for (auto i:val)
                    std::cout<<i.num<<' ';
                std::cout<<std::endl;
            }else{
                std::cout<<"null"<<std::endl;
            }
        }
    }
    return 0;
}
