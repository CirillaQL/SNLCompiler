#include "WordAnalysis/FileReader.hpp"
#include "WordAnalysis/Token.hpp"
#include "WordAnalysis/DFA.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    DFA a = DFA();
    TokenList p = a.getTokenlist("1.txt");
    p.print();
    //FileReader fi = FileReader();
   // fi.ReadFile("1.txt");
    //fi.ShowFile();
    /*TokenList o = TokenList();
    for (int i = 0; i < l.size(); ++i) {
        getToken(o,l[i],i);
    }
    vector<Token> ans = o.getTokenList();
    //setlocale(LC_ALL, "chs");
    cout << "单词属性             " << "内容                " << "行数        "<<endl;
    for(auto item : ans){

        string a1 = transformE2S(item.getType());
        string a2 = item.getValue();
        a1.resize(20,' ');
        a2.resize(20,' ');
        cout << a1 << a2 << item.getLine() <<endl;
    }*/
    //TokenList o = TokenList();
    //getToken(o,"program p type t = integer; var t v1; ",0);
    return 0;
}
