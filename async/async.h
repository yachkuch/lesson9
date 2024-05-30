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

const auto writere = [](std::string deta, std::shared_ptr<std::atomic<bool>> flag,std::shared_ptr<std::ofstream> fstream)
{
    flag->operator=(false);
    deta.append("\n");
    fstream->write(deta.data(),deta.size());
    flag->operator=(true);
};

class async
{

    class logger_Class
    {

        std::shared_ptr<std::ofstream> fileThreadA;
        std::shared_ptr<std::ofstream> fileThreadB;

        std::shared_ptr<std::atomic<bool>> flag1 ;
        std::shared_ptr<std::atomic<bool>> flag2;

    public:
        void log_data(std::string data)
        {
            // ошибка возможна утечка памяти
            if (flag1.get()->load() == true)
            {
                auto file1 = std::thread(writere,std::move(data),flag1,fileThreadA);
                file1.detach();
            }
            else if (flag1.get()->load()== true)
            {
                
                auto file1 = std::thread(writere,std::move(data),flag2,fileThreadB);
                file1.detach();
            }
            else
            {
                log_data(data);
            }
        }
        logger_Class() : flag1(std::make_shared<std::atomic<bool>>(true)), flag2(std::make_shared<std::atomic<bool>>(true)),
        fileThreadA(std::make_shared<std::ofstream>()), fileThreadB(std::make_shared<std::ofstream>())
        {
            fileThreadA.get()->open("1.txt");
            fileThreadB.get()->open("2.txt");
            if(!fileThreadA.get()->is_open()) std::abort();
            if(!fileThreadB.get()->is_open()) std::abort();
        }
        ~logger_Class()
        {
            fileThreadA.get()->close();
            fileThreadB.get()->close();
        }

        logger_Class &operator=(const logger_Class &log) = default;
        logger_Class &operator=(logger_Class &&log) = default;
        logger_Class(const logger_Class &log) = default;
        logger_Class( logger_Class &&log) = default;
    };

public:
    async() = default;
    async(const async &as) = default;
    async(async &&as) = default;
    int connect(int blocCommandSize_);
    void recieve(const char *command_, int size_);
    void disconnect();

    void operator() (int ,std::string data);

private:

    std::shared_ptr<std::mutex> logMut{std::make_shared<std::mutex>()};
    std::shared_ptr<std::mutex> writeInComVect{std::make_shared<std::mutex>()};
    std::shared_ptr<std::atomic<int>> dynamcicBlockCounter{std::make_shared<std::atomic<int>>(0)};
    std::shared_ptr<std::atomic<int>> blockCommandSize{std::make_shared<std::atomic<int>>(0)};

    std::vector<std::string> commandsVector;
    void printer(std::vector<std::string> prints_);
    logger_Class logger;
};

#endif // __ASYNC_H_RWPAIYPRNZUO__
