#include "Scanner/FileReader.hpp"

#include <iostream>

using namespace std;

int main()
{
    FileReader file = FileReader();
    file.ReadFile("1.txt");
    for(auto p : file.getSrcLine()){
        cout << p << endl;
    }
    return 0;
}
