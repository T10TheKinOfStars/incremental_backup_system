#ifndef SEPFILE_HPP
#define SEPFILE_HPP
#include <iostream>
#include <vector>

using namespace std;

namespace process{
    class FileWorker {
        private:
            char* addr;
            //std::vector<std::string> segs;
            //std::string block;
            string path;
            int filesize;
            int blocksize;
            int segsize;
        public:
            FileWorker() :  blocksize(0),segsize(0),addr(nullptr) {};
            FileWorker(int bsize, int ssize, char* add, string fpath) : blocksize(bsize),segsize(ssize),addr(add), path(fpath) {};
            ~FileWorker();
            //std::string getxFileSeg(int idx);
            int getSegSize();
            int getBlockSize();
            int getFileSize();
            string getBlock(int pos);
            string getSeg(int pos);
            char getxChar(int pos);
            char* getFileAddr();
            void setBlockSize(int val);
            void setSegSize(int val);
    };
}
#endif
