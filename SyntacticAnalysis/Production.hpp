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
    vector<string> Derivations;
    vector<string> PredictSets;
public:
    Production();
    Production(const string& _content, const vector<string>& _derivations, const vector<string>& _predictsets);
    //插入生成导出式
    void insertDerivation(const string& _derivation);
    //插入select集元素
    void insertPredictSet(const string& _predictset);
    //设置符号
    void setContent(const string& input);

    const string &getContent() const;

    const vector<string> &getDerivations() const;

    const vector<string> &getPredictSets() const;
};

Production::Production(const string &_content, const vector<string> &_derivations,
                       const vector<string> &_predictsets) {
    this->Content = _content;
    this->Derivations = _derivations;
    this->PredictSets = _predictsets;
}

void Production::insertDerivation(const string& _derivation) {
    this->Derivations.push_back(_derivation);
}

void Production::insertPredictSet(const string& _predictset) {
    this->PredictSets.push_back(_predictset);
}

void Production::setContent(const string& input) {
    this->Content = input;
}

const string &Production::getContent() const {
    return Content;
}

const vector<string> &Production::getDerivations() const {
    return Derivations;
}

const vector<string> &Production::getPredictSets() const {
    return PredictSets;
}

Production::Production() = default;

#endif //SNLCOMPILER_PRODUCTION_HPP
