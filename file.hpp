#ifndef SEPFILE_HPP
#define SEPFILE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

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
            char* getFileAddr();
            void setBlockSize(int val);
            void updateFile(vector<string> olddes, vector<string> newdes);
    };
}
#endif
