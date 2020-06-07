//
// Created by QianLu on 2020/6/2.
//

#ifndef SNLCOMPILER_SYNTAX_HPP
#define SNLCOMPILER_SYNTAX_HPP

#include "Production.hpp"
//#include "WordAnalysis/DFA.hpp"
#include <fstream>
#include <iostream>
#include <stack>
class LL1Syntax{
private:
    //存储Production推导式
    vector<Production> tables;
    //分析栈
    stack<string> AnalysisStack;
public:
    //根据上下文无关文法生成Precdict
    void initProductions(const string& filename);
    //输出表
    void print();
    //分析栈入栈
    void LL1();
    //替换函数，将栈顶的元素替换成推导式
    void Replace();
};

/*
 * 初始化LL1分析表，通过推导式表示.
 */
void LL1Syntax::initProductions(const string& filename) {
    ifstream infile(filename);
    string line;

    if (infile){
        string value;
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
            int j = i + 2;
            for (; j < ans.size(); ++j) {
                if (ans[j] == '#'){
                    word = "";
                    break;
                }else if (ans[j] == ' '){
                    if (word == "" || word ==" "){
                        break;
                    } else{
                        a.insertDerivation(word);
                        word = "";
                    }
                }else{
                    word += ans[j];
                }
            }
            for (int k = j+13; k < ans.size(); ++k) {
                if (ans[k] != ' '){
                    word += ans[k];
                }else{
                    a.insertPredictSet(word);
                    word = "";
                }
            }
            tables.push_back(a);
        }
    }
}

void LL1Syntax::print() {
    for (auto item : this->tables){
        //cout << item.first;
        //cout << item.second.getPredictSets()
    }
}

void LL1Syntax::LL1() {
    this->AnalysisStack.push(tables[0].getContent());
}

void LL1Syntax::Replace() {
    //todo为栈顶元素
    string todo = this->AnalysisStack.top();
    const vector<string>& todo_predictSet = todo.getPredictSets();
    vector<string>::const_reverse_iterator i = todo_predictSet.rbegin();
    for (std::set<int>::reverse_iterator it=todo_predictSet.rbegin();it != todo_predictSet.rend();++it) {

    }

}


#endif //SNLCOMPILER_SYNTAX_HPP
