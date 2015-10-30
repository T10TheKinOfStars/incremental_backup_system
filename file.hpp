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
#include "common.h"
#include "md5.h"
#include "file.hpp"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mutex>

using namespace std;

extern std::mutex mtx;
extern std::unordered_map<std::string,int> filestatus;

class FileWorker {
    public:
        FileWorker() :  blocksize(0),filesize(0),path("") {};
        ~FileWorker();
        void setPath(const string &str);
        string getPath();
        vector<Filedes> getFiledes();
        string getWholeFile();
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
