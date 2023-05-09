#ifndef CLIENTCLASS_H_NAME
#define CLIENTCLASS_H_NAME

#include<iostream>

#include <arpa/inet.h>  
#include <stdio.h>  
#include <string.h>  
#include <string>
#include <sys/socket.h>  
#include <unistd.h>  

using namespace std;

class client{

public:
    client();
    ~client();

public:
    bool setParams(int PORT, string IP);
    bool connectToServer();
    virtual void buildUpMsg() = 0;
    void communicate();
    void setMsg(char* buffer, int bufferSize);

private:
    char msg[2048];
    char readbuff[2048];
    int sock;
    struct sockaddr_in serv_addr;  

};

#endif
