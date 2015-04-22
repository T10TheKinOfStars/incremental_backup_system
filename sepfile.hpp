#ifndef SEPFILE_HPP
#define SEPFILE_HPP
#include <iostream>
#include <vector>

using namespace std;

namespace process{
    class FileWorker {
        private:
            //char* addr;
            //std::vector<std::string> segs;
            //std::string block;
            string path;
            int filesize;
            int blocksize;
        public:
            FileWorker() :  blocksize(0),addr(nullptr) {};
            FileWorker(int bsize, char* add, string fpath) : blocksize(bsize),addr(add), path(fpath) {};
            ~FileWorker();
            FileWorker(const FileWorker &worker);
            //std::string getxFileSeg(int idx);
            int getBlockSize();
            int getFileSize();
            string getBlock(int pos);
            char getxChar(int pos);
            char* getFileAddr();
            void setBlockSize(int val);
    };
}
#endif
