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
    //�洢Production�Ƶ�ʽ
    vector<Production> tables;
    //����ջ
    stack<string> AnalysisStack;
    //TokenList����
    vector<Token> tokenList;
    //�������
    vector<string> ans;
public:
    //�����������޹��ķ�����Precdict
    void initProductions(const string &filename);

    //�����
    void print();

    //����ջ��ջ
    void LL1();

    //�滻��������ջ����Ԫ���滻���Ƶ�ʽ
    void Replace(const string &input);

    //setTokenList
    void setTokenList(const TokenList &tokenlist);

    //����
    void Analysis();
};

/*
 * ��ʼ��LL1������ͨ���Ƶ�ʽ��ʾ.
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

    //todoΪջ��Ԫ��
    string todo = this->AnalysisStack.top();
    /*
     * �����жϣ�ջ��Ԫ���ǲ���ֱ�ӵ��ڵ�ǰToken
     */
    if (this->AnalysisStack.top() == input) {
        string temp = "�ҵ� "+this->AnalysisStack.top();
        this->ans.push_back(temp);
        this->AnalysisStack.pop();
        cout << "�ҵ� :" << input << endl;
        return;
    }

    for (auto item : this->tables) {
        /*
         * ���Ƶ�ʽ�����ҵ�Production->Content == ��ǰջ��string��item
         */
        if (item.getContent() == todo) {
            /*
             * ������ӦProduction��PredictSet,�жϵ�ǰTokenList���˵�Ԫ���ǲ����ڵ�ǰProduction��Ӧ�ս����
             * ��Ҫע����ǣ���txt�ĵ��У������ж��Production����ͬ����ֵ�������Ҫinput���ĸ�����
             */
            for (auto predictset : item.getPredictSets()) {
                if (input == predictset) {
                    /*
                     * �ҵ��ˣ�����ջ��������Derivation�дӺ���ǰ��ջ������ջ��Ԫ�ؾ��ǵ�һ��Derivation
                     * ע�⣬��DerivationΪEPSILONʱ������ջ
                     */
                    cout << "�ҵ����滻ʽ: "<<endl;
                    cout << item.getContent() << " : ";
                    for (auto p : item.getDerivations()) {
                        cout << p <<" ";
                    }
                    cout <<endl;
                    /*
                     * ����鿴     ��
                     */
                    this->AnalysisStack.pop();
                    //���������ջ
                    for (int i = item.getDerivations().size() - 1; i >= 0; i--) {
                        /*
                         * ����Ǧ��Թ�
                         */
                        if (item.getDerivations()[i] == "EPSILON") {
                            continue;
                        } else {
                            this->AnalysisStack.push(item.getDerivations()[i]);
                        }
                    }
                    /*
                     * ��������ǵ�ǰԪ�أ��򵯳�(ƥ�䵽��)�����򣬵ݹ顣
                     */
                    if (this->AnalysisStack.top() == input) {
                        string temp = "�ҵ� "+this->AnalysisStack.top();
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
     * �����ǰջ��Ԫ��
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
 * �����﷨��˼�룺��ƥ�䵽��ǰԪ�ز�����ʱ�����Ԫ�����ʣ���ȷ���﷨�������������
 *
 */



#endif //SNLCOMPILER_SYNTAX_HPP
