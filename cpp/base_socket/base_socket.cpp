// base_socket.cpp

#include "base_socket.h"
#include <string.h>
#include <stdio.h>

using std::cerr;
using std::endl;

BaseSocket::BaseSocket()
{
    m_connected = false;
    m_udp = false;
    m_port = -1;
    m_sock = -1;
}

BaseSocket::~BaseSocket()
{
    Close();
}

void BaseSocket::Close()
{
    if (m_sock != -1) {
        shutdown(m_sock, SHUT_RDWR);
        close(m_sock);
    }
}

SOCKET BaseSocket::GetHandle()
{
    return m_sock;
}

bool BaseSocket::isConnected()
{
     return (m_sock!=-1)&&m_connected;
}

bool BaseSocket::Create(bool udp)
{
    m_udp = udp;
    if (m_udp == false) {
        m_sock = socket(AF_INET, SOCK_STREAM, 0);
    } else {
        m_sock = socket(AF_INET,SOCK_DGRAM, 0);
    }
    
    return (m_sock != -1);
}

bool BaseSocket::Bind(unsigned int port)
{
    if (port == -1) {
        return false;
    }
    if (m_sock < 0) {
        cerr << "socket not created ." << endl;
        return false;
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);
    
    if (bind(m_sock, (struct sockaddr *)&sin,sizeof(sin)) < 0) {
        return false;
    }
    //m_connected = true;
    return true;
}

bool BaseSocket::Listen(unsigned int timeout) const
{
    return (listen(m_sock, timeout) >= 0);
    
}

bool BaseSocket::GetPeer(string & host, int & port)
{
    struct sockaddr_in sin;
    socklen_t sinlen = sizeof(sin);
    memset(&sin, 0, sizeof(sin));
    if (getpeername(m_sock, (struct sockaddr*)&sin, &sinlen) != 0) {
        return false;
    }

    char strtmp[64];
    //sprintf(strtmp,"%u.%u.%u.%u",sin.sin_addr.s_addr&0xFF,(sin.sin_addr.s_addr>>8)&0xFF,(sin.sin_addr.s_addr>>16)&0xFF,(sin.sin_addr.s_addr>>24)&0xFF);
    sprintf(strtmp, "%s", inet_ntoa(sin.sin_addr));
    host = strtmp;
    port =  ntohs(sin.sin_port);
    
    return true;
}

bool BaseSocket::Accept(BaseSocket& client)
{
    if (m_sock < 0) {
        return false;
    }
    client.m_sock = accept(m_sock, 0 ,0);
    if (client.m_sock < 0) {
        return false;
    }
    client.m_connected = true;
    m_connected = true;
    return true;
}

bool BaseSocket::Connect(const string& host, unsigned int port)
{
    if (m_sock < 0) {
        return true;
    }
    m_host = host;
    m_port = port;
    
    struct sockaddr_in sin;
    memset(&sin, 0 ,sizeof(sin));
    sin.sin_family = AF_INET;
    inet_pton(AF_INET, m_host.c_str(), &sin.sin_addr);
    sin.sin_port = htons(m_port);
    
    if (connect(m_sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        return false;
    }
    
    return true;
    
}

long int BaseSocket::Send(const char* buf, int len,int flags)
{
    return sendto(m_sock, buf, len, flags, NULL, 0);    //is equivalent to : send(m_sock, buf, len, flags);
}

long BaseSocket::Send(const string& msg, int flags)
{
    return Send(msg.c_str(), msg.length()+1, flags);
}

long BaseSocket::Recv(char* buf, int len, int flags)
{
    return recv(m_sock, buf, len, flags);
}

string BaseSocket::Recv(int flags)
{
    char *buf = new char [BUF_SIZE];
    int len =  Recv(buf, BUF_SIZE, flags);
    string str = buf;
    delete [] buf;
    return (len >= 0 ? str : "");
}

long BaseSocket::SendTo(const char* buf, int len,  const string& host, int port, int flags)
{
    struct sockaddr_in sin;
    socklen_t addrlen = sizeof(sin);
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &sin.sin_addr);
    
    return sendto(m_sock, buf, len, flags, (struct sockaddr*)&sin, addrlen);
}

long BaseSocket::SendTo(const string& msg, const string& host, int port, int flags)
{
    return SendTo(msg.c_str(), msg.length() + 1, host, port, flags);
}


long BaseSocket::RecvFrom(char* buf, int len, const string& host, int port, int flags)
{
    struct sockaddr_in sin;
    socklen_t addrlen = sizeof(sin);
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &sin.sin_addr);
    
    return recvfrom(m_sock, buf, len, flags, (struct sockaddr*)&sin, &addrlen);
}

string BaseSocket::RecvFrom(const string& host, int port, int flags)
{
    char *buf = new char [BUF_SIZE];
    int len =  RecvFrom(buf, BUF_SIZE, host, port, flags);
    string str = buf;
    delete [] buf;
    return (len >= 0 ? str : "");
}



