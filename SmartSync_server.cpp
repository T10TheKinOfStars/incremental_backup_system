// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "SmartSync.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class SmartSyncHandler : virtual public SmartSyncIf {
 public:
  SmartSyncHandler() {
    // Your initialization goes here
  }

  void writeFile(StatusReport& _return, const RFile& rfile) {
    // Your implementation goes here
    printf("writeFile\n");
  }

  void checkFile(RFileMetadata& _return, const RFileMetadata& meta) {
    // Your implementation goes here
    printf("checkFile\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<SmartSyncHandler> handler(new SmartSyncHandler());
  shared_ptr<TProcessor> processor(new SmartSyncProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

