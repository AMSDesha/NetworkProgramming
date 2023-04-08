#include"ServerClass.h"
#include<thread>
#include<ostream>
#include<iostream>
#include<vector>
#include <memory>


extern "C" {
#include <netinet/in.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <unistd.h>  
}

/* Just a sample class to try thread and it works*/
/*
class Task
{
public:
    void execute()
    {
        for(int i = 0; i < 5; i++)
        {
            std::cout<<"Test"<<" :: "<<i<<std::endl;
        }
    }
};
*/

/*
class server{

public:
    server(int port){
         mPort = port;
    };
    ~server(){

    };

    void setupTCPsocket()
    {
            mServer_fd = socket(AF_INET, SOCK_STREAM, 0);
            if (mServer_fd < 0) 
            {  
                perror("socket failed");  
                exit(EXIT_FAILURE);  
            } 

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
    };

    void acceptIncoming()
    {
            std::cout << "Started accepting incoming..." << std::endl;   
            while(1)
            {
                int socket  = accept( mServer_fd, (struct sockaddr*)&mAddress, (socklen_t*)&addrlen );

                if ( socket  < 0 )
                {  
                    perror("can not accept");  
                    //exit(EXIT_FAILURE);  
                }
                else{
                    mSocketIDs.push_back(socket);
                }

                std::cout << "New client connected" << std::endl;                
            }
    };

    void handle_clients(int socket)
    {
        char buffer[1024] = { 0 };  
        char hello[] = "Hello from server"; 

        // Declaring iterator to a vector
        std::vector<int>::iterator ptr;

        std::cout << "Started listning..." << std::endl;  
        
        while(1)
        {
            int valread = read(socket, buffer, 1024);  
            printf("%s\n", buffer);

            send(socket, hello, strlen(hello), 0);  
        }
    };

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

*/

int main()  
{  
    int port = 8081;
    std::shared_ptr<server> testServer(new server(port));
    testServer->setupTCPsocket();
    
    //std::thread accept(&server::acceptIncoming,testServer);

    std::cout << "Started accepting incoming..." << std::endl;   
    while(1)
    {
        int socket  = accept( testServer->mServer_fd, (struct sockaddr*)&testServer->mAddress, (socklen_t*)&testServer->addrlen );

        if ( socket  < 0 )
        {  
            perror("can not accept");  
            //exit(EXIT_FAILURE);  
        }
        else{
            testServer->mSocketIDs.push_back(socket);
        }

        std::cout << "New client connected" << std::endl;   

        std::thread listen(&server::handle_clients,testServer,socket);

        listen.detach();     
    }
    
    /* Just a sample class to try thread and it works*/
    /*
    Task * taskPtr = new Task();
    // Create a thread using member function
    std::thread th(&Task::execute, taskPtr);
    th.join();
    delete taskPtr;
    */
    return 0;
}
