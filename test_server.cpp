#include"ServerClass.h"
#include<thread>
#include<ostream>
#include<iostream>
#include<vector>
#include<memory>
#include<map>


///extern "C" {
#include <netinet/in.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#include <queue>
//}

/*CHAT APPLICATION MULTIPLE CLIENTS*/

/* Client packet format */
/* 100byte 100byte 1000byte */
/* |UserID|To Whom|msg| */

class myServer : public server
{
public:
    myServer( int port )
    {
        mPort = port;
    }; 

private:
    std::map<std::string,int> nameToSocketID;
    // create a queue of tuples <socket ID, msg>
    std::queue<std::tuple<int, std::string>> msgQueue;

public:
    void addClients( std::string msg,int socket ){
        
        // decode name
        std::string str = msg;
        std::vector<std::string> tokens;

        size_t pos = 0;
        std::string token;
        while ((pos = str.find("#")) != std::string::npos) {
            token = str.substr(0, pos);
            tokens.push_back(token);
            str.erase(0, pos + 1);
        }
        tokens.push_back(str);

        //THERE SHOULD BE AN INITIAL MSG
        if( tokens.size() == 1 ) // Means it is the initial msg and new client
        {
            std::string sender   = tokens[0];
            if ( nameToSocketID.find(sender) == nameToSocketID.end() )
            {
                //nameToSocketID[sender] = socket;
                nameToSocketID.insert( std::make_pair( sender, socket ) );
            }
        }
 
        if( tokens.size() == 3 ) 
        {
            std::string sender   = tokens[1];
            std::string receiver = tokens[2];
            std::string msg      = tokens[0];

            auto it = nameToSocketID.find(receiver);
            if (it != nameToSocketID.end()) 
            {
                msgQueue.push( std::make_tuple( it->second, msg ) );
                send(it->second, msg.c_str(), msg.length(), 0);  
            } 
            else 
            {
                std::cout << "no such receiver" << std::endl;
            }
        }
    }

    void handle_clients( int socket ){
        char buffer[1024] = { 0 };  
        
        while(1)
        {
            int valread = read( socket, buffer, 1024 );  
            printf("%s\n", buffer);

            addClients( buffer,socket );
            buffer;
        }
    }
};

int main()  
{  
    int port = 8081;
    std::shared_ptr<server> testServer(new myServer(port));
    try{
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
    }
    catch(...)
    {
        for (const auto& sock : testServer->mSocketIDs) {
            shutdown(sock, SHUT_RDWR);

            // send any remaining data
            char buffer[1];
            while (send(sock, buffer, 0, 0) > 0);

            // receive any remaining data
            while (recv(sock, buffer, 1, MSG_WAITALL) > 0);

            // close the socket
            close(sock);
        }
    }
    
    return 0;
}
