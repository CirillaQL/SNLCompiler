//
// Created by QianLu on 2020/6/10.
//

#ifndef SNLCOMPILER_TREE_HPP
#define SNLCOMPILER_TREE_HPP

#include "Syntax.hpp"
#include "../WordAnalysis/Token.hpp"
#include <string>
#include <queue>

const string nodekind[] = {"Prok","PheadK","TypeK", "Vark", "ProcDecK","StmLK","DecK","Stmtk","ExpK"};
const string kindDec[] = {"ArrayK","CharK","IntegerK","RecordK","IdK"};
const string kindStmt[] = {"IfK","WhileK","AssignK","ReadK","WriteK","CallK","ReturnK"};
const string kindexp[] = {"OpK","ConstK","IdK"};

/*
 * 语法树节点的类
 */
class TreeNode{
private:
    int line;
    string NodeKind;
    string value;
    Word real_Kind;
public:
    TreeNode();
    void setKind(const string& _kind);
    void setValue(const string& _value);

    int getLine() const;

    void setLine(int line);

    void setNodeKind(const string &nodeKind);

    const string &getNodeKind() const;

    const string &getValue() const;

    Word getRealKind() const;

    void setRealKind(Word realKind);
};

TreeNode::TreeNode() {
    this->NodeKind = "";
    this->value = "";
}

void TreeNode::setKind(const string &_kind) {
    this->NodeKind = _kind;
}

void TreeNode::setValue(const string &_value) {
    this->value = _value;
}

const string &TreeNode::getNodeKind() const {
    return NodeKind;
}

const string &TreeNode::getValue() const {
    return value;
}

int TreeNode::getLine() const {
    return line;
}

void TreeNode::setLine(int line) {
    TreeNode::line = line;
}

void TreeNode::setNodeKind(const string &nodeKind) {
    NodeKind = nodeKind;
}

Word TreeNode::getRealKind() const {
    return real_Kind;
}

void TreeNode::setRealKind(Word realKind) {
    real_Kind = realKind;
}


class TreeDraw{
private:
    queue<TreeNode> GrammarStack;
    queue<TreeNode> OperandStack;
    vector<Token> TokenList;
    int Grammarsuojin = 1;
    int Operandsuojin = 2;
public:
    void setTokenList(vector<Token> p){
        this->TokenList = p;
    }
    void InQueue(){
        for (auto item : TokenList) {
            if(item.isGrammer()){
                TreeNode a = TreeNode();
                a.setValue(item.getValue());
                a.setKind(transformE2S(item.getType()));
                a.setLine(item.getLine());
                a.setRealKind(item.getType());
                GrammarStack.push(a);
            } else if (item.isOp()){
                TreeNode a = TreeNode();
                a.setValue(item.getValue());
                a.setKind(transformE2S(item.getType()));
                a.setLine(item.getLine());
                a.setRealKind(item.getType());
                OperandStack.push(a);
            }
        }
    }

    void printBlank(int n){
        for (int i = 0; i < 4*n; ++i) {
            cout << " ";
        }
    }

    void PrintHead(TreeNode a){
        if (a.getRealKind() == TYPE){
            cout << "TypeK" ;
        }else if (a.getRealKind() == PROCEDURE){
            cout << "ProcDeck" ;
        }else if (a.getRealKind() == PROGRAM){
            cout << "PheadK" << " ";
        }else if (a.getRealKind() == VAR){
            cout << "VarK" << " ";
        }else if (a.getRealKind() == BEGIN ){
            this->Operandsuojin++;
            this->Grammarsuojin++;
            cout << "StmLk" ;
        }else if (a.getRealKind() == END || a.getRealKind() == ENDWH){
            this->Grammarsuojin--;
            this->Operandsuojin--;
            cout << a.getNodeKind() << " ";
        }
        else{
            cout << a.getNodeKind() << " ";
        }
    }

    void print(){
        int line = 1;
        cout << "Prok" << endl;
        for (; line < 40; line++) {
            while (GrammarStack.front().getLine() == line){
                printBlank(Grammarsuojin);
                PrintHead(GrammarStack.front());
                GrammarStack.pop();
                cout << endl;
            }
            while (OperandStack.front().getLine() == line){
                printBlank(Operandsuojin);
                PrintHead(OperandStack.front());
                cout <<" " << OperandStack.front().getValue();
                OperandStack.pop();
                cout << endl;
            }
        }
    }
};



/*
class Line{
private:
    vector<Token> TokenListOfLine;
public:
    void addToken(const Token& input);

    const vector<Token> &getTokenListOfLine() const;

    void setTokenListOfLine(const vector<Token> &tokenListOfLine);

    void clear();
};

void Line::addToken(const Token &input) {
    this->TokenListOfLine.push_back(input);
}

const vector<Token> &Line::getTokenListOfLine() const {
    return TokenListOfLine;
}

void Line::setTokenListOfLine(const vector<Token> &tokenListOfLine) {
    TokenListOfLine = tokenListOfLine;
}

void Line::clear() {
    this->TokenListOfLine.clear();
}

void printBlank(int n){
    for (int i = 0; i < 4*n; ++i) {
        cout << " ";
    }
}

vector<Line> GetLineList(vector<Token> tokenList){
    int line = 1;
    vector<Line> ans;
    Line temp;
    for (auto item : tokenList) {
        if(item.getLine() == line){
            cout << item.getValue() << " ";
            temp.addToken(item);
        } else{
            line++;
            cout << endl;
            cout << item.getValue() << " ";
            ans.push_back(temp);
            temp.clear();
            temp.addToken(item);
        }
    }
    return ans;
}


void PrintTree(const vector<Line>& LineList){
    int level = 0;
    for (auto line : LineList){
        vector<Token> itemList = line.getTokenListOfLine();
        for (int i = 0; i < itemList.size(); ++i) {
            if (itemList[i].getType() == PROGRAM){
                cout << "Prok" << endl;
                level++;
            }
            else if (itemList.)
        }
    }
}
*/


#endif //SNLCOMPILER_TREE_HPP
