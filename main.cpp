#include "Scanner/FileReader.hpp"
#include "Scanner/Token.hpp"
#include "Scanner/WordDFA.h"
#include <iostream>

using namespace std;

int main()
{
    /*
    TokenList k = TokenList();
    k.getWordList("1.txt");
    auto l = k.getWordList1();
    for (auto m : l) {
        cout << "单词内容： " << m.value << "    " << "行数: "<< m.word_line << endl;
    }*/
    TokenList o = TokenList();
    getToken(o,"program * * * * \n * if while",0);
    return 0;
}
