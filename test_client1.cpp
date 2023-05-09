#include"ClientClass.h"

#include<thread>

class myClient : public client{
public:
    myClient(){};
    ~myClient(){};
public:
    void buildUpMsg(){
        char buff[2048];
        strcat(buff,"Sam Macathi#"); // Who am i
        strcat(buff,"Jhon Samuwel#"); // msg to
        strcat(buff,"Hi Jhon, Did you recive my msg"); // msg

        client::setMsg( buff,sizeof(buff));
    }
};

class myClient2 : public client{
public:
    myClient2(){};
    ~myClient2(){};
public:
    void buildUpMsg(){
        char buff[2048];
        strcat(buff,"Jhon Samuwel#"); // Who am i
        strcat(buff,"Sam Macathi#"); // msg to
        strcat(buff,"Hi Sam, Yes, great to hear from u"); // msg

        client::setMsg( buff,sizeof(buff));
    }
};

int main(int argc, char const* argv[])  
{  
    myClient client;
    client.setParams(8081,"127.0.0.1");
    client.connectToServer();
    client.buildUpMsg();
    std::thread comm1(&client::communicate,client);
    comm1.detach();  

    myClient2 client2;
    client2.setParams(8081,"127.0.0.1");
    client2.connectToServer();
    client2.buildUpMsg();
    std::thread comm2(&client::communicate,client2);
    comm2.detach();  
}