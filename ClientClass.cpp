// programming  
#include"ClientClass.h"

client::client()
{
}

client::~client(){
};

bool client::setParams(int PORT, string IP)
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  
            printf("\n Socket creation error \n");  
            return -1;  
    }  

    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(PORT);  

    // Convert IPv4 and IPv6 addresses from text to binary  
    // form  
    if (inet_pton(AF_INET, IP.c_str(), &serv_addr.sin_addr)  <= 0)
    {  
        printf("\nInvalid address/ Address not supported \n");  
    }  
    return true;
}

int client::connectToServer()
{
    int client_fd;

    if ((client_fd  
            = connect(sock, (struct sockaddr*)&serv_addr,  
                            sizeof(serv_addr)))  
            < 0) {  
            printf("\nConnection Failed \n");  
            return -1;  
    }
    return client_fd;
}

void client::readIncoming()
{
    int valread = 0;
    while(1)
    { 
        //send(sock, msg, strlen(msg), 0);  
        valread = read(sock, readbuff, 1024);  
        printf("%s\n", readbuff);  
    }
}

void client::sendMsg( std::string msg )
{
    const char* msgBuff = msg.c_str();
    send(sock, msgBuff, msg.length(), 0);  
}
