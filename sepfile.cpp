#include "sepfile.hpp"
#include <fstream>
#include <cstdlib>

using namespace file;

FileWorker::~FileWorker() {
    //path = "";
    block = "";
    segs.clear();
    blocksize = 0;
    segsize = 0;
}

std::string FileWorker::getxFileSeg(int idx) {
    return segs[idx];
}

int FileWorker::getSegSize() {
    return segs.size();
}

void FileWorker::processBlock() {        
    int idx = 0;
    while (idx < block.size()) {
        segs.push_back(block.substr(idx,segsize));
        idx += segsize;
    }
}

void FileWorker::setBlock(std::ifstream &ifs) {
    //std::ifstream ifs(path.c_str(), std::ifstream::binary);
    //ifs.seekg(pos,ios::beg); 
    if (ifs) {
        char *s = new char[blocksize+1];
        ifs.read(s,blocksize);
        s[blocksize] = '\0';
        block = s;
        delete s;
    } else {
        std::cerr<<"ifs error"<<std::endl;
        std::exit(-1);
    }
}
