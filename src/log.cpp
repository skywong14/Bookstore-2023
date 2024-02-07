//
// Created by skywa on 2023/12/24.
//
#include "log.h"

void Log_class::init(){
    int new_file = log_file.initialise(file_name);
    logs.initialise(log_file_name);
    if (new_file) log_file.write_info(0, 1);
}

Log_class::Log_class(){
    init();
}

ReturnMode Log_class::Show_Finance(const std::vector<string>& tokens){
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

void Log_class::Log() {
    print_Log(0);
}

void Log_class::Report_Finance() {
    print_Log(1);
}

void Log_class::Report_Employee() {
    print_Log(2);
}

void Log_class::print_Log(int mode) {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    freopen("LOG.txt","a",stdout);
    std::cout << std::endl << "---------------------//Current time: ";
    std::cout << localTime->tm_year + 1900 << "-" << localTime->tm_mon + 1 << "-" << localTime->tm_mday << " ";
    std::cout << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec << "//---------------------" << std::endl;
    if (mode == 0) std::cout<<"System_Log\n";
    else if (mode == 1) std::cout<<"Finance_Report\n";
    else if (mode == 2) std::cout<<"Employee_Report\n";

    int size = logs.get_info(1);
    for (int i = 1; i <= size; i++){
        Operation t = logs.read_T(i);
        if (mode == 0){
            std::cout << t.info1.output() << '\t' << t.user.output() << '\t' << t.info2.output() << '\t'
                      << t.info3.output() <<std::endl;
        }else if (mode == 1){
            if (t.mode==1 || t.mode == 3){
                std::cout << t.info1.output() << '\t' << t.user.output() << '\t' << t.info2.output() << '\t'
                          << t.info3.output() <<std::endl;
            }
        }else if (mode == 2) {
            if (t.mode == 2 || t.mode == 3) {
                std::cout << t.info1.output() << '\t' << t.user.output() << '\t' << t.info2.output() << '\t'
                          << t.info3.output() << std::endl;
            }
        }
    }
    std::cout<<"------------log end.------------------"<<std::endl<<std::endl;
    fclose(stdout);
}

void Log_class::add_Log(int mode, string user, int permission, string info1, string info2, string info3) {
    Operation t;
    t.user_permission = permission;
    t.mode = mode;
    if (permission == 3) user += "*";
    if (permission == 7) user += "**";
    t.user = user;
    t.info1 = info1;
    t.info2 = info2;
    t.info3 = info3;
    int sz = logs.get_info(1) + 1;
    logs.write_info(sz, 1);
    logs.add_T(t, sz);
}

