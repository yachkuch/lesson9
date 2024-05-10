#include <iostream>
#include <algorithm>
#include "async/async.h"

void write(async &a)
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

int main(int, char**)
{
    std::cout << "Hello, from logger!\n";
    async a;
    std::thread t(write,std::ref(a));
    std::thread t1(write,std::ref(a));
    std::thread t2(write,std::ref(a));
    t.detach();
    t1.detach();
    t2.detach();
    std::cout<<"Hello, from logger\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<<"Hello, from logger\n";
}
