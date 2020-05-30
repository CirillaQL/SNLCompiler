//
// Created by qianlu on 2020/5/29.
//

#ifndef SNLCOMPILER_WORDDFA_H
#define SNLCOMPILER_WORDDFA_H

#include <string>
#include "Token.hpp"
#include "Word.hpp"

enum StateEnum{
    NORMAL,             //��ʼ״̬
    INID,               //��ʶ��״̬
    INNUM,              //����״̬
    INASSIGN,           //��ֵ״̬
    INDOT,              //��״̬
    INRANGE,            //�����±����״̬
    INCHAR,             //�ַ���־״̬
    ERROR               //����
};

//�ж�Ϊ��ĸ
bool isAlpha(const char& ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

//�ж�Ϊ����
bool isDigit(const char& ch){
    return (ch >= '0' && ch <= '9');
}

//�ж�Ϊ�ո�
bool isBlank(const char& ch){
    return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
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
                    stateEnum = INDOT;            // ��ĵ������
                } else if (ch == '\'') {
                    word.erase(word.end()-1);
                    stateEnum = INCHAR;
                } else {
                    stateEnum = ERROR;
                }
                break;
            /*
             * INID״̬���ж��Ƿ�Ϊ�ؼ���
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
                    //���Token���
                    word = "";
                    stateEnum = NORMAL;
                }
                break;
            case INNUM:
                //��������֣����Զ���������״̬���������ֵĻ������;
                if (!isDigit(ch)) {
                    word.erase(word.end()-1); // ch
                    Token token = Token(INTC,word,line);
                    list.AddToken(token);
                    word = "";
                    stateEnum = NORMAL;
                }
                break;
            case INASSIGN:
                //��ֵ���
                if (ch == '=') {
                    Token token = Token(ASSIGN,":=",line);
                    list.AddToken(token);
                    word="";
                    stateEnum = NORMAL;
                } else {
                    //������֮��������ǡ�=��,��ôһ���Ǵ��
                    word = "";
                    stateEnum = ERROR;
                }
                break;
            case INDOT:
                /*
                 * ��ţ������������һ��������������ʱ��������.��������һ���ǳ������
                 */
                if (isAlpha(ch)) {          // record���еĵ������
                    word.erase(word.end()-1);
                    Token token = Token(RECORD,word,line);
                    list.AddToken(token);
                    word = "";
                    stateEnum = NORMAL;
                } else if (ch == '.') {     // ������±������
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
                    // ����
                    word.erase(word.begin());
                    word.erase(word.begin());
                    Token token = Token(UNDERRANGE,"..",line);
                    list.AddToken(token);
                    stateEnum = NORMAL;
                } else{
                    // ������治�����֣���ôerror
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
}

class DFA{
private:
    FileReader inputFile;
    TokenList tokenList;
public:
    DFA();
    DFA(const std::string& FileName);
    void setFileName(const std::string& FileName);
    TokenList getTokenList();
    void showTokenList();
};

DFA::DFA(const std::string &FileName) {
    this->inputFile.ReadFile(FileName);
}

void DFA::setFileName(const std::string &FileName) {
    this->inputFile.ReadFile(FileName);
}

TokenList DFA::getTokenList() {
    int Length = this->inputFile.getSrcLine().size();
    for (int i = 0; i < Length; ++i) {
        getToken(this->tokenList,this->inputFile.getSrcLine()[i],i);
    }
    //setlocale(LC_ALL, "chs");
    //cout << "��������             " << "����                " << "����        "<<endl;
    /*for(auto item : this->tokenList.getTokenList()){
        string a1 = transformE2S(item.getType());
        string a2 = item.getValue();
        a1.resize(20,' ');
        a2.resize(20,' ');
        cout << a1 << a2 << item.getLine() <<endl;
    }*/
    return this->tokenList;
}

void DFA::showTokenList() {
    std::cout << "��������             " << "����                " << "����        "<<std::endl;
    for(auto item : this->tokenList.getTokenList()){
        std::string a1 = transformE2S(item.getType());
        std::string a2 = item.getValue();
        a1.resize(20,' ');
        a2.resize(20,' ');
        std::cout << a1 << a2 << item.getLine() <<std::endl;
    }
}

DFA::DFA() = default;

#endif //SNLCOMPILER_WORDDFA_H
