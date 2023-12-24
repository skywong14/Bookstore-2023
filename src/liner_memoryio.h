//
// Created by skywa on 2023/12/24.
//

#ifndef BOOKSTORE_2023_LINER_MEMORYIO_H
#define BOOKSTORE_2023_LINER_MEMORYIO_H

#include <fstream>
#include <ostream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<class T, int info_len = 2>
class MemoryRiver {
private:
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {}

    int get_pos(int pos){
        return sizeof(int) * info_len + (pos - 1) * sizeofT;
    }

    bool check_File_Exists(const std::string& filePath) {
        std::fstream file_tmp(filePath);
        return file_tmp.is_open();
    }

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;

        if (check_File_Exists(file_name)) return; //文件已经存在就无需初始化

        file.open(file_name, std::ios::out);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    int get_info(int n) {
        if (n > info_len) return -1;
        file.open(file_name, std::ios::in | std::ios::binary);
        int tmp;
        file.seekg(sizeof(int) * (n-1), std::ios::beg);
        file.read((char*)&tmp, sizeof(int));
        file.close();
        return tmp;
    }

    void write_info(int tmp, int n) {
        if (n > info_len) return;
        file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
        int det = sizeof(int) * (n-1);
        file.seekp(det, std::ios::beg);
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    void add_T(T t,int pos) {
        file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
        file.seekp(get_pos(pos), std::ios::beg);
        file.write(reinterpret_cast<char *>(&t), sizeofT);
        file.close();
    }

    T read_T(int pos) {
        file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
        file.seekg(get_pos(pos), std::ios::beg);
        T t;
        file.read((char*)&t, sizeofT);
        file.close();
        return t;
    }
};
#endif //BOOKSTORE_2023_LINER_MEMORYIO_H
