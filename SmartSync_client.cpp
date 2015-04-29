#include <iostream>
#include "SmartSync.h"
#include <unistd.h>
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
#include <sys/stat.h>
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
        cout<<"You should use it like ./client ip port 1024 --filename x.\n1024 stands for 1024Byte blocksize.\n";
    }
    int opt;
    int optidx;
    std::string operation;
    std::string filename;
    std::string user;
    RFile rfile;
    RFileMetadata data;
    StatusReport statusReport;

    ChksumWorker chkworker;
    FileWorker fworker;
    
    boost::shared_ptr<TSocket> socket(new TSocket(argv[1], atoi(argv[2])));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport)); 
    boost::shared_ptr<TMemoryBuffer> buffer(new TMemoryBuffer());
    TJSONProtocol jsonprotocol(buffer);

    SmartSyncClient client(protocol);
    try {
        transport->open();
        static struct option long_options[] = {
            {"filename", required_argument, 0, 'f'},
            {0,0,0,0}
        };
        while ((opt = getopt_long(argc-3,argv + 3, "f", long_options, &optidx)) != -1) {
            //-1 means it reaches end
            switch (opt) {
                case 'f':
                    filename = optarg;
                    break;
                default:
                    std::cout<<"operation error"<<std::endl;
                    return -1;
            }
        }

        struct stat st;
        if (stat(filename.c_str(),&st) == -1) {
            return -1;
        }
        fworker.setPath(filename);
        fworker.setBlockSize(atoi(argv[3]));

        Timestamp lastmod = time(&st.st_atime);
        cout<<"Time of file will send to server is "<<lastmod<<endl;
        data.__set_updated(lastmod);
        //first check whether need update
        {
            try {
                cout<<filename<<endl;
                ifstream ifs(filename.c_str());
                if (ifs) {
                    ifs.seekg(0,ifs.end);
                    int len = ifs.tellg();

                    fworker.setFileSize(len);

                    ifs.seekg(0,ifs.beg);
                    char* buf = new char[len+1];
                    ifs.read(buf,len);
                    buf[len] = '\0';
                    data.__set_contenthash(md5(buf));
                    data.__set_contentLen(len);
                    delete [] buf;
                    ifs.close();
                } else {
                    cerr<<"open file error"<<endl;
                    return -1;
                }
                data.__set_filename(filename);
                client.checkFile(statusReport,data);                
            } catch (SystemException se) {
                //format se in json format
                std::cout<<ThriftJSONString(se)<<std::endl;
                return -1;
            }
            //format rfile in json format
            std::cout<<ThriftJSONString(rfile)<<std::endl;
        }
        
        cout<<"get status is "<<statusReport.status<<endl; 
        if (statusReport.status == 1) {
            cout<<"file doesn't exist on server and write to server"<<endl;
            //data.__set_filename(filename);
            data.__set_version(0);
            //data.__set_owner(user);
            //Timestamp lastmod = time(&st.st_atime);
            //data.__set_updated(lastmod);
            
            //read data from disk            
            std::ifstream ifs(filename.c_str(),std::ios::binary);
            if (ifs) {
                ifs.seekg(0,ifs.end);
                int len = ifs.tellg();
                ifs.seekg(0,ifs.beg);
                char *buf = new char[len+1];
                ifs.read(buf,len);
                buf[len] = '\0';
                ifs.close();
                data.__set_contentLen(len);
                rfile.__set_content(buf);
                rfile.__set_meta(data);
                delete []buf;
            } else {
                std::cerr<<"read file error!\n";
                return -1;
            }
            try {
                client.writeFile(statusReport,rfile);
            } catch (SystemException se) {
                //format se information in json format
                std::cout<<ThriftJSONString(se)<<std::endl;
                return -1;
            }
            //format status in json format
            std::cout<<ThriftJSONString(statusReport)<<std::endl;
        } else if (statusReport.status == 0) {
            //file is the same 
            std::cout<<"File is the same"<<std::endl;
        } else if (statusReport.status == 2) {
            //if client is older, it sends des to server
            vector<Filechk> vchk;
            vector<Filedes> des;
            //generate vector<Filechk> vchk
            {
                vector<string> file;
                ifstream ifs(fworker.getPath().c_str());
                double filesize = fworker.getFileSize();
                int blocksize = fworker.getBlockSize();
                cout<<"File size is "<<filesize<<", blocksize is "<<blocksize<<endl;
                cout<<"For loop excutes "<<(int)ceil(filesize/blocksize)<<endl;
                if (ifs) {
                    for (int i = 0; i < (int)ceil(filesize/blocksize); ++i) {
                        char *buf = new char[blocksize];
                        ifs.read(buf,blocksize);
                        if (ifs) {
                            file.push_back(buf);
                        } else {
                            buf[ifs.gcount()] = '\0';
                            file.push_back(buf);
                        }
                        delete [] buf;
                    }
                } else {
                    cerr<<"open file error"<<endl;
                    exit(-1);
                }
                ifs.close();
                //show files---------------------------
                for (int i = 0; i < (int)file.size(); ++i) {
                    cout<<file[i];
                }
                cout<<endl;
                //------------------------------------
                int l;
                int bsize = fworker.getBlockSize();
                int fsize = fworker.getFileSize();
                for (int i = 0; i < (int)file.size(); ++i) {
                    if (i == (int)file.size() - 1) {
                        l = fsize - (i+1)*bsize-1;
                    } else {
                        l = bsize-1;
                    }
                    checksum num1 = 1;
                    checksum num2 = 0;
                    checksum rchk = chkworker.rolling_chksum1(file[i],0,l,num1,num2);
                    checksum md5chk = chkworker.md5_chksum(file[i]);
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
                client.updateLocal(des,vchk);
            } catch (SystemException se) {
                std::cout<<ThriftJSONString(se)<<std::endl;
                return -1;
            }

            //generate new file based on des
            if (fworker.updateFile(des)) 
                cout<<"update finished\n";
            else
                cout<<"update failed\n";
        } else if (statusReport.status == 3) {
            //if client is newer, it receives the des from server
            vector<Filechk> fchks;
            client.request(fchks);
            vector<Filedes> vdes;
            //generate vector<Filedes> vdes
            //...........

            try {
                client.updateServer(statusReport,vdes);
            } catch (SystemException se) {
                std::cout<<ThriftJSONString(se)<<std::endl;
                return -1;
            }
            if (statusReport.status == 5) {
                std::cout<<"Success"<<std::endl;
            } else if (statusReport.status == 4) {
                std::cout<<"Fail"<<std::endl;
            } else {
                std::cout<<"undefined status"<<std::endl;
            }
        } else {
            std::cerr<<"operation argument error"<<std::endl;
            return 0;
        }

        transport->close();
    } catch (TException &tx) {
        std::cout<<"ERROR: "<<tx.what()<<std::endl;
        return -1;
    }

    return 0;
}
