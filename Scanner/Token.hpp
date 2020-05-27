//
// Created by qianlu on 2020/5/27.
//

#ifndef SNLCOMPILER_TOKEN_HPP
#define SNLCOMPILER_TOKEN_HPP

#include <string>
#include <vector>
#include "Word.hpp"

//Token结构
class Token{
private:
    Word Type;
    std::string context;
    unsigned short int line;
public:
    Token(Word type, std::string _context, unsigned short int _line);
    ~Token();
};

Token::Token(Word type, std::string _context, unsigned short int _line) {
    this->Type = type;
    this->context = _context;
    this->line = _line;
}

Token::~Token() = default;

//Token序列，保存从文本文档中读取到的Token
class TokenList{
private:
    std::vector<Token> tokenList;
public:
    TokenList();

    const std::vector<Token> &getTokenList() const;

    void setTokenList(const std::vector<Token> &tokenList);

    ~TokenList();
    void AddToken(Token _Token);
};

void TokenList::AddToken(Token _Token) {
    this->tokenList.push_back(_Token);
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
