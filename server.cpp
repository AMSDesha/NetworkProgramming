// Server side C/C++ program to demonstrate Socket  
// programming  
#include <netinet/in.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#define PORT 8081
int main(int argc, char const* argv[])  
{  
       int server_fd, new_socket, valread;  
       struct sockaddr_in address;  
       int opt = 1;  
       int addrlen = sizeof(address);  
       char buffer[1024] = { 0 };  
       char hello[] = "Hello from server";  
  
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
       if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  
               perror("socket failed");  
               exit(EXIT_FAILURE);  
       }  
  
       // Forcefully attaching socket to port 8080  
       if (setsockopt(server_fd, SOL_SOCKET,  
                               SO_REUSEADDR, &opt,  
                               sizeof(opt))) {  
               perror("setsockopt");  
               exit(EXIT_FAILURE);  
       }  
       address.sin_family = AF_INET;  
       address.sin_addr.s_addr = INADDR_ANY;  
       address.sin_port = htons(PORT);  
  
       // Forcefully attaching socket to port 8081 
       if (bind(server_fd, (struct sockaddr*)&address,  
                       sizeof(address))  
               < 0) {  
               perror("bind failed");  
               exit(EXIT_FAILURE);  
       }  
       if (listen(server_fd, 3) < 0) {  
               perror("listen");  
               exit(EXIT_FAILURE);  
       }

        if ( ( new_socket  = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))  < 0 )
        {  
                perror("accept");  
                exit(EXIT_FAILURE);  
        }  

        int cout = 0;
       while(1)
       {
                valread = read(new_socket, buffer, 1024);  
                printf("%s\n", buffer);  


                sprintf(hello, "%d", cout++);
                send(new_socket, hello, strlen(hello), 0);  
       }
  
       // closing the connected socket  
       close(new_socket);  
       // closing the listening socket  
       shutdown(server_fd, SHUT_RDWR);  
       return 0;  
}  