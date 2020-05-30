//
// Created by qianlu on 2020/5/27.
//

#ifndef SNLCOMPILER_WORD_HPP
#define SNLCOMPILER_WORD_HPP

#include <string>

enum Word {
    PROGRAM, TYPE, VAR, PROCEDURE, BEGIN, END, ARRAY, OF, RECORD, IF, THEN,
    ELSE, FI, WHILE, DO, ENDWH, READ, WRITE, RETURN, INTEGER, CHAR,INTC,UNDERRANGE,NOTINTHIS,
    UNSIGNEDNUMBER,
    ADD, SUB, MUL, DIV, LESS, EQUAL, LEFT_PARENT, RIGHT_PARENT,
    LEFT_BRACKET, RIGHT_BRACKET, DOT, SEMICOLON, EoF, SPACE,
    COLON_EQUAL, LEFT_BRACES, RIGHT_BRACES, APOSTROPHE, TWO_DOT,
    COMMA,ASSIGN,
    ID, VOID
};

std::string transformE2S(Word type){
    if (type == PROGRAM)
        return "PROGRAM";
    else if (type == TYPE)
        return "TYPE";
    else if (type == VAR)
        return "VAR";
    else if (type == PROCEDURE)
        return "PROCEDURE";
    else if (type == BEGIN)
        return "BEGIN";
    else if (type == END)
        return "END";
    else if (type == ARRAY)
        return "ARRAY";
    else if (type == OF)
        return "OF";
    else if (type == RECORD)
        return "RECORD";
    else if (type == IF)
        return "IF";
    else if (type == THEN)
        return "THEN";
    else if (type == ELSE)
        return "ELSE";
    else if (type == FI)
        return "FI";
    else if (type == WHILE)
        return "WHILE";
    else if (type == DO)
        return "DO";
    else if (type == ENDWH)
        return "ENDWH";
    else if (type == READ)
        return "READ";
    else if (type == WRITE)
        return "WRITE";
    else if (type == RETURN)
        return "RETURN";
    else if (type == INTEGER)
        return "INTEGER";
    else if (type == CHAR)
        return "CHAR";
    else if (type == INTC)
        return "INTC";
    else if (type == UNDERRANGE)
        return "UNDERRANGE";
    else if (type == ADD)
        return "ADD";
    else if (type == SUB)
        return "SUB";
    else if (type == MUL)
        return "MUL";
    else if (type == DIV)
        return "DIV";
    else if (type == LESS)
        return "LESS";
    else if (type == EQUAL)
        return "EQUAL";
    else if (type == LEFT_BRACES)
        return "LEFT_BRACES";
    else if (type == RIGHT_BRACES)
        return "RIGHT_BRACES";
    else if (type == SEMICOLON)
        return "SEMICOLON";
    else if (type == LEFT_BRACKET)
        return "LEFT_BRACKET";
    else if (type == RIGHT_BRACKET)
        return "RIGHT_BRACKET";
    else if (type == COMMA)
        return "COMMA";
    else if (type == ASSIGN)
        return "ASSIGN";
    else if (type == ID)
        return "ID";
    else
        return "NO";
}

#endif //SNLCOMPILER_WORD_HPP
