#ifndef SERVERCLASS_H_NAME
#define SERVERCLASS_H_NAME

#include<vector>

extern "C" {
#include <netinet/in.h>
}

class server{

public:
    server(){};
    ~server(){};
    void setupTCPsocket();
    virtual void handle_clients(int scoketID) = 0;


private:
    void acceptAndListen();

public:
        struct sockaddr_in mAddress; 
        int mServer_fd;
        int mNewSocket;
        std::vector<int> mSocketIDs;
        int addrlen = sizeof(mAddress);  
        int mOpt;
        
public:
        int mPort;

};

#endif