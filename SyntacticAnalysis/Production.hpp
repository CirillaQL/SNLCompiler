//
// Created by QianLu on 2020/6/5.
//

#ifndef SNLCOMPILER_PRODUCTION_HPP
#define SNLCOMPILER_PRODUCTION_HPP

#include <string>
#include <vector>
#include <set>

using namespace std;


/*
 * Select(predict)集合，用来进行LL1文法
*/
class Production{
private:
    string Content;
    vector<Production> Derivation;
    vector<Production> PredictSet;
public:
    Production();
    Production(const string& _content, const vector<Production>& _derivation, const vector<Production>& _predictset);
};

Production::Production(const string &_content, const vector<Production> &_derivation,
                       const vector<Production> &_predictset) {
    this->Content = _content;
    this->Derivation = _derivation;
    this->PredictSet = _predictset;
}

Production::Production() = default;

#endif //SNLCOMPILER_PRODUCTION_HPP
