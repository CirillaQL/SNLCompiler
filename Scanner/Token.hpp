//
// Created by qianlu on 2020/5/27.
//

#ifndef SNLCOMPILER_TOKEN_HPP
#define SNLCOMPILER_TOKEN_HPP

#include <string>
#include <utility>
#include "Word.hpp"

class Token{
private:
    Word Type;
    std::string context;
    unsigned short int line;
public:
    Token(Word type, std::string _context, unsigned short int _line);
};

Token::Token(Word type, std::string _context, unsigned short int _line) {
    this->Type = type;
    this->context = _context;
    this->line = _line;
}

#endif //SNLCOMPILER_TOKEN_HPP
