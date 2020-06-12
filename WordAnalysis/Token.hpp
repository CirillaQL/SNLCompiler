//
// Created by qianlu on 2020/5/27.
//

#ifndef SNLCOMPILER_TOKEN_HPP
#define SNLCOMPILER_TOKEN_HPP

#include <string>
#include <vector>
#include <map>
#include "Word.hpp"
#include "FileReader.hpp"

/*
 * 设置SNL语言中的关键字
 */


//判断为保留字
Word WhichID(const std::string& _text){
    if (_text == "if"){
        return IF;
    }else if (_text == "then"){
        return THEN;
    }else if (_text == "fi"){
        return FI;
    }else if (_text == "program"){
        return PROGRAM;
    }else if (_text == "type"){
        return TYPE;
    }else if (_text == "var"){
        return VAR;
    }else if (_text == "procedure"){
        return PROCEDURE;
    }else if (_text == "else"){
        return ELSE;
    }else if (_text == "while"){
        return WHILE;
    }else if (_text == "do"){
        return DO;
    }else if (_text == "endwh"){
        return ENDWH;
    }else if (_text == "begin"){
        return BEGIN;
    }else if (_text == "end"){
        return END;
    }else if (_text == "read"){
        return READ;
    }else if (_text == "write"){
        return WRITE;
    }else if (_text == "of"){
        return OF;
    }else if (_text == "return"){
        return RETURN;
    }else if (_text == "array"){
        return ARRAY;
    }else if (_text == "record"){
        return RECORD;
    }else if (_text == "integer"){
        return INTEGER;
    }else if (_text == "char"){
        return CHAR;
    } else
        return NOTINTHIS;
}

/* **************************
 * **************************
 * **     Token结构         **
 * **************************
 * **************************/
class Token {
private:
    Word Type;
    std::string value;
    unsigned short int line;
public:
    Token();

    Token(Word type, std::string _context, unsigned short int _line);

    ~Token();

    Word getType() const;

    const std::string &getValue() const;

    unsigned short getLine() const;

    bool isGrammer();

    bool isOp();

};

Token::Token(Word type, std::string _context, unsigned short int _line) {
    this->Type = type;
    this->value = _context;
    this->line = _line;
}

//默认构造函数
Token::Token() {
    Type = VOID;
    value = "";
    line = -1;
}

Word Token::getType() const {
    return Type;
}

const std::string &Token::getValue() const {
    return value;
}

unsigned short Token::getLine() const {
    return line;
}

bool Token::isGrammer() {
    if (this->Type == PROGRAM) {
        return true;
    } else if (this->Type == TYPE) {
        return true;
    } else if (this->Type == VAR) {
        return true;
    } else if (this->Type == PROCEDURE) {
        return true;
    } else if (this->Type == BEGIN) {
        return true;
    } else if (this->Type == END) {
        return true;
    } else if (this->Type == ARRAY) {
        return true;
    } else if (this->Type == RECORD) {
        return true;
    } else if (this->Type == IF) {
        return true;
    } else if (this->Type == THEN) {
        return true;
    } else if (this->Type == ELSE) {
        return true;
    } else if (this->Type == FI) {
        return true;
    } else if (this->Type == WHILE) {
        return true;
    } else if (this->Type == DO) {
        return true;
    } else if (this->Type == ENDWH) {
        return true;
    } else if (this->Type == READ) {
        return true;
    } else if (this->Type == WRITE) {
        return true;
    } else if (this->Type == RETURN) {
        return true;
    } else if (this->Type == ASSIGN) {
        return true;
    } else
        return false;
}


bool Token::isOp() {
    if (this->Type == ADD){
        return true;
    }else if (this->Type == SUB){
        return true;
    }else if (this->Type == MUL){
        return true;
    }else if (this->Type == DIV){
        return true;
    }else if (this->Type == LESS){
        return true;
    }else if (this->Type == ID){
        return true;
    }else if (this->Type == INTC){
        return true;
    }else if (this->Type == INTEGER){
        return true;
    }else {
        return false;
    }
}

Token::~Token() = default;


/***********************
 * *********************
 ***** Token序列  ******
 * *********************
 ***********************/
class TokenList {
private:
    std::vector<Token> tokenList;
public:
    TokenList();

    const std::vector<Token> &getTokenList() const;

    void setTokenList(const std::vector<Token> &tokenList);

    ~TokenList();

    //向TokenList中添加Token
    void AddToken(const Token& token);

    int getSize();

    void print();
};


void TokenList::AddToken(const Token &token) {
    this->tokenList.push_back(token);
}

const std::vector<Token> &TokenList::getTokenList() const {
    return tokenList;
}

void TokenList::setTokenList(const std::vector<Token> &tokenList) {
    TokenList::tokenList = tokenList;
}

int TokenList::getSize() {
    return this->tokenList.size();
}

void TokenList::print() {
    for(auto const& item : this->tokenList){
        std::string a1 = transformE2S(item.getType());
        std::string a2 = item.getValue();
        a1.resize(20,' ');
        a2.resize(20,' ');
        std::cout << a1 << a2 << item.getLine() << std::endl;
    }
}


TokenList::~TokenList() = default;

TokenList::TokenList() = default;


#endif //SNLCOMPILER_TOKEN_HPP
