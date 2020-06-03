//
// Created by QianLu on 2020/6/3.
//

#ifndef SNLCOMPILER_DFA_HPP
#define SNLCOMPILER_DFA_HPP

#include "Token.hpp"

using namespace std;

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

//词法分析程序，DFA自动机
class DFA{
private:
    enum StateEnum{
        NORMAL,             //初始状态
        INID,               //标识符状态
        INNUM,              //数字状态
        INASSIGN,           //赋值状态(:
        INCOMMIT,           //注释状态
        INDOT,              //点状态
        INRANGE,            //数组下标界限状态
        INCHAR,             //字符标志状态
        ERROR               //出错
    };
public:
    DFA();
    TokenList getTokenlist(const string& filename);
};

TokenList DFA::getTokenlist(const string &filename) {
    FileReader fileReader = FileReader();
    fileReader.ReadFile(filename);
    //完成读取源文件
    vector<string> srcLine = fileReader.getSrcLine();
    //读取到源文件序列中
    //初始化TokenList
    TokenList list = TokenList();
    //每行的读取与处理
    int lineNumber = 1;
    for(const auto& line : srcLine){
        //每行的具体操作
        int length = line.size();
        string word;
        StateEnum stateEnum = NORMAL;
        for (int i = 0; i <= length; i++) {
            word += line[i];
            switch (stateEnum) {
                case NORMAL:
                    //一开始进入，初始化
                    //如果S为字母，转INID
                    if (isAlpha(line[i])){
                        stateEnum = INID;
                    }
                    //如果S为数字，转INNUM;
                    else if(isDigit(line[i])){
                        stateEnum = INNUM;
                    }
                    //为空格
                    else if (isBlank(line[i])){
                        word.erase(word.end()-1);
                        stateEnum = NORMAL;
                    }
                    //如果S为‘：’，转赋值
                    else if (line[i] == ':'){
                        stateEnum = INASSIGN;
                    }
                    //如果S为'{'进入
                    else if (line[i] == '{'){
                        stateEnum = INCOMMIT;
                    }
                    //如果S为.判断是数组还是结束
                    else if(line[i] == '.'){
                        if (line[i+1] == '.'){
                            stateEnum = INRANGE;
                        } else {
                            stateEnum = INDOT;
                        }
                    }
                    //如果S为',则进入字符
                    else if (line[i] == '\''){
                        stateEnum = INCHAR;
                    }
                    //余下的则为判断特殊字符
                    else if (line[i] == '+') {
                        Token token = Token(ADD,"+",lineNumber);
                        list.AddToken(token);
                        word="";
                    } else if (line[i] == '-') {
                        Token token = Token(SUB,"-",lineNumber);
                        list.AddToken(token);
                        word="";
                    } else if (line[i] == '*') {
                        Token token = Token(MUL,"*",lineNumber);
                        list.AddToken(token);
                        word="";
                        //return token;   word= "";
                    } else if (line[i] == '/') {
                        Token token = Token(DIV,"/",lineNumber);
                        list.AddToken(token);
                        word="";
                    } else if (line[i] == '(') {
                        Token token = Token(LEFT_BRACKET,"(",lineNumber);
                        list.AddToken(token);
                        word="";
                    } else if (line[i] == ')') {
                        Token token = Token(RIGHT_BRACKET,")",lineNumber);
                        list.AddToken(token);
                        word="";
                    } else if (line[i] == ',') {
                        Token token = Token(COMMA,",",lineNumber);
                        list.AddToken(token);
                        word="";
                    } else if (line[i] == ';') {
                        Token token = Token(SEMICOLON,";",lineNumber);
                        list.AddToken(token);
                        word="";
                    } else if (line[i] == '[') {
                        Token token = Token(LEFT_BRACES,"[",lineNumber);
                        list.AddToken(token);
                        word="";
                    } else if (line[i] == ']') {
                        Token token = Token(RIGHT_BRACES,"]",lineNumber);
                        list.AddToken(token);
                        word="";
                    } else if (line[i] == '=') {
                        Token token = Token(EQUAL,"=",lineNumber);
                        list.AddToken(token);
                        word="";
                    } else if (line[i] == '<') {
                        Token token = Token(LESS, "<", lineNumber);
                        list.AddToken(token);
                        word = "";
                    }
                    break;
                //标识符处理
                case INID:
                    if (isAlpha(line[i]) || isDigit(line[i])) {
                        //没完事，继续
                        stateEnum = INID;
                    } else {
                        word.erase(word.end()-1);
                        Word flag = WhichID(word);
                        if (flag == NOTINTHIS){
                            Token token = Token(ID,word,lineNumber);
                            list.AddToken(token);
                        } else{
                            Token token = Token(WhichID(word),word,lineNumber);
                            list.AddToken(token);
                        }
                        //添加Token完毕
                        if (line[i] == ' '){
                            i++;
                            word = "";
                        }
                        i--;
                        stateEnum = NORMAL;
                    }
                    break;
                //数字状态处理
                case INNUM:
                    //如果是数字，会自动保持数字状态，不是数字的话就完成;
                    if (!isDigit(line[i])) {
                        word.erase(word.end()-1); // ch
                        Token token = Token(INTC,word,lineNumber);
                        list.AddToken(token);
                        word="";
                        i--;
                        stateEnum = NORMAL;
                    }else{
                        //没完事，继续读数字
                        stateEnum = INNUM;
                    }
                    break;
                case INASSIGN:
                    if (line[i] == '=') {
                        Token token = Token(ASSIGN,":=",lineNumber);
                        list.AddToken(token);
                        word="";
                        stateEnum = NORMAL;
                    } else {
                        //‘：’之后如果不是‘=’,那么一定是错的
                        stateEnum = ERROR;
                    }
                    break;
                case INDOT:
                    /*
                     * 句号，有两种情况，一个是数组声明的时候用两个.来声明，一个是程序结束
                     */
                    if (isAlpha(line[i])) {          // record域中的点运算符
                        word.erase(word.end()-1);
                        Token token = Token(RECORD,word,lineNumber);
                        list.AddToken(token);
                        word = "";
                        stateEnum = NORMAL;
                    }else if (line[i] == ' ' || line[i] == '\n'){
                        Token token = Token(EoF,".",lineNumber);
                        list.AddToken(token);
                        return list;
                    }
                    break;
                case INRANGE:
                    if (isDigit(line[i+1])) {
                        // 回溯
                        word.erase(word.begin());
                        word.erase(word.begin());
                        Token token = Token(UNDERRANGE,"..",lineNumber);
                        list.AddToken(token);
                        stateEnum = NORMAL;
                    } else{
                        // 如果后面不是数字，那么error
                        stateEnum = ERROR;
                    }
                    break;
                case INCHAR:
                    if (isDigit(line[i]) || isAlpha(line[i])) {
                        stateEnum = INCHAR;
                    }else if (line[i] == '\''){
                        word.erase(word.end()-1);
                        Token token = Token(CHAR,word,lineNumber);
                        list.AddToken(token);
                        word = "";
                        stateEnum = NORMAL;
                    } else{
                        word = "";
                        stateEnum = ERROR;
                    }
                    break;
                case ERROR:
                    Token ErrorToken = Token(Error, word, lineNumber);
                    word = "";
            }
        }
        lineNumber++;           //行数自增1
    }
    return list;
}

DFA::DFA() = default;

#endif //SNLCOMPILER_DFA_HPP