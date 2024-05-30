#include <iostream>
#include <algorithm>
#include "async/async.h"
#include <boost/signals2.hpp>
#include <boost/asio/io_context.hpp>
#include "Server.h"
#include <memory>
void writes(async &a)
{
    a.connect(4);
    for(int i = 0; i <10000; i++)
    {
    a.recieve("a",1);
    a.recieve("a",1);
    a.recieve("a",1);
    a.recieve("{",1);
    a.recieve("b",1);
    a.recieve("b",1);
    a.recieve("c",1);
    a.recieve("}",1);
    a.recieve("{",1);
    }
}

// void smth(async &a)
// {
//     a.connect(4);
//     std::cout<<"sdf"<<std::endl;
    
// }

void start(boost::asio::io_context &context)
{
    context.run();
}

int main(int, char**)
{
    
    std::cout << "Hello, from logger!\n";
    async a;
    boost::asio::io_context context;
    std::cout<<"Give me port number"<<std::endl;
    int port{};
    std::cin>>port;
    Server serv(context,"127.0.0.1",port);
    serv.on_message_.connect(a);
    std::thread thread(start,std::ref(context));
    //writes(a);
    thread.join();
}
