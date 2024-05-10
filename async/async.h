#ifndef __ASYNC_H_RWPAIYPRNZUO__
#define __ASYNC_H_RWPAIYPRNZUO__
#include <thread>
#include <mutex>
#include <filesystem>
#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <atomic>
#include <future>
#include <chrono>
#include <iostream>
#include <fstream>
///////////////////////////////////////////////////////////
/// @brief async
///

const auto writer = [](std::string deta, std::atomic<bool> &flag,std::ofstream &fstream)
{
    flag = false;
    deta.append("\n");
    fstream.write(deta.data(),deta.size());
    flag = true;
};

class async
{

    class logger_Class
    {
        std::thread file1;
        std::thread file2;

        std::ofstream fileThreadA;
        std::ofstream fileThreadB;

        std::atomic<bool> flag1{true};
        std::atomic<bool> flag2{true};

    public:
        void log_data(std::string data)
        {
            if (flag1 == true)
            {
                file1 = std::thread(writer,data,std::ref(flag1),std::ref(fileThreadA));
                file1.detach();
            }
            else if (flag2 == true)
            {
                
                file2 = std::thread(writer,data,std::ref(flag2),std::ref(fileThreadB));
                file2.detach();
            }
            else
            {
                log_data(data);
            }
        }
        logger_Class()
        {
            fileThreadA.open("1.txt");
            fileThreadB.open("2.txt");
        }
        ~logger_Class()
        {
            fileThreadA.close();
            fileThreadB.close();
        }
    };

public:
    async() = default;

    int connect(int blocCommandSize_);
    void recieve(const char *command_, int size_);
    void disconnect();

private:
    std::thread log;

    std::mutex logMut;
    std::mutex writeInComVect;
    std::atomic<int> dynamcicBlockCounter;
    std::atomic<int> blockCommandSize{};

    std::vector<std::string> commandsVector;
    void printer(std::vector<std::string> prints_);
    logger_Class logger;
};

#endif // __ASYNC_H_RWPAIYPRNZUO__
