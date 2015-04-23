#include "file.hpp"

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

void FileWorker::updateFile(vector<string> olddes, vector<string> newdes) {
    //use to store the content of each block
    vector<string> file(olddes.size());
    ifstream ifs(path.c_str());
    if (ifs) {
        for (int i = 0; i < olddes.size(); ++i) {
            char *buf = new char[blocksize];
            ifs.read(buf,blocksize);
            file[i] = buf;
            delete [] buf;
        }
        ifs.close();
    } else {
        cerr<<"open file error"<<endl;
        exit(-1);
    }
}
