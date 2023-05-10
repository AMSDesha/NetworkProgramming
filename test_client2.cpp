#include"ClientClass.h"

#include<thread>

class myClient : public client{
public:
    myClient(){};
    ~myClient(){};
public:
    // Initial msg when connecting to the server
    void initialMsg(){
        std::string Who_am_I = "Jhon Samuwel"; // Who am i
        sendMsg( Who_am_I );
    };

    void communicate(){
        std::string msg;
        while(1)
        {
            std::getline(std::cin, msg);
            msg.append("#Jhon Samuwel#Sam Macathi");
            sendMsg(msg);
        }
    }
};


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

    while(1)
    {};
}