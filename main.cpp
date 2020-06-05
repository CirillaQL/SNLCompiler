
#include "WordAnalysis/Token.hpp"
#include "WordAnalysis/DFA.hpp"

using namespace std;

int main()
{
    DFA a = DFA();
    TokenList p = a.getTokenlist("1.txt");
    p.print();
    return 0;
}
