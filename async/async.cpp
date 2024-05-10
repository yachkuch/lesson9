#include "async.h"

#include <iostream>
#include <algorithm>

enum class e_CommansType : int
{
    NEW_BLOCK,
    END_BLOCK,
    CANSEL_BLOCK,
};

const std::unordered_map<std::string, e_CommansType> commandTypes =
    {
        {"{", e_CommansType::NEW_BLOCK},
        {"}", e_CommansType::END_BLOCK},
        {"EOF", e_CommansType::CANSEL_BLOCK}
    };

void async::printer(std::vector<std::string> prints_)
{
    logMut.lock();
    for (const auto &el : prints_)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    logMut.unlock();
}

int async::connect(int blocCommandSize_)
{
    this->blockCommandSize = blocCommandSize_;
    return blockCommandSize;
}

void async::recieve(const char *command_, int size_)
{
    if (this->blockCommandSize == 0)
    {
        printer(commandsVector);
    }
    std::string com{command_};
    logMut.lock();
    logger.log_data(com);
    commandsVector.push_back(com);
    logMut.unlock();
    auto val = commandTypes.find(com);
    if(val != commandTypes.end())
    {
        switch (val.operator*().second)
        {
        case e_CommansType::NEW_BLOCK:
            dynamcicBlockCounter.operator++(1);
            break;
        default:
        {
            if(dynamcicBlockCounter != 0)
            {
                dynamcicBlockCounter--;
                logMut.lock();
                auto iter = commandsVector.rbegin();
                int counter = 0;
                while(iter != commandsVector.rend())
                {
                    iter++;
                    counter++;
                    if(*iter == "{" or *iter == "EOF")
                    {
                        commandsVector.erase(commandsVector.begin() + (commandsVector.size() - counter -1 ),commandsVector.end());
                        break;
                    }
                    std::cout<<*iter<<" ";
                }
                logMut.unlock();
            }
            else 
            {

            }
            return;
        }
        }
    }
    else
    {
        if(dynamcicBlockCounter == 0)
        {
            blockCommandSize--;
            if(blockCommandSize == 0)
            {
                printer(commandsVector);
                std::cout<<"END PROGRAMM"<<std::endl;
            }
        }
    }
}

void async::disconnect()
{
    recieve("EOF",3);
}