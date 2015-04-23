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

void FileWorker::setBlockSize(int val) {
    blocksize = val;
}

void FileWorker::updateFile(vector<Filedes> newdes) {
    //use to store the content of each block
    vector<string> file;
    ifstream ifs(path.c_str());
    if (ifs) {
        for (int i = 0; i < (int)ceil(filesize/blocksize); ++i) {
            char *buf = new char[blocksize];
            ifs.read(buf,blocksize);
            file.push_back(buf);
            delete [] buf;
        }
        //ifs.close();
    } else {
        cerr<<"open file error"<<endl;
        exit(-1);
    }

    ifs.seekg(0,ifs.beg);
    for (int i = 0; i < newdes.size(); ++i) {
        if (newdes[i].flag == 0) {
            //0 means it has content
            ifs<<newdes[i].content;
        } else {
            ifs<<file[newdes[i].block];
        }
    }

    ifs.close();
}
