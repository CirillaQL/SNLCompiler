//
// Created by qianlu on 2020/5/29.
//

#ifndef SNLCOMPILER_WORDDFA_H
#define SNLCOMPILER_WORDDFA_H

#include <string>
#include "Token.hpp"
#include "Word.hpp"

enum StateEnum{
    NORMAL,             //初始状态
    INID,               //标识符状态
    INNUM,              //数字状态
    INASSIGN,           //赋值状态
    INDOT,              //点状态
    INRANGE,            //数组下标界限状态
    INCHAR,             //字符标志状态
    ERROR               //出错
};

//判断为字母
bool isAlpha(const char& ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

//判断为数字
bool isDigit(const char& ch){
    return (ch >= '0' && ch <= '9');
}

//判断为空格
bool isBlank(const char& ch){
    return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
}

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
    }else if (_text == "Integer"){
        return INTEGER;
    }else if (_text == "char"){
        return CHAR;
    } else
        return EoF;
}

void getToken(TokenList& list, const std::string& input, const unsigned short& line){
    StateEnum stateEnum = NORMAL;
    std::string word;

    for(char ch : input){
        word += ch;
        switch (stateEnum) {
            case NORMAL:
                if (isAlpha(ch)){
                    stateEnum = INID;
                } else if (isDigit(ch)){
                    stateEnum = INNUM;
                }else if (isBlank(ch)){
                    word.erase(word.end()-1);
                    stateEnum = NORMAL;
                }else if (ch == '+') {
                    Token token = Token(ADD,"+",line);
                    //return token;   word= "";
                } else if (ch == '-') {
                    Token token = Token(SUB,"-",line);
                    //return token;   word= "";
                } else if (ch == '*') {
                    Token token = Token(MUL,"*",line);
                    list.AddToken(token);
                    word="";
                    //return token;   word= "";
                } else if (ch == '/') {
                    Token token = Token(DIV,"/",line);
                    //return token;   word= "";
                } else if (ch == '(') {
                    Token token = Token(LEFT_BRACKET,"(",line);
                    //return token;   word= "";
                } else if (ch == ')') {
                    Token token = Token(RIGHT_BRACKET,")",line);
                    //return token;   word= "";
                } else if (ch == ',') {
                    Token token = Token(COMMA,",",line);
                    //return token;   word= "";
                } else if (ch == ';') {
                    Token token = Token(SEMICOLON,";",line);
                    //return token;   word= "";
                } else if (ch == '[') {
                    Token token = Token(LEFT_BRACES,"[",line);
                    //return token;   word= "";
                } else if (ch == ']') {
                    Token token = Token(RIGHT_BRACES,"[",line);
                    //return token;   word= "";
                } else if (ch == '=') {
                    Token token = Token(EQUAL,"=",line);
                    //return token;   word= "";
                } else if (ch == '<') {
                    Token token = Token(LESS,"<",line);
                    //return token;   word= "";
                }else if (ch == ':') {
                    stateEnum = INASSIGN;
                }else if (ch == '.') {
                    stateEnum = INDOT;            // 域的点运算符
                } else if (ch == '\'') {
                    word.erase(word.end()-1);
                    stateEnum = INCHAR;
                } else {
                    stateEnum = ERROR;
                }
                break;
            case INID:
                if (isAlpha(ch) || isDigit(ch)) {
                    stateEnum = INID;
                    std::cout << "进入INID" << std::endl;
                } else {
                    // 当前字符已经不是标识符范围的了，标识符已经结束了
                    // 回溯一个字符
                    word.erase(word.end()-1);
                    Token token = Token(WhichID(word),word,line);
                    std::cout << "完成" << std::endl;
                    list.AddToken(token);
                    word = "";
                    stateEnum = NORMAL;
                    ////return token;   word= "";
                }
                break;
            case INNUM:
                if (!isDigit(ch)) {
                    word.erase(word.end()-1); // ch
                    //token = new Token(line, column, TokenType.INTC, sb.substring(0, sb.length() - 1));
                    //LOG.debug("已识别Token：" + token);
                    ////return token;   word= "";
                }
                break;
            case INASSIGN:
                break;
            case INDOT:
                break;
            case INRANGE:
                break;
            case INCHAR:
                break;
            case ERROR:
                break;
        }
    }
    //Token a = Token(EoF,".",5);
    //return a;
}

#endif //SNLCOMPILER_WORDDFA_H
