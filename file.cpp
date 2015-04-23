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

void FileWorker::initFolder() {
    std::string cmd = "rm -rf files | mkdir files";    
    if (system(cmd.c_str()) == -1) {
        SystemException se;
        se.__set_message("create folder failed");
        throw se;
    }
}

int FileWorker::write2Disk(std::string path, const std::string &content) {
    std::ofstream ofs(path.c_str(), std::ios::binary);

    if (ofs) {
        ofs<<content;
        ofs.close();
    } else {
        return -1;
    }

    return 0;
}

int FileWorker::writefile(const RFile &_rfile) {
    RFile rfile = _rfile;
    RFileMetadata rdata = rfile.meta;    
    std::string filename = rdata.filename;
    std::string path = "./files/" + filename;
    SystemException exception;
    
    if (filemap.find(filename) == files.end()) {
        //std::cout<<"this file not exists, we need create a new one"<<std::endl;
        if (write2Disk(path,rfile.content) != -1) {
            rdata.__set_version(0);
            rdata.__set_contentHash(md5(rfile.content));
            rdata.__set_created((Timestamp)time(NULL) * 1000);    //need to change
            rdata.__set_updated((Timestamp)time(NULL) * 1000);    //need to change                
        } else {
            return -1;
        }
    }
    return 0;
        /* when do update, can review this
         else {
            std::cout<<"this file exists, we need do update"<<std::endl;
            if (write2Disk(path,rfile.content) != -1) {                
                ++files[filename].version;
                files[filename].__set_contentLength(rfile.content.size());
                files[filename].__set_contentHash(md5(rfile.content));
                files[filename].__set_updated((Timestamp)time(NULL) * 1000);    //need to change
            } else {
                return -1;
            }
        }
    */
}
