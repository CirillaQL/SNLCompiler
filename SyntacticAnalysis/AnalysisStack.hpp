//
// Created by QianLu on 2020/6/5.
//

#ifndef SNLCOMPILER_ANALYSISSTACK_HPP
#define SNLCOMPILER_ANALYSISSTACK_HPP

#include <stack>
#include "Production.hpp"

using namespace std;

//分析栈
class AnalysisStack{
private:
    stack<Production> AnalysisStack;
};

#endif //SNLCOMPILER_ANALYSISSTACK_HPP
