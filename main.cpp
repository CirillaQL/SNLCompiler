
#include "WordAnalysis/Token.hpp"
#include "WordAnalysis/DFA.hpp"
#include "SyntacticAnalysis/Syntax.hpp"
using namespace std;

int main()
{
    LL1Syntax k = LL1Syntax();
    k.initProductions("productionLines.txt");
    k.print();
    return 0;
}
