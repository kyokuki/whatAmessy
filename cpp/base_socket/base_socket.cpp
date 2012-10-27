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
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock != -1) {
        //m_connected = true;
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

bool BaseSocket::Listen(unsigned int timeout)
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
    
    
}

