#include <iostream>
#include "SmartSync.h"
#include <unistd.h>
#include <getopt.h>
#include "checksum.hpp"
#include "package.hpp"
#include "search.h"
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
    int opt;
    int optidx;
    std::string operation;
    std::string filename;
    std::string user;
    RFile rfile;
    RFileMetadata data;
    StatusReport statusReport;
    ChksumWorker chkworker;
    
    boost::shared_ptr<TSocket> socket(new TSocket(argv[1], atoi(argv[2])));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport)); 
    boost::shared_ptr<TMemoryBuffer> buffer(new TMemoryBuffer());
    TJSONProtocol jsonprotocol(buffer);

    FileStoreClient client(protocol);
    try {
        transport->open();

        static struct option long_options[] = {
            {"filename", required_argument, 0, 'f'},
            {0,0,0,0}
        };
        while ((opt = getopt_long(argc-2,argv + 2, "f", long_options, &optidx)) != -1) {
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
        bool needUpdate = false;

        //first check whether need update
        {
            try {
                struct stat st;
                if (stat(filename.c_str(),&st) == -1) {
                    cerr<"stat error"<<endl;
                    return -1;
                }
                ifstream ifs(filename.c_str());
                if (ifs) {
                    char* buf = new char[INT_MAX];
                    ifs.seekg(0,ifs.end);
                    int len = ifs.tellg();
                    ifs.seekg(0,ifs.beg);
                    ifs.read(buf,len);
                    data.__set_contenthash(md5(buf));
                    delete [] buf;
                    ifs.close();
                } else {
                    cerr<<"open file error"<<endl;
                    return -1;
                }
                Timestamp lastmod = time(&st.st_mtime);
                data.__set_filename(filename);
                data.__set_modified(lastmod);
             
                statusReport = client.checkFile(data);                
            } catch (SystemException se) {
                //format se in json format
                std::cout<<ThriftJSONString(se)<<std::endl;
                return -1;
            }
            //format rfile in json format
            std::cout<<ThriftJSONString(rfile)<<std::endl;
        }         
        if (statusReport.status == 1) {
            //file doesn't exist on server
            data.__set_filename(filename);
            data.__set_version(0);
            data.__set_owner(user);
            
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
                data.__set_contentLength(len);
                rfile.__set_content(buf);
                rfile.__set_meta(data);
                delete []buf;
            } else {
                std::cerr<<"read file error!\n";
                return -1;
            }
            try {
                client.writeFile(status,rfile);
            } catch (SystemException se) {
                //format se information in json format
                std::cout<<ThriftJSONString(se)<<std::endl;
                return -1;
            }
            //format status in json format
            std::cout<<ThriftJSONString(status)<<std::endl;
        } else if (statusReport.status == 0) {
            //file is the same 
        } else if (statusReport.status == 2) {
            //if client is older, it sends des to server
            rfile = client.update(rfile);
            //...........
        } else if (statusReport.status == 3) {
            //if client is newer, it receives the des from server
            RFile newrfile = client.request();
            newrfile = client.update(newrfile);
            //..........
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
