//
// Created by qianlu on 2020/5/26.
//

#ifndef SNLCOMPILER_FILEREADER_HPP
#define SNLCOMPILER_FILEREADER_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class FileReader{
private:
    //采用vector来存储每一行的文本
    std::vector<std::string> SrcLine;
public:
    FileReader();
    ~FileReader();
    void ReadFile(const std::string& filename);
    const std::vector<std::string> &getSrcLine() const;
};

FileReader::FileReader() = default;
FileReader::~FileReader() = default;
void FileReader::ReadFile(const std::string &filename) {
    std::ifstream infile(filename);
    std::string line;
    //判断是否打开文件，之后读取
    if (infile){
        while (getline(infile,line)){
            SrcLine.push_back(line);
        }
    }
    else{
        std::cout << "文本文件未打开" << std::endl;
    }
}

const std::vector<std::string> &FileReader::getSrcLine() const {
    return SrcLine;
}

#endif //SNLCOMPILER_FILEREADER_HPP
