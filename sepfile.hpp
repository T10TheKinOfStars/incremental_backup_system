#ifndef SEPFILE_HPP
#define SEPFILE_HPP
#include <iostream>
#include <vector>

namespace file{
    class FileWorker {
        private:
            std::string path;
            std::vector<std::string> blocks;
            int blocksize;
        public:
            FileWorker() : path(""), blocksize(0) {};
            FileWorker(std::string val, int size) : path(val), blocksize(size) {};
            ~FileWorker();
            std::string getxFileBlock(int idx);
            int getBlockSize();
            void processFile();
    };
}
#endif
