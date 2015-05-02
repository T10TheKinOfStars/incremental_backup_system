#ifndef FILE_HPP
#define FILE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "smartSync_types.h"
#include "mytypes.h"
#include "md5.h"
#include "file.hpp"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

class FileWorker {
    public:
        FileWorker() :  blocksize(0),filesize(0),path("") {};
        //FileWorker(int bsize, int fsize, string fpath) : blocksize(bsize),filesize(fsize), path(fpath) {};
        ~FileWorker();
        void setPath(const string &str);
        string getPath();
        void setFileSize(int val);
        int getFileSize();
        void setBlockSize(int val);
        int getBlockSize();
        FileWorker(const FileWorker &worker);
        string getBlock(int pos);
        char getxChar(int pos);
        bool updateFile(vector<Filedes> newdes);
        void initFolder();
        int writefile(const RFile &rfile);
        NameDataMap getMap();
    private:
        NameDataMap filemap;
        int blocksize;
        int filesize;
        string path;
        int write2Disk(string path, const string &content);
};
#endif
