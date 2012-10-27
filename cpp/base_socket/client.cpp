// client.cpp

#include <istream>
#include "base_socket.h"
#include "test.h"

using namespace std;


int main(int argc, char *argv[])
{
    int port = 8888;
    string ip = "127.0.0.1";
    BaseSocket toserver;

#ifdef TEST_TCP
    if (!toserver.Create()) {
        cerr << "client create error." << endl;
        return -1;
    }
    
    string host;
    int peer;
    
    if (!toserver.Connect(ip, port)) {
        cerr << "connect to server error." << endl;
        return -1;
    }
    if (!toserver.GetPeer(host, peer)) {
        cerr <<   "server get peer error." << endl;
        //return -1;
    }
    
    cout << "connected to " << host << " : " << peer << endl;
    
    cout << toserver.Send("this is the client sending msg...") << endl;
    cout << toserver.Recv() << endl;
    
    return 0;  
#endif
    
#ifdef TEST_UDP
     if (!toserver.Create(true)) {
        cerr << "client create error." << endl;
        return -1;
    }
   
    toserver.SendTo("udp test from client...", ip, port);
    cout << toserver.RecvFrom(ip, port) << endl;
    return 0;  
#endif
}