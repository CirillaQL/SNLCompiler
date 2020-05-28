//
// Created by qianlu on 2020/5/27.
//

#ifndef SNLCOMPILER_TOKEN_HPP
#define SNLCOMPILER_TOKEN_HPP

#include <string>
#include <vector>
#include "Word.hpp"

static std::string reservedWords[] = {"program", "type", "var", "procedure", "begin", "end", "array", "of", "record",
                                      "if", "then",
                                      "else", "fi", "while", "do", "endwh", "read", "write", "return", "integer", "char"
};

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
    void AddToken(const Token &token);

    //从FileReader中获取
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

TokenList::~TokenList() = default;

TokenList::TokenList() = default;


#endif //SNLCOMPILER_TOKEN_HPP
