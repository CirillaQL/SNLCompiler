
#include "WordAnalysis/Token.hpp"
#include "WordAnalysis/DFA.hpp"
#include "SyntacticAnalysis/Syntax.hpp"
using namespace std;

int main()
{
    DFA sss = DFA();
    TokenList p = sss.getTokenlist("1.txt");

    LL1Syntax k = LL1Syntax();
    k.initProductions("productionLines.txt");
    k.setTokenList(p);
    k.LL1();

    k.Analysis();

    return 0;
}
