#ifndef FILE_HPP
#define FILE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include "smartSync_types.h"
#include "types.h"

using namespace std;

namespace process{
    class FileWorker {
        private:
            string path;
            int filesize;
            int blocksize;
        public:
            FileWorker() :  blocksize(0),filesize(0),path("") {};
            FileWorker(int bsize, int fsize, string fpath) : blocksize(bsize),filesize(fsize), path(fpath) {};
            ~FileWorker();
            FileWorker(const FileWorker &worker);
            int getBlockSize();
            int getFileSize();
            string getBlock(int pos);
            char getxChar(int pos);
            void setBlockSize(int val);
            void updateFile(vector<Filedes> newdes);
    };
}
#endif
