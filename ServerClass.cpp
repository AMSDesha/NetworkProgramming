#include<thread>

#include"ServerClass.h"

extern "C" {
#include <netinet/in.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <unistd.h>  
}

void server::setupTCPsocket()
{
    // Creating socket file descriptor  
    /*
    AF_INET: This specifies the address family (protocol) that will be used for the socket. 
    In this case, AF_INET indicates that the socket will use the IPv4 protocol.

    SOCK_STREAM: This specifies the type of socket that will be created. 
    In this case, SOCK_STREAM indicates a reliable, two-way, connection-based byte stream 
    socket. This means that data will be transmitted in a continuous stream of bytes and 
    that the recipient will receive all data sent in the same order as it was sent.

    0: This specifies the protocol to be used. If set to 0, the operating system will choose 
    the appropriate protocol based on the specified address family and socket type. 
    In the case of AF_INET and SOCK_STREAM, the protocol used will be TCP 
    (Transmission Control Protocol), which is the most commonly used protocol 
    for connection-oriented data transmission over IP networks.
    */
    mServer_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (mServer_fd < 0) 
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    } 

    /*
    the setsockopt() call you provided is enabling the SO_REUSEADDR option for the server_fd socket, 
    which will allow the socket to be bound to a previously-used address without waiting for the operating system to release it.
    */
    /*
    The first parameter, server_fd, is the file descriptor for the socket you want to modify.
    The second parameter, SOL_SOCKET, is a level identifier that specifies the protocol level at which the option resides. In this case, we're using the SOL_SOCKET level, which contains options that apply to sockets in general.
    The third parameter, SO_REUSEADDR, is the specific option we want to set. SO_REUSEADDR allows the reuse of a local socket address that is already in use by another socket that has a lingering connection. This option is useful in situations where you need to restart a server that was previously running and bound to a particular port, without having to wait for the operating system to release the port.
    The fourth parameter, &opt, is a pointer to the value you want to set the option to. In this case, opt is likely an integer variable that has been set to 1, indicating that we want to enable the SO_REUSEADDR option.
    The fifth parameter, sizeof(opt), specifies the size of the value pointed to by the &opt pointer. In this case, since opt is an integer variable, its size is sizeof(int).
    */
    int res = setsockopt( mServer_fd, SOL_SOCKET, SO_REUSEADDR, &mOpt, sizeof(mOpt) );
    if (res) 
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  

    //setting up the address information for the socket in preparation
    //set port number to the socket
    mAddress.sin_family = AF_INET;  
    mAddress.sin_addr.s_addr = INADDR_ANY;  
    mAddress.sin_port = htons(mPort);

    // Forcefully attaching socket to port 8081 
    res = bind( mServer_fd, (struct sockaddr*)&mAddress, sizeof(mAddress) );
    if( res  < 0 )
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  

    //enable the server socket referenced by server_fd to accept incoming client connections.
    //second argument specifies the maximum number of pending connections that can be queued up before the server starts rejecting new connections.
    res = listen(mServer_fd, 3);

    if (res < 0)
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }
}


