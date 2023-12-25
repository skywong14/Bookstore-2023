//
// Created by skywa on 2023/12/24.
//
#include "log.h"

void Log_class::init(){
    log_file.initialise(file_name);
    log_file.write_info(0, 1);
}

Log_class::Log_class(){
    init();
}

ReturnMode Log_class::Show_Finance(const std::vector<string>& tokens){
//    std::cout<<"Fi::";
    long long cnt_pos = 0, cnt_neg = 0;
    int num;
    Trade_info info{};
    num = log_file.get_info(1);
    if (tokens.empty()){
        for (int i = 1; i <= num; i++){
            info = log_file.read_T(i);
            if (info.mode == 1) cnt_pos += info.value;
            else cnt_neg += info.value;
        }
        std::cout << "+ " << longlong_to_strdouble(cnt_pos) << " - "
                  << longlong_to_strdouble(cnt_neg) << std::endl;
        return ReturnMode::Correct;
    }
    if (tokens.size() > 1 || !is_Int(tokens[0])) return ReturnMode::Invalid_Format;
    int Count = std::stoi(tokens[0]);
    if (Count < 0 || Count > num) return ReturnMode::Wrong_Value;
    if (Count == 0){
        std::cout<<std::endl;
        return ReturnMode::Correct;
    }

    for (int i = num - Count + 1; i <= num; i++){
        info = log_file.read_T(i);
        if (info.mode == 1) cnt_pos += info.value;
        else cnt_neg += info.value;
    }
    std::cout << "+ " << longlong_to_strdouble(cnt_pos) << " - "
              << longlong_to_strdouble(cnt_neg) << std::endl;
    return ReturnMode::Correct;
}

void Log_class::add_Trade(long long _price, int _num){
    Trade_info info(_price * _num);
    int num = log_file.get_info(1);
    num++;
    log_file.add_T(info, num);
    log_file.write_info(num, 1);
}
