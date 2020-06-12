//
// Created by QianLu on 2020/6/2.
//

#ifndef SNLCOMPILER_SYNTAX_HPP
#define SNLCOMPILER_SYNTAX_HPP

#include "Production.hpp"
//#include "WordAnalysis/Word.hpp"
#include <fstream>
#include <iostream>
#include <stack>

class LL1Syntax {
private:
    //存储Production推导式
    vector<Production> tables;
    //分析栈
    stack<string> AnalysisStack;
    //TokenList序列
    vector<Token> tokenList;
    //输出序列
    vector<string> ans;
public:
    //根据上下文无关文法生成Precdict
    void initProductions(const string &filename);

    //输出表
    void print();

    //分析栈入栈
    void LL1();

    //替换函数，将栈顶的元素替换成推导式
    void Replace(const string &input);

    //setTokenList
    void setTokenList(const TokenList &tokenlist);

    //分析
    void Analysis();
};

/*
 * 初始化LL1分析表，通过推导式表示.
 */
void LL1Syntax::initProductions(const string &filename) {
    ifstream infile(filename);
    string line;

    if (infile) {
        string value;
        while (getline(infile, line)) {
            string ans = line + ' ';
            Production a = Production();
            vector<string> Derivations;
            string word;
            int i = 0;
            for (; i < ans.size() - 1; ++i) {
                if (ans[i] != '-' && ans[i + 1] != '>') {
                    word += ans[i];
                } else {
                    a.setContent(word);
                    word = "";
                    break;
                }
            }
            int j = i + 2;
            for (; j < ans.size(); ++j) {
                if (ans[j] == '#') {
                    word = "";
                    break;
                } else if (ans[j] == ' ') {
                    if (word == "" || word == " ") {
                        break;
                    } else {
                        a.insertDerivation(word);
                        word = "";
                    }
                } else {
                    word += ans[j];
                }
            }
            for (int k = j + 13; k < ans.size(); ++k) {
                if (ans[k] != ' ') {
                    word += ans[k];
                } else {
                    a.insertPredictSet(word);
                    word = "";
                }
            }
            tables.push_back(a);
        }
    }
}

void LL1Syntax::print() {
    for (auto item : this->tables) {
        //cout << item.first;
        //cout << item.second.getPredictSets()
    }
}

void LL1Syntax::LL1() {
    this->AnalysisStack.push(tables[0].getContent());
}

void LL1Syntax::Replace(const string &input) {
    if (input == "EOF")
        return;

    //todo为栈顶元素
    string todo = this->AnalysisStack.top();
    /*
     * 首先判断，栈顶元素是不是直接等于当前Token
     */
    if (this->AnalysisStack.top() == input) {
        string temp = "找到 "+this->AnalysisStack.top();
        this->ans.push_back(temp);
        this->AnalysisStack.pop();
        cout << "找到 :" << input << endl;
        return;
    }

    for (auto item : this->tables) {
        /*
         * 在推导式表中找到Production->Content == 当前栈顶string的item
         */
        if (item.getContent() == todo) {
            /*
             * 遍历对应Production的PredictSet,判断当前TokenList顶端的元素是不是在当前Production对应终结符中
             * 需要注意的是，在txt文档中，可能有多个Production有相同的左值，因此需要input在哪个当中
             */
            for (auto predictset : item.getPredictSets()) {
                if (input == predictset) {
                    /*
                     * 找到了，分析栈弹出，在Derivation中从后往前入栈，这样栈顶元素就是第一个Derivation
                     * 注意，当Derivation为EPSILON时，不入栈
                     */
                    cout << "找到了替换式: "<<endl;
                    cout << item.getContent() << " : ";
                    for (auto p : item.getDerivations()) {
                        cout << p <<" ";
                    }
                    cout <<endl;
                    /*
                     * 输出查看     ↑
                     */
                    this->AnalysisStack.pop();
                    //倒叙遍历入栈
                    for (int i = item.getDerivations().size() - 1; i >= 0; i--) {
                        /*
                         * 如果是ε略过
                         */
                        if (item.getDerivations()[i] == "EPSILON") {
                            continue;
                        } else {
                            this->AnalysisStack.push(item.getDerivations()[i]);
                        }
                    }
                    /*
                     * 如果顶端是当前元素，则弹出(匹配到了)，否则，递归。
                     */
                    if (this->AnalysisStack.top() == input) {
                        string temp = "找到 "+this->AnalysisStack.top();
                        this->ans.push_back(temp);
                        this->AnalysisStack.pop();
                    } else {
                        Replace(input);
                    }
                }
            }
        }
    }

    /*
     * 输出当前栈中元素
     */


    vector<string> check;
    if(this->AnalysisStack.empty()){
        cout << "Analysis Stack is Empty" << endl;
        return;
    }
}

void LL1Syntax::setTokenList(const TokenList &tokenlist) {
    this->tokenList = tokenlist.getTokenList();
}

void LL1Syntax::Analysis() {
    for (auto & i : this->tokenList) {
        Replace(transformE2S(i.getType()));
    }
}

/*
 * 绘制语法树思想：在匹配到当前元素并弹出时，检测元素性质，并确定语法树的缩进输出。
 *
 */



#endif //SNLCOMPILER_SYNTAX_HPP
