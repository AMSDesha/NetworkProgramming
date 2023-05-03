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

/*CHAT APPLICATION MULTIPLE CLIENTS*/

/* Client packet format */
/* 100byte 100byte 1000byte */
/* |UserID|To Whom|msg| */

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
