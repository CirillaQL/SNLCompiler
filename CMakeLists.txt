cmake_minimum_required(VERSION 3.16)
project(SNLCompiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(SNLCompiler main.cpp WordAnalysis/FileReader.hpp WordAnalysis/Token.hpp WordAnalysis/Word.hpp SyntacticAnalysis/Syntax.hpp WordAnalysis/DFA.hpp SyntacticAnalysis/AnalysisStack.hpp SyntacticAnalysis/Production.hpp SyntacticAnalysis/Tree.hpp)