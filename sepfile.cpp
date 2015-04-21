#include "sepfile.hpp"
#include <fstream>
#include <cstdlib>

using namespace file;

FileWorker::~FileWorker() {
    path = "";
    //segs.clear();
    blocksize = 0;
    segsize = 0;
    addr = nullptr;
}

int FileWorker::getBlockSize() {
    return blocksize;
}

int FileWorker::getSegSize() {
    return segsize;
}

int FileWorker::getFileSize() {
    return filesize;
}
string FileWorker::getBlock(int pos) {
    int len = (filesize - pos) > blocksize ? blocksize : (filesize - pos);
    ifstream ifs(path.c_str());
    ifs.seekg(pos,ifs.beg);
    char* buf = new char[len];
    ifs.read(buf,len);
    string retVal = buf;
    ifs.close();
    return retVal;
}

string FileWorker::getSeg(int pos) {
    int len = (filesize - pos) > segsize ? segsize : (filesize - pos);
    ifstream ifs(path.c_str());
    ifs.seekg(pos,ifs.beg);
    char* buf = new char[len];
    ifs.read(buf,len);
    string retVal = buf;
    ifs.close();
    return retVal;
}

char FileWorker::getxChar(int pos) {
    ifstream ifs(path.c_str());
    ifs.seekg(pos-1,ifs.beg);
    char c = ifs.peek();
    ifs.close();
    return c;
}

char* FileWorker::getFileAddr() {
    return addr;
}

void FileWorker::setBlockSize(int val) {
    blocksize = val;
}

void FileWorker::setSegSize(int val) {
    segsize = val;
}
/*
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
*/
