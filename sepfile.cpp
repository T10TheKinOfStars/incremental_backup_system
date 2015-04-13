#include "sepfile.hpp"
#include <fstream>
#include <cstdlib>

using namespace file;

FileWorker::~FileWorker() {
    path = "";
    blocks.clear();
    blocksize = 0;
}

std::string FileWorker::getxFileBlock(int idx) {
    return blocks[idx];
}

int FileWorker::getBlockSize() {
    return blocks.size();
}

void FileWorker::processFile() {
    std::ifstream ifs(path.c_str(),std::ifstream::binary);
    
    if (ifs) {
        while (ifs.tellg() != -1) {
            char *s = new char[blocksize+1];
            ifs.read(s,blocksize);
            s[blocksize] = '\0';
            blocks.push_back(std::string(s));
            delete s;
        }
    } else {
        std::cerr<<"Read FileWorker failed"<<std::endl;
        std::exit(-1);
    }
}
             
