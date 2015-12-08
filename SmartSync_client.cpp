#include <iostream>
#include <sstream>
#include "common.h"
#include "SmartSync.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <getopt.h>
#include "checksum.hpp"
#include "package.hpp"
#include "file.hpp"
#include "search.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using boost::shared_ptr;

int main(int argc, char** argv) {
    if (argc < 5) {
        cout<<"You should use it like ./client ip port 1024 --dir x.\n1024 stands for 1024Byte blocksize.\n";
    }
    int opt;
    int optidx;
    string operation;
    string filepath;
    string filename;
    string dirname;
    unordered_map<string,int> status;
    int targetid = getpid();
    dprintf("This client target id is %d\n",targetid);

    DIR *dp;
    struct dirent *dirp;

    string user;
    RFile rfile;
    RFileMetadata data;
    StatusReport statusReport;

    ChksumWorker* chkworker = new ChksumWorker();
    FileWorker* fworker = new FileWorker();
    Package* pkgworker = new Package();
    SearchWorker* searchworker = new SearchWorker(chkworker,fworker,pkgworker);
    
    boost::shared_ptr<TSocket> socket(new TSocket(argv[1], atoi(argv[2])));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport)); 
    boost::shared_ptr<TMemoryBuffer> buffer(new TMemoryBuffer());
    TJSONProtocol jsonprotocol(buffer);

    SmartSyncClient client(protocol);
    try {
        transport->open();
        static struct option long_options[] = {
            {"dir", required_argument, 0, 'd'},
            {0,0,0,0}
        };
        while ((opt = getopt_long(argc-3,argv + 3, "d", long_options, &optidx)) != -1) {
            //-1 means it reaches end
            switch (opt) {
                case 'd':
                    dirname = optarg;
                    break;
                default:
                    dprintf("operation error\n");
                    return -1;
            }
        }
        dprintf("dir is %s\n",dirname.c_str());
        if ((dp = opendir(dirname.c_str())) == NULL) {
            std::cout<< "can't open "<<dirname<<std::endl;
            exit(1);
        }
        vector<string> files;
        while ((dirp = readdir(dp)) != NULL) {
            if (dirp->d_type == 8) {
                files.push_back(dirp->d_name);
                status[dirp->d_name] = 0;
            }
        }
        dprintf("There are %lu files in directory\n",files.size());
        int idx = 0; 
        data.__set_target(targetid);
        while (true) {
            filepath = dirname + files[idx];
            filename = files[idx];
            ++idx;
            //when go through all the files in directory
            //sleep 5 seconds and reset idx to 0
            if (idx == (int)files.size()) {
                dprintf("reset idx and sleep for several seconds\n");
                sleep(5);
                idx = 0;
            }
            dprintf("Processing %s .......\n",filename.c_str());
            struct stat st;
            time_t t;
            struct tm lt;
            char timebuf[80];
            if (stat(filepath.c_str(),&st) == -1) {
                dprintf("stat error\n");
                return -1;
            }
            fworker->setPath(filepath);
            fworker->setBlockSize(atoi(argv[3]));
            //Timestamp is string type
            t = st.st_mtime;
            localtime_r(&t,&lt);
            strftime(timebuf,80,"%Y%m%d%H%M%S",&lt);

            data.__set_updated(timebuf);
            //first check whether need update
            {
                try {
                    ifstream ifs(filepath.c_str());
                    if (ifs) {
                        ifs.seekg(0,ifs.end);
                        int len = ifs.tellg();

                        fworker->setFileSize(len);

                        ifs.seekg(0,ifs.beg);
                        char* buf = new char[len+1];
                        ifs.read(buf,len);
                        buf[ifs.gcount()] = '\0';
                        data.__set_contenthash(md5(buf));
                        data.__set_contentLen(ifs.gcount());
                        delete [] buf;
                        ifs.close();
                    } else {
                        cerr<<"open file error"<<endl;
                        return -1;
                    }
                    data.__set_filename(filename);
                    dprintf("send checkfile request\n");
                    client.checkFile(statusReport,data);                
                } catch (SystemException se) {
                    //format se in json format
                    std::cout<<ThriftJSONString(se)<<std::endl;
                    return -1;
                }
            }
            
            if (statusReport.status != 0) {        
                //file is not the same, need update
                if (statusReport.status == 1) {
                    dprintf("[%s] file doesn't exist on server and write to server\n",filename.c_str());
                    data.__set_version(0);
                    //read data from disk            
                    ifstream ifs(filepath.c_str(),std::ios::binary);
                    if (ifs) {
                        ifs.seekg(0,ifs.end);
                        int len = ifs.tellg();
                        ifs.seekg(0,ifs.beg);
                        char *buf = new char[len+1];
                        ifs.read(buf,len);
                        buf[ifs.gcount()] = '\0';
                        ifs.close();
                        data.__set_contentLen(ifs.gcount());
                        data.__set_contenthash(md5(buf));
                        rfile.__set_content(buf);
                        rfile.__set_meta(data);
                        delete []buf;
                    } else {
                        cerr<<"read file error!\n";
                        return -1;
                    }
                    try {
                        dprintf("File %s doesnt exist on server. The data transport between the client and the server is %lu Byte\n", fworker->getFilename().c_str(), sizeof(statusReport) + getSizeOfObject(rfile));
                        client.writeFile2Server(statusReport,rfile);
                    } catch (SystemException se) {
                        //format se information in json format
                        cout<<ThriftJSONString(se)<<endl;
                        return -1;
                    }
                    //format status in json format
                    dprintf("write 2 server is %d\n",statusReport.status);
                } else if (statusReport.status == 2) {
                    //if client is older, it sends des to server
                    dprintf("file on client is older\n");
                    vector<Filechk> vchk;
                    vector<Filedes> des;
                    //generate vector<Filechk> vchk
                    {
                        vector<string> file;
                        ifstream ifs(fworker->getPath().c_str());
                        double filesize = fworker->getFileSize();
                        int blocksize = fworker->getBlockSize();
                        if (ifs) {
                            for (int i = 0; i < (int)ceil(filesize/blocksize); ++i) {
                                char *buf = new char[blocksize+1];
                                ifs.read(buf,blocksize);
                                buf[ifs.gcount()] = '\0';
                                file.push_back(buf);
                                delete [] buf;
                            }
                        } else {
                            cout<<"open file error"<<endl;
                            exit(-1);
                        }
                        ifs.close();
                        int l;
                        int bsize = fworker->getBlockSize();
                        int fsize = fworker->getFileSize();
                        for (int i = 0; i < (int)file.size(); ++i) {
                            if (i == (int)file.size() - 1) {
                                l = fsize - (i+1)*bsize-1;
                            } else {
                                l = bsize-1;
                            }
                            checksum num1 = 1;
                            checksum num2 = 0;
                            checksum rchk = chkworker->rolling_chksum1(file[i],0,l,num1,num2);
                            string md5chk = chkworker->md5_chksum(file[i]);
                            Filechk temp;
                            temp.__set_rollchk(rchk);
                            temp.__set_md5chk(md5chk);
                            temp.__set_block(i);
                            temp.__set_num1(num1);
                            temp.__set_num2(num2);

                            vchk.push_back(temp);
                        }
                    }
                    try {
                        dprintf("The file %s on client is older. The data transport between clients and servers are %lu Byte\n", fworker->getFilename().c_str(), getSizeOfObject(des) + getSizeOfObject(vchk));
                        client.updateLocal(des,vchk,targetid);
                    } catch (SystemException se) {
                        std::cout<<ThriftJSONString(se)<<std::endl;
                        return -1;
                    }

                    //generate new file based on des
                    if (fworker->updateFile(des)) 
                        dprintf("update finished\n");
                    else
                        dprintf("update failed\n");
                } else if (statusReport.status == 3) {
                    //if client is newer, it receives the des from server
                    dprintf("File on client is newer\n");
                    vector<Filechk> fchks;
                    client.request(fchks,targetid);
                    if (fworker->getFileSize() / 1000000 > fworker->getBlockSize() * (int)fchks.size()) {
                        //directly write file to server
                        t = st.st_mtime;
                        localtime_r(&t,&lt);
                        strftime(timebuf,80,"%Y%m%d%H%M%S",&lt);
                        string content = fworker->getWholeFile();
                        data.__set_contentLen(content.size());
                        data.__set_contenthash(md5(content));
                        rfile.__set_content(content);
                        rfile.__set_meta(data);
                        data.__set_updated(timebuf);
                        dprintf("The file %s on client is newer and need whole update. The data transport between the client and the server is %lu Byte\n", fworker->getFilename().c_str(),sizeof(statusReport)+getSizeOfObject(rfile));

                        client.writeFile2Server(statusReport,rfile); 
                    } else {
                        vector<Filedes> vdes;
                        //generate vector<Filedes> vdes
                        searchworker->init(fchks);
                        searchworker->find();
                        vdes = pkgworker->getFiledes();
                        try {
                            dprintf("The file %s on client is newer and dont need updata the whole file. The data transport between the client and the server is %lu\n", fworker->getFilename().c_str(), sizeof(statusReport) + getSizeOfObject(vdes) + sizeof(targetid));
                            client.updateServer(statusReport,vdes,targetid);
                        } catch (SystemException se) {
                            cout<<ThriftJSONString(se)<<endl;
                            return -1;
                        }
                        if (statusReport.status == 5) {
                            cout<<"Success"<<endl;
                        } else if (statusReport.status == 4) {
                            cout<<"Fail"<<endl;
                        } else {
                            cout<<"undefined status"<<endl;
                        }
                    }
                    status[filename] = 0;
                } else if (statusReport.status == 6) {
                    dprintf("server modifying\n");
                } else {
                    dprintf("operation argument error\n");
                    return 0;
                }
            }
        }
        transport->close();
        } catch (TException &tx) {
            cout<<"ERROR: "<<tx.what()<<endl;
            transport->close();
            return -1;
        }

    closedir(dp);
    return 0;
}
