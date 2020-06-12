
#include "WordAnalysis/Token.hpp"
#include "WordAnalysis/DFA.hpp"
#include "SyntacticAnalysis/Syntax.hpp"
#include "SyntacticAnalysis/Tree.hpp"
using namespace std;

int main()
{
    /*      LL1∑÷Œˆ≤‚ ‘    */
    DFA sss = DFA();
    TokenList p = sss.getTokenlist("1.txt");

    TreeDraw kkk = TreeDraw();
    kkk.setTokenList(p.getTokenList());
    kkk.InQueue();
    kkk.print();

    /*
    LL1Syntax k = LL1Syntax();
    k.initProductions("productionLines.txt");
    k.setTokenList(p);
    k.LL1();

    k.Analysis();
    */
    //vector<Line> ans;
    //ans = GetLineList(p.getTokenList());

    return 0;
}
