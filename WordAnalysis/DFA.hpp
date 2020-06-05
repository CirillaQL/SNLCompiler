//
// Created by QianLu on 2020/6/3.
//

#ifndef SNLCOMPILER_DFA_HPP
#define SNLCOMPILER_DFA_HPP

#include "Token.hpp"

using namespace std;

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

//�ʷ���������DFA�Զ���
class DFA{
private:
    enum StateEnum{
        NORMAL,             //��ʼ״̬
        INID,               //��ʶ��״̬
        INNUM,              //����״̬
        INASSIGN,           //��ֵ״̬(:
        INCOMMIT,           //ע��״̬
        INDOT,              //��״̬
        INRANGE,            //�����±����״̬
        INCHAR,             //�ַ���־״̬
        ERROR               //����
    };
public:
    DFA();
    TokenList getTokenlist(const string& filename);

};

TokenList DFA::getTokenlist(const string &filename) {
    FileReader fileReader = FileReader();
    fileReader.ReadFile(filename);
    //��ɶ�ȡԴ�ļ�
    vector<string> srcLine = fileReader.getSrcLine();
    //��ȡ��Դ�ļ�������
    //��ʼ��TokenList
    TokenList list = TokenList();
    //ÿ�еĶ�ȡ�봦��
    int lineNumber = 1;
    for(const auto& line : srcLine){
        //ÿ�еľ������
        int length = line.size();
        string word;
        StateEnum stateEnum = NORMAL;
        for (int i = 0; i <= length; i++) {
            word += line[i];
            switch (stateEnum) {
                case NORMAL:
                    //һ��ʼ���룬��ʼ��
                    //���SΪ��ĸ��תINID
                    if (isAlpha(line[i])){
                        stateEnum = INID;
                    }
                    //���SΪ���֣�תINNUM;
                    else if(isDigit(line[i])){
                        stateEnum = INNUM;
                    }
                    //Ϊ�ո�
                    else if (isBlank(line[i])){
                        word.erase(word.end()-1);
                        stateEnum = NORMAL;
                    }
                    //���SΪ��������ת��ֵ
                    else if (line[i] == ':'){
                        stateEnum = INASSIGN;
                    }
                    //���SΪ'{'����
                    else if (line[i] == '{'){
                        stateEnum = INCOMMIT;
                    }
                    //���SΪ.�ж������黹�ǽ���
                    else if(line[i] == '.'){
                        if (line[i+1] == '.'){
                            stateEnum = INRANGE;
                        } else {
                            stateEnum = INDOT;
                        }
                    }
                    //���SΪ',������ַ�
                    else if (line[i] == '\''){
                        stateEnum = INCHAR;
                    }
                    //���µ���Ϊ�ж������ַ�
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
                //��ʶ������
                case INID:
                    if (isAlpha(line[i]) || isDigit(line[i])) {
                        //û���£�����
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
                        //���Token���
                        if (line[i] == ' '){
                            i++;
                            word = "";
                        }
                        i--;
                        stateEnum = NORMAL;
                    }
                    break;
                //����״̬����
                case INNUM:
                    //��������֣����Զ���������״̬���������ֵĻ������;
                    if (!isDigit(line[i])) {
                        word.erase(word.end()-1); // ch
                        Token token = Token(INTC,word,lineNumber);
                        list.AddToken(token);
                        word="";
                        i--;
                        stateEnum = NORMAL;
                    }else{
                        //û���£�����������
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
                        //������֮��������ǡ�=��,��ôһ���Ǵ��
                        stateEnum = ERROR;
                    }
                    break;
                case INDOT:
                    /*
                     * ��ţ������������һ��������������ʱ��������.��������һ���ǳ������
                     */
                    if (isAlpha(line[i])) {          // record���еĵ������
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
                        // ����
                        word.erase(word.begin());
                        word.erase(word.begin());
                        Token token = Token(UNDERRANGE,"..",lineNumber);
                        list.AddToken(token);
                        stateEnum = NORMAL;
                    } else{
                        // ������治�����֣���ôerror
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
                    cout << "�����޷�ʶ���" << lineNumber << "�д���"<< endl;
                    word = "";
                    exit(1);
            }
        }
        lineNumber++;           //��������1
    }
    return list;
}

DFA::DFA() = default;

#endif //SNLCOMPILER_DFA_HPP