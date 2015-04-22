#include "sepfile.hpp"

using namespace process;

FileWorker::~FileWorker() {
    path = "";
    blocksize = 0;
    filesize = 0;
}

FileWorker::FileWorker(const FileWorker &worker) {
    path = worker.path;
    filesize = worker.filesize;
    blocksize = worker.blocksize;
}

int FileWorker::getBlockSize() {
    return blocksize;
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

