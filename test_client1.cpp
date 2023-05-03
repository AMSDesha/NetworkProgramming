#include"ClientClass.h"

class myClient : public client{
public:
    myClient(){};
    ~myClient(){};
public:
    void buildUpMsg(){
        client::setMsg("Hello From Client");
    }
};

int main(int argc, char const* argv[])  
{  
    myClient client;
    client.setParams(8081,"127.0.0.1");
    client.connectToServer();
    client.buildUpMsg();
    client.communicate();
}