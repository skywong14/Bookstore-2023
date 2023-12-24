//
// Created by skywa on 2023/12/24.
//
#include "format.h"

bool noQuotationMarks60(const std::string& str){
    if (str.size() > 60) return false;
    for (char c : str)
        if (c == '"' || !std::isprint(c)) //ATTENTON:另一种实现方法...? 或者isprint?
            return false;
    return true;
}

bool hasQuotationMarks60(const std::string& str){
    if (str.size() > 62 || str.empty()) return false;
    if (str.length() > 2 && str.front() == '"' && str.back() == '"') {
        return noQuotationMarks60(str.substr(1, str.length() - 2));
    }
    return false;
}

bool string_size(const std::string& _str, int _size){
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

bool is_alnum30(const std::string& str){
    if (str.size() > 30) return false;
    for (char c : str)
        if (!std::isalnum(c) && c != ' ')
            return false;
    return true;
}

bool is_ISBN(const std::string& str){
    if (str.size() > 20) return false;
    for (char c : str)
        if (c < 32 || c > 126) return false;
    return true;
}

bool is_ascii30(const std::string& str){
    if (str.size() > 30) return false;
    for (char c : str)
        if (c < 32 || c > 126) return false;
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

std::vector<std::string> get_tokens() {
    std::vector<std::string> tokens;
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