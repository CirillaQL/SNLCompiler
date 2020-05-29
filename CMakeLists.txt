cmake_minimum_required(VERSION 3.16)
project(SNLCompiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(SNLCompiler main.cpp Scanner/FileReader.hpp Scanner/Token.hpp Scanner/Word.hpp Scanner/WordDFA.h)