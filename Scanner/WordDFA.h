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
    }else if (_text == "integer"){
        return INTEGER;
    }else if (_text == "char"){
        return CHAR;
    } else
        return NOTINTHIS;
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
                    list.AddToken(token);
                    word="";
                } else if (ch == '-') {
                    Token token = Token(SUB,"-",line);
                    list.AddToken(token);
                    word="";
                } else if (ch == '*') {
                    Token token = Token(MUL,"*",line);
                    list.AddToken(token);
                    word="";
                    //return token;   word= "";
                } else if (ch == '/') {
                    Token token = Token(DIV,"/",line);
                    list.AddToken(token);
                    word="";
                } else if (ch == '(') {
                    Token token = Token(LEFT_BRACKET,"(",line);
                    list.AddToken(token);
                    word="";
                } else if (ch == ')') {
                    Token token = Token(RIGHT_BRACKET,")",line);
                    list.AddToken(token);
                    word="";
                } else if (ch == ',') {
                    Token token = Token(COMMA,",",line);
                    list.AddToken(token);
                    word="";
                } else if (ch == ';') {
                    Token token = Token(SEMICOLON,";",line);
                    list.AddToken(token);
                    word="";
                } else if (ch == '[') {
                    Token token = Token(LEFT_BRACES,"[",line);
                    list.AddToken(token);
                    word="";
                } else if (ch == ']') {
                    Token token = Token(RIGHT_BRACES,"[",line);
                    list.AddToken(token);
                    word="";
                } else if (ch == '=') {
                    Token token = Token(EQUAL,"=",line);
                    list.AddToken(token);
                    word="";
                } else if (ch == '<') {
                    Token token = Token(LESS,"<",line);
                    list.AddToken(token);
                    word="";
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
            /*
             * INID状态，判断是否为关键字
             */
            case INID:
                if (isAlpha(ch) || isDigit(ch)) {
                    stateEnum = INID;
                } else {
                    word.erase(word.end()-1);
                    Word flag = WhichID(word);
                    if (flag == NOTINTHIS){
                        Token token = Token(ID,word,line);
                        list.AddToken(token);
                    } else{
                        Token token = Token(WhichID(word),word,line);
                        list.AddToken(token);
                    }
                    //添加Token完毕
                    word = "";
                    stateEnum = NORMAL;
                }
                break;
            case INNUM:
                //如果是数字，会自动保持数字状态，不是数字的话就完成;
                if (!isDigit(ch)) {
                    word.erase(word.end()-1); // ch
                    Token token = Token(INTC,word,line);
                    list.AddToken(token);
                    word = "";
                    stateEnum = NORMAL;
                }
                break;
            case INASSIGN:
                //赋值语句
                if (ch == '=') {
                    Token token = Token(ASSIGN,":=",line);
                    list.AddToken(token);
                    word="";
                    stateEnum = NORMAL;
                } else {
                    //‘：’之后如果不是‘=’,那么一定是错的
                    word = "";
                    stateEnum = ERROR;
                }
                break;
            case INDOT:
                /*
                 * 句号，有两种情况，一个是数组声明的时候用两个.来声明，一个是程序结束
                 */
                if (isAlpha(ch)) {          // record域中的点运算符
                    word.erase(word.end()-1);
                    Token token = Token(RECORD,word,line);
                    list.AddToken(token);
                    word = "";
                    stateEnum = NORMAL;
                } else if (ch == '.') {     // 数组的下标运算符
                    stateEnum = INRANGE;
                    word = "";
                    break;
                }else if (ch == ' ' || ch == '\n'){
                    //Token token = Token(EoF,".",line);
                    //list.AddToken(token);
                    //word = "";
                    stateEnum = NORMAL;
                }
                break;
            case INRANGE:
                if (isDigit(ch)) {
                    // 回溯
                    word.erase(word.begin());
                    word.erase(word.begin());
                    Token token = Token(UNDERRANGE,"..",line);
                    list.AddToken(token);
                    stateEnum = NORMAL;
                } else{
                    // 如果后面不是数字，那么error
                    stateEnum = ERROR;
                }
                break;
            case INCHAR:
                if (isDigit(ch) || isAlpha(ch)) {
                    stateEnum = INCHAR;
                }else if (ch == '\''){
                    word.erase(word.end()-1);
                    Token token = Token(CHAR,word,line);
                    list.AddToken(token);
                    word = "";
                    stateEnum = NORMAL;
                } else{
                    word = "";
                    stateEnum = ERROR;
                }
                break;
            case ERROR:
                break;
        }
    }
    //Token a = Token(EoF,".",5);
    //return a;
}

#endif //SNLCOMPILER_WORDDFA_H
