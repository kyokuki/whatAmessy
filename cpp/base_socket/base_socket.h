// base_socket.h

#ifndef BASE_SOCKET_H
#define BASE_SOCKET_H

#include <iostream>

#include <string>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>     /* for the socket's  */
#include <netinet/in.h>     /* for struct sockaddr_in */
#include <arpa/inet.h>      /* 处理字节序和网络字节序 */

typedef int SOCKET;
using std::string;

class BaseSocket
{
private:
    SOCKET m_sock;    // it's a fd in linux
    unsigned int m_port;
    string m_host;
    bool m_connected;
    bool m_udp;
    
public:
    static const unsigned int TIMEOUT = 1024;
    
    BaseSocket();
    virtual ~BaseSocket();
    bool Create(bool udp=false);
    bool Bind(unsigned int port);
    bool Listen(unsigned int timeout = TIMEOUT);
    bool GetPeer(string & host, int & port);
    bool Accept(BaseSocket & client);
    void Close();
    bool isConnected();
    bool Connect(const string & host, unsigned int port);
    SOCKET GetHandle();
    
};

#endif