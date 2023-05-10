#include"ClientClass.h"

#include<thread>

class myClient : public client{
public:
    myClient(){};
    ~myClient(){};
public:
    // Initial msg when connecting to the server
    void initialMsg(){
        std::string Who_am_I = "Sam Macathi"; // Who am i
        sendMsg(Who_am_I);
    };

    void communicate(){
        std::string msg;
        while(1)
        {
            std::getline(std::cin, msg);
            msg.append("#Sam Macathi#Jhon Samuwel");
            sendMsg(msg);
        }
    }
};
/*
class myClient2 : public client{
public:
    myClient2(){};
    ~myClient2(){};
public:
    // Initial msg when connecting to the server
    void initialMsg(){
        char buff[1024];
        strcat(buff,"???Jhon Samuwel"); // Who am i

        client::setMsg( buff,sizeof(buff));
    };

    void buildUpMsg(){
        char buff[1024];
        strcat(buff,"Jhon Samuwel#"); // Who am i
        strcat(buff,"Sam Macathi#"); // msg to
        strcat(buff,"Hi Sam, Yes, great to hear from u \n"); // msg

        client::setMsg( buff,sizeof(buff));
    }
};
*/

int main(int argc, char const* argv[])  
{  
    myClient client;
    client.setParams(8081,"127.0.0.1");
    int client_fd = client.connectToServer();
    client.initialMsg();
    std::thread thread1(&client::readIncoming,client);
    thread1.detach();
    std::thread thread2(&client::communicate,client);
    thread2.detach();
    /*
    myClient2 client2;
    client2.setParams(8081,"127.0.0.1");
    client2.connectToServer();
    client2.buildUpMsg();
    std::thread comm2(&client::communicate,client2);
    comm2.detach();  
    */

    // this is must otherwise main process will end
    while(1)
    {};
}