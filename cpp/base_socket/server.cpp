// server.cpp

#include <istream>
#include "base_socket.h"
using namespace std;

int main(int argc, char *argv[])
{
    int port = 8888;
    BaseSocket server;
    BaseSocket client;
    
    if (!server.Create() || !client.Create()) {
        cerr << "server of client create error." << endl;
        return -1;
    }
    
    if (!server.Bind(port)) {
        cerr << "server bind error." << endl;
         return -1;
    }
    
    if (!server.Listen()) {
        cerr << "server listen error." << endl;
         return -1;
    }
    
    cout <<  "listening on port " << port << endl;
    if (!server.Accept(client)) {
        cerr << "server accept error." << endl;
         return -1;
    }
    
    string host;
    int peer;
    
    if (!client.GetPeer(host, peer)) {
        cerr <<   "server get peer error." << endl;
        return -1;
    }
    
    cout << "accept from " << host << " : " << peer << endl;
    
    
}