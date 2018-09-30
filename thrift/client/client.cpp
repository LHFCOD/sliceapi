

// #include <thrift/stdcxx.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <iostream>
#include "../gen-cpp/SliceEntry.h"

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using namespace Slice;

int main()
{
    stdcxx::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    stdcxx::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    stdcxx::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    SliceEntryClient client(protocol);

    try
    {
        transport->open();
        Pointer a = client.RequstMDSFile("/home/mi/project/slicePro/sliceapi/data/1.mds");
        // int a = client.add(3, 4);
        cout << a;
        transport->close();
    }
    catch (TException &tx)
    {
        cout << "ERROR: " << tx.what() << endl;
    }
}
