#include "file.hpp"

using namespace std;

std::mutex mtx;
std::unordered_map<std::string,int> filestatus;

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

vector<Filedes> FileWorker::getFiledes() {
    vector<Filedes> retVal;
    ifstream ifs(path.c_str());
    if (ifs) {
        int count = 0;
        while (count < filesize) {
            char *buf = new char[blocksize+1];
            ifs.read(buf,blocksize);
            buf[ifs.gcount()] = '\0';
            Filedes temp;
            temp.__set_flag(0);
            temp.__set_content(buf);
            temp.__set_block(-1);
            retVal.push_back(temp);
            count += blocksize;
            delete []buf;
        }
        ifs.close();
    }

    return retVal;
}

string FileWorker::getWholeFile() {
    string ret = "";
    ifstream ifs(path.c_str(),std::ios::binary);
    if (ifs) {
        ifs.seekg(0,ifs.end);
        int len = ifs.tellg();
        ifs.seekg(0,ifs.beg);
        char *buf = new char[len+1];
        ifs.read(buf,len);
        buf[ifs.gcount()] = '\0';
        ifs.close();
        delete []buf;

        ret = buf;
    }

    return ret;
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
    buf[ifs.gcount()] = '\0';
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
    string filename = path.substr(path.find_last_of('/'));
    dprintf("update filename is %s\n",filename.c_str());
    dprintf("file path is %s\n",path.c_str());
    try {
    ifstream ifs(path.c_str());
    if (ifs) {
        for (int i = 0; i < (int)ceil((double)filesize/blocksize); ++i) {
            char *buf = new char[blocksize+1];
            ifs.read(buf,blocksize);
            buf[ifs.gcount()] = '\0';
            file.push_back(buf);
            if (buf)
                delete []buf;
        }
        ifs.close();
    } else {
        cerr<<"open file error"<<endl;
        return false;
    }
    } catch (SystemException se) {
        dprintf("init vector of file error happens in updateFile fun\n");
        exit(-1);
    }
    //#ifdef DEBUG
    /*
    cout<<"show vector of file:\n";
    for (int i = 0; i < (int)file.size(); ++i) {
        cout<<"Block "<<i<<" content is: "<<file[i]<<endl;
    }
    cout<<"end show file---------------------------\n";

    cout<<"show newdes:\n";
    for (int i = 0; i < (int)newdes.size(); ++i) {
        cout<<"Flag:"<<newdes[i].flag<<" content:"<<newdes[i].content<<" block:"<<newdes[i].block<<endl;
    }
    cout<<"end show newdes--------------------------\n";
    //#endif
    */
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
        mtx.lock();
        filestatus[filename] = 0;
        mtx.unlock();
        dprintf("After update, file %s's file status is %d\n",filename.c_str(),filestatus[filename]);
        ofs.close();
    } else {
        cerr<<"open file error"<<endl;
        return false;
    }

    return true;
}

void FileWorker::initFolder() {
    string cmd = "rm -rf files";    
    if (system(cmd.c_str()) == -1) {
        SystemException se;
        se.__set_message("remove folder failed");
        throw se;
    }
    cmd = "mkdir files";
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
            //means write complete
            rdata.__set_version(0);
            rdata.__set_contenthash(md5(rfile.content));
            struct stat st;
            time_t t;
            char timebuf[80];
            struct tm lt;
            if (stat(path.c_str(),&st) != -1) {
                t = st.st_mtime;
                localtime_r(&t,&lt);
                strftime(timebuf,80,"%Y%m%d%H%M%S",&lt);
                dprintf("time is %s\n",timebuf);
                rdata.__set_updated(timebuf);
            }
            filemap[filename] = rdata;
        } else {
            return -1;
        }
    }
    mtx.lock();
    filestatus[filename] = 0;
    mtx.unlock();
    dprintf("After writefile, file %s's file status is %d\n",filename.c_str(),filestatus[filename]);

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
