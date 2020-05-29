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
static std::string reservedWords[] = {"program", "type", "var", "procedure", "begin", "end", "array", "of", "record",
                                      "if", "then",
                                      "else", "fi", "while", "do", "endwh", "read", "write", "return", "integer", "char"
};

/*
 * 源代码中待处理的Word信息结构体
 */
struct WordInfo{
    std::string value;
    unsigned short word_line;
    WordInfo();
    WordInfo(const std::string& value, unsigned short& word_line);
    ~WordInfo();
};

WordInfo::WordInfo() {
    this->value = "";
    this->word_line = 0;
}

WordInfo::WordInfo(const std::string& value, unsigned short& word_line) {
    this->value = value;
    this->word_line = word_line;
}

WordInfo::~WordInfo() {
    word_line=0;
    value="";
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
    std::vector<WordInfo> WordList;
    std::vector<Token> tokenList;
public:
    TokenList();

    const std::vector<Token> &getTokenList() const;

    void setTokenList(const std::vector<Token> &tokenList);

    ~TokenList();

    //向TokenList中添加Token
    void AddToken(const Token& token);

    //从FileReader中获取
    void getWordList(const std::string& filename);

    const std::vector<WordInfo> &getWordList1() const;
};

void TokenList::getWordList(const std::string& filename) {
    FileReader fileReader = FileReader();
    fileReader.ReadFile(filename);
    if (fileReader.getSrcLine().empty()){
        throw std::invalid_argument("源代码文件为空");
    }
    const std::vector<std::string> _line = fileReader.getSrcLine();
    std::string _word = "";
    auto word = WordInfo();
    for (unsigned short i = 0; i < _line.size(); ++i) {
        for (char ch : _line[i]) {
            /*std::cout << (int )ch << " ";

            std::cout << ch << " ";
            std::cout << std::endl;
             */

            if (ch == ' ' || ch == '\n' || ch < 48 || 58 <= ch < 65 || ch > 122 ){

                word.value = _word;
                word.word_line = i;
                WordList.push_back(word);
                word.value = "";
                word.word_line = 0;
                _word = "";
            } else{
                _word += ch;
            }
        }
        //_word = "";
    }

}

void TokenList::AddToken(const Token &token) {
    this->tokenList.push_back(token);
}

const std::vector<Token> &TokenList::getTokenList() const {
    return tokenList;
}

void TokenList::setTokenList(const std::vector<Token> &tokenList) {
    TokenList::tokenList = tokenList;
}

const std::vector<WordInfo> &TokenList::getWordList1() const {
    return WordList;
}

TokenList::~TokenList() = default;

TokenList::TokenList() = default;


#endif //SNLCOMPILER_TOKEN_HPP
