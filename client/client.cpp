#include "../gen-cpp/Serv.h"
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/concurrency/Thread.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TNonblockingServerSocket.h>
#include <thrift/transport/TNonblockingServerTransport.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using boost::shared_ptr;

int main(int argc, char **argv)
{
    stdcxx::shared_ptr<ServiceHandler> handler(new ServiceHandler());

    //调用server服务
    Student s;
    s.sno = 123;
    s.sname = "hao973";
    s.ssex = 1;
    s.sage = 30;

    ServClient client(protocol);
    printf("sno=%d sname=%s ssex=%d sage=%d\n", s.sno, s.sname.c_str(), s.ssex, s.sage);
    //put
    client.put(s);
    //icall scall
    std::string strname = "";
    client.scall(strname, s);
    printf("icall=%d, scall=%s\n", client.icall(s), strname.c_str());
    //stcall
    Student stu;
    client.stcall(stu, s);
    printf("student sno=%d sname=%s ssex=%d sage=%d\n", stu.sno, stu.sname.c_str(), stu.ssex, stu.sage);
    transport->close();

    return 0;
}