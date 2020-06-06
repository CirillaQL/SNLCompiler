//
// Created by QianLu on 2020/6/2.
//

#ifndef SNLCOMPILER_SYNTAX_HPP
#define SNLCOMPILER_SYNTAX_HPP

#include "Production.hpp"
#include "AnalysisStack.hpp"
#include <fstream>
#include <iostream>

class LL1Syntax{
private:
    vector<Production> tables;
public:
    //根据上下文无关文法生成Precdict
    void initProductions(const string& filename);
    //输出表
    void print();
};

/*
 * 初始化LL1分析表，通过推导式表示.
 */
void LL1Syntax::initProductions(const string& filename) {
    ifstream infile(filename);
    string line;
    if (infile){
        while (getline(infile,line)){
            string ans = line +' ';
            Production a = Production();
            vector<string> Derivations;
            string word;
            int i = 0;
            for (; i < ans.size()-1; ++i) {
                if (ans[i]!='-' && ans[i+1] != '>') {
                    word += ans[i];
                }
                else{
                    a.setContent(word);
                    word = "";
                    break;
                }
            }
            for (int j = i+2; j < ans.size(); ++j) {
                if (ans[j] != ' '){
                    word += ans[j];
                } else {
                    a.insertDerivation(word);
                    word = "";
                }
            }
            tables.push_back(a);
        }
    }
}

void LL1Syntax::print() {
    for (auto item : this->tables){
        cout << item.getContent() << " -> ";
        for (auto p : item.getDerivations()) {
            cout << p << " ";
        }
        cout << endl;
    }
}


#endif //SNLCOMPILER_SYNTAX_HPP
