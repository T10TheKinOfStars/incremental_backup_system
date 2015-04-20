#ifndef SEPFILE_HPP
#define SEPFILE_HPP
#include <iostream>
#include <vector>

namespace process{
    class FileWorker {
        private:
            std::vector<std::string> segs;
            std::string block;
            int blocksize;
            int segsize;
        public:
            FileWorker() :  blocksize(0),segsize(0) {};
            FileWorker(int bsize, int ssize) : blocksize(bsize),segsize(ssize) {};
            ~FileWorker();
            std::string getxFileSeg(int idx);
            int getSegSize();
            void processBlock();
            void setBlock(std::ifstream &ifs);
    };
}
#endif
