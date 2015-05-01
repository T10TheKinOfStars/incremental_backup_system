#include "file.hpp"

using namespace std;

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

void FileWorker::setFileSize(int val) {
    filesize = val;
}

int FileWorker::getFileSize() {
    return filesize;
}
string FileWorker::getBlock(int pos) {
    int len = (filesize - pos) > blocksize ? blocksize : (filesize - pos);
    ifstream ifs(path.c_str());
    ifs.seekg(pos,ifs.beg);
    char* buf = new char[len+1];
    ifs.read(buf,len);
    buf[len] = '\0';
    string retVal = buf;
    ifs.close();
    return retVal;
}

void FileWorker::setPath(const string &str) {
    path = str;
}

string FileWorker::getPath() {
    return path;
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

bool FileWorker::updateFile(vector<Filedes> newdes) {
    //use to store the content of each block in old file
    vector<string> file;
    ifstream ifs(path.c_str());
    if (ifs) {
        for (int i = 0; i < (int)ceil((double)filesize/blocksize); ++i) {
            char *buf = new char[blocksize];
            ifs.read(buf,blocksize);
            if (ifs) {
                file.push_back(buf);
            } else {
                buf[ifs.gcount()] = '\0';
                file.push_back(buf);
            }
            delete [] buf;
            ifs.close();
        }
    } else {
        cerr<<"open file error"<<endl;
        return false;
    }
    //generate new file 
    ofstream ofs(path.c_str());
    if (ofs) {
        for (int i = 0; i < (int)newdes.size(); ++i) {
            if (newdes[i].flag == 0) {
                //0 means it has content
                ofs<<newdes[i].content;
            } else {
                ofs<<file[newdes[i].block];
            }
        }
        ofs.close();
    } else {
        cerr<<"open file error"<<endl;
        return false;
    }

    return true;
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
    
    if (filemap.find(filename) == filemap.end()) {
        //std::cout<<"this file not exists, we need create a new one"<<std::endl;
        if (write2Disk(path,rfile.content) != -1) {
            rdata.__set_version(0);
            rdata.__set_contenthash(md5(rfile.content));
            struct stat st;
            if (stat(path.c_str(),&st) != -1) {
                Timestamp temp = time(&st.st_mtime);
                rdata.__set_updated(temp);
            }
            filemap[filename] = rdata;
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

NameDataMap FileWorker::getMap() {
    return filemap;
}
