//
// Created by skywa on 2023/12/22.
//
#include "bookinfo.h"

Book_info::Book_info(){
    ISBN = string20();
    BookName = Author = Keyword = string60(); //其中Keyword保留分隔符
    Quantity = 0;
    Price  = 0;
}
Book_info::Book_info(const string& _strISBN, const string& _strBookName, const string& _strAuthor,
        const string& _strKeyword, int _intPrice){
    ISBN = string20(_strISBN);
    BookName = string60(_strBookName);
    Author = string60(_strAuthor);
    Keyword = string60(_strKeyword); //其中Keyword保留分隔符
    Price = _intPrice;
    Quantity = 0;
}

void Book_class::init_Book(){
    Book_file.initialise(file_name);
    BookName_file.initialise(BookName_file_name);
    KeyWord_file.initialise(KeyWord_file_name);
    Author_file.initialise(Author_file_name);
}

Book_class::Book_class(){
    init_Book();
}

void Book_class::find_or_create(const string& _str){
    if (Book_file.search_Atom(_str).empty()){
        Book_info new_book(_str);
        Book_file.insert_Atom(_str, new_book);
    }
}

ReturnMode Book_class::Show(std::vector<string> tokens){
    std::vector<Book_info> Books = {};
    std::vector<string20> ISBNs;
    int flag = -1;
    if (tokens.empty()){
        Books = Book_file.get_all_values();
        flag = 0;
    }else{
        if (tokens.size() > 1) return ReturnMode::Invalid_Format;
        string_pair splits = split_equal(tokens[0]);
        if (splits.first == "-ISBN"){
            if (!is_ISBN(splits.second)) return ReturnMode::Invalid_Format;
            Books = Book_file.search_Atom(splits.second);
            flag = 0;
        }
        if (splits.first == "-name"){
            if (!hasQuotationMarks60(splits.second)) return ReturnMode::Invalid_Format;
            string BookName = splits.second.substr(1, splits.second.length() - 2);
            ISBNs = BookName_file.search_Atom(BookName);
            flag = 1;
        }
        if (splits.first == "-author"){
            if (!hasQuotationMarks60(splits.second)) return ReturnMode::Invalid_Format;
            string Author = splits.second.substr(1, splits.second.length() - 2);
            ISBNs = Author_file.search_Atom(Author);
            flag = 1;
        }
        if (splits.first == "-keyword"){
            if (!hasQuotationMarks60(splits.second)) return ReturnMode::Invalid_Format;
            string KeyWord = splits.second.substr(1, splits.second.length() - 2);
            std::vector<string> keys = split_pipe(KeyWord);
            if (keys.size() != 1) return ReturnMode::Invalid_Format;
            ISBNs = KeyWord_file.search_Atom(keys[0]);
            flag = 1;
        }
    }
    if (flag == -1) return ReturnMode::Invalid_Format;

    if (flag == 0){
        std::sort(Books.begin(), Books.end());
    }
    if (flag == 1){
        std::vector<Book_info> infos = {};
        for (auto _isbn:ISBNs){
            string _str = _isbn.output();
            infos = Book_file.search_Atom(_str);
            if (!infos.empty()){
                Books.push_back( infos[0] );
                //debug();
            }
        }
        std::sort(Books.begin(), Books.end());
    }
    for (auto info:Books){
        std::cout<< info.ISBN.output() << '\t' << info.BookName.output() <<'\t'
                 <<info.Author.output() << '\t' << info.Price<< '\t' << info.Quantity << std::endl;
        //todo: price format
    }
    //[ISBN]\t[BookName]\t[Author]\t[Keyword]\t[Price]\t[库存数量]\n
    return ReturnMode::Correct;
}
//show (-ISBN=[ISBN] | -name="[BookName]" | -author="[Author]" | -keyword="[Keyword]")?
ReturnMode Book_class::Buy(std::vector<string> tokens){
    if (tokens.size() != 2) return ReturnMode::Invalid_Format;
    if (!is_ISBN(tokens[0]) || !is_Int(tokens[1])) return ReturnMode::Invalid_Format;
    string ISBN = tokens[0];
    int dec_num = std::stoi(tokens[1]);
    std::vector<Book_info> infos = Book_file.search_Atom(ISBN);
    if (infos.empty()) return ReturnMode::Wrong_Value;
    if (dec_num < 1 || dec_num > infos[0].Quantity) return ReturnMode::Wrong_Value;

    Book_file.delete_Atom(ISBN, infos[0]);
    infos[0].Quantity -= dec_num;
    double each_price = infos[0].Price;
    Book_file.insert_Atom(ISBN, infos[0]);
    //todo:fiance num = dec_num
    return ReturnMode::Correct;
}
//buy [ISBN] [Quantity]
std::pair<ReturnMode, string> Book_class::Modify(const std::vector<string>& tokens, const string& now_select){
    if (now_select.empty()) return std::make_pair(ReturnMode::Invalid_Operation, now_select);
    if (tokens.empty()) return std::make_pair(ReturnMode::Invalid_Format, now_select);
    int has_ISBN = 0, has_BookName = 0, has_Author = 0, has_KeyWord = 0, has_Price  = 0;
    string ISBN, BookName, Author, KeyWord;
    double Price;
    string_pair splits;
    for (const auto& _str: tokens){
        splits = split_equal(_str);
        if (splits.first == "-ISBN"){
            if (!is_ISBN(splits.second)) return std::make_pair(ReturnMode::Invalid_Format, now_select);
            ISBN = splits.second;
            if (!has_ISBN) has_ISBN = 1; else return std::make_pair(ReturnMode::Invalid_Format, now_select);
            continue;
        }
        if (splits.first == "-name"){
            if (!hasQuotationMarks60(splits.second)) return std::make_pair(ReturnMode::Invalid_Format, now_select);
            BookName = splits.second.substr(1, splits.second.length() - 2);
            if (!has_BookName) has_BookName = 1; else return std::make_pair(ReturnMode::Invalid_Format, now_select);
            continue;
        }
        if (splits.first == "-author"){
            if (!hasQuotationMarks60(splits.second)) return std::make_pair(ReturnMode::Invalid_Format, now_select);
            Author = splits.second.substr(1, splits.second.length() - 2);
            if (!has_Author) has_Author = 1; else return std::make_pair(ReturnMode::Invalid_Format, now_select);
            continue;
        }
        if (splits.first == "-keyword"){
            if (!hasQuotationMarks60(splits.second)) return std::make_pair(ReturnMode::Invalid_Format, now_select);
            KeyWord = splits.second.substr(1, splits.second.length() - 2);
            if (!has_KeyWord) has_KeyWord = 1; else return std::make_pair(ReturnMode::Invalid_Format, now_select);
            continue;
        }
        if (splits.first == "-price"){
            if (!is_Double(splits.second)) return std::make_pair(ReturnMode::Invalid_Format, now_select);
            Price = std::stod(splits.second);
            if (!has_Price) has_Price = 1; else return std::make_pair(ReturnMode::Invalid_Format, now_select);
            continue;
        }
        return std::make_pair(ReturnMode::Invalid_Format, now_select);
    }

    Book_info new_info = Book_file.search_Atom(now_select)[0];
    Book_file.delete_Atom(new_info.ISBN.output(), new_info);

    if (has_ISBN){
        if (now_select == ISBN) return std::make_pair(ReturnMode::Wrong_Value, now_select);
        new_info.ISBN = string20(ISBN);

        if (!new_info.Author.output().empty()){
            Author_file.delete_Atom(new_info.Author.output(), now_select);
            Author_file.insert_Atom(new_info.Author.output(), ISBN);
        }
        if (!new_info.Keyword.output().empty()){
            KeyWord_file.delete_Atom(new_info.Keyword.output(), now_select);
            KeyWord_file.insert_Atom(new_info.Keyword.output(), ISBN);
        }
        if (!new_info.BookName.output().empty()){
            BookName_file.delete_Atom(new_info.BookName.output(), now_select);
            BookName_file.insert_Atom(new_info.BookName.output(), ISBN);
        }
    }
    if (ISBN.empty()) ISBN = new_info.ISBN.output();

    if (has_Author){
        string pre_Author = new_info.Author.output();
        if (!pre_Author.empty()) Author_file.delete_Atom(Author, now_select);

        new_info.Author = string60(Author);

        Author_file.insert_Atom(Author, ISBN);
    }
    if (has_BookName){
        string pre_Name = new_info.BookName.output();
        if (!pre_Name.empty()) BookName_file.delete_Atom(pre_Name, now_select);

        new_info.BookName = string60(BookName);

        BookName_file.insert_Atom(BookName, ISBN);
    }

    if (has_KeyWord) {
        string pre_keys = new_info.Keyword.output();
        std::vector<string> keys = split_pipe(new_info.Keyword.output());
        for (const auto& key_atom: keys){
            KeyWord_file.delete_Atom(key_atom, now_select);
        }

        new_info.Keyword = string60(KeyWord);
        keys = split_pipe(KeyWord);
        for (const auto& key_atom: keys){
            KeyWord_file.insert_Atom(key_atom, ISBN);
        }
    }
    if (has_Price) {
        new_info.Price = Price;
    }
    Book_file.insert_Atom(ISBN, new_info);
    return std::make_pair(ReturnMode::Correct, ISBN);
}
//modify (-ISBN=[ISBN] | -name="[BookName]" | -author="[Author]" | -keyword="[Keyword]" | -price=[Price])+

ReturnMode Book_class::Import(std::vector<string> tokens, const string& now_select){
    if (tokens.size() != 2 || now_select.empty()) return ReturnMode::Invalid_Format;
    if (!is_Int(tokens[0]) || !is_Double(tokens[1])) return ReturnMode::Invalid_Format;
    int add_num = std::stoi(tokens[0]);
    double add_cost = std::stod(tokens[1]);
    if (add_num < 1 || add_cost < 0) return ReturnMode::Wrong_Value;

    Book_info info = Book_file.search_Atom(now_select)[0];
    Book_file.delete_Atom(now_select, info);
    info.Quantity += add_num;
    Book_file.insert_Atom(now_select, info);

    //todo::doc.h!!!

    return ReturnMode::Correct;
}
//import [Quantity] [TotalCost]