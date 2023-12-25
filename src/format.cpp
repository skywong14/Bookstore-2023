//
// Created by skywa on 2023/12/24.
//
#include "format.h"

bool noQuotationMarks60(const std::string& str){
    if (str.size() > 60) return false;
    for (char c : str)
        if (c == '"' || !std::isprint(c))
            return false;
    return true;
}

bool hasQuotationMarks60(const std::string& str){
    if (str.size() > 62 || str.empty()) return false;
    if (str.length() > 2 && str.front() == '"' && str.back() == '"') {
        return noQuotationMarks60(str.substr(1, str.length() - 2));
    }
    return false;
} //且key不重复

bool same_KeyWord(const std::string& str){
    std::vector<std::string> keys = split_pipe(str);
    std::sort(keys.begin(), keys.end());
    if (keys[0].empty()) return true;
    for (int i = 1; i < keys.size(); i++)
        if (keys[i] == keys[i-1]) return true;
    return false;
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

bool is_alnum30(const std::string& str){
    if (str.size() > 30 || str.empty()) return false;
    for (char c : str)
        if (!(std::isalnum(c) || c=='_'))
            return false;
    return true;
}

bool is_ISBN(const std::string& str){
    if (str.size() > 20 || str.empty()) return false;
    for (char c : str)
        if (!std::isprint(c)) return false;
    return true;
}

bool is_ascii30(const std::string& str){
    if (str.size() > 30 || str.empty()) return false;
    for (char c : str)
        if (!std::isprint(c)) return false;
    return true;
}

bool is_Double(const std::string& str){
    if (str.size() > 13) return false;
    try{
        std::stod(str);
        return true;
    }catch (const std::invalid_argument&){
        return false;
    }catch (const std::out_of_range&){
        return false;
    }
}

long long double_to_longlong(const std::string &_str){
    double val = std::stod(_str);
    return round(val * 100);
}
std::string longlong_to_strdouble(long long _val){
    std::string str = std::to_string(_val);
    if (str == "0") str = "0.00";
    else {
        if (str.size() == 1) str.insert(0, "0");
        if (str.size() == 2) str.insert(0, "0");
        str.insert(str.length() - 2, ".");
    }
    return str;
}

std::vector<std::string> get_tokens() {
    std::vector<std::string> tokens;
    if (std::cin.eof()) { tokens = {"exit"}; return tokens; }
    std::string str;
    std::getline(std::cin, str);
    std::istringstream iss(str); // 创建字符串流
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return std::move(tokens);
}
void output_tokens(const std::vector<std::string>& tokens){
    for (auto i:tokens){
        std::cout<<i<<',';
    }
    std::cout<<std::endl;
}

string_pair split_equal(const std::string& token){
    size_t delimiterPos = token.find('=');
    std::string key = token, value = "";
    if (delimiterPos != std::string::npos) {
        key = token.substr(0, delimiterPos);
        value = token.substr(delimiterPos + 1);
    }
    return std::make_pair(key,value);
}//按照第一个等号分割

std::vector<std::string> split_pipe(const std::string& _str){
    std::vector<std::string> result;
    std::stringstream ss(_str);
    std::string item;
    while (std::getline(ss, item, '|')){
        result.push_back(item);
    }
    return std::move(result);
}//按照“|”分割