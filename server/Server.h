#ifndef __SERVER_H_5JDOLOB2E0L6__
#define __SERVER_H_5JDOLOB2E0L6__
#include <boost/signals2.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/container/vector.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <memory>


///////////////////////////////////////////////////////////
/// @brief Server класс сервера для получения информации
///
class Server final
{
public:
    Server( boost::asio::io_context &context_,std::string adr, unsigned short port);

    void sendData(std::string data);
    /// @brief 
    boost::signals2::signal<void(int,std::string)> on_message_;

private:

    void handle_accept(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    /// @brief Набор параметров необходимый для подключения клиентов
    boost::asio::io_context &context_;
    std::shared_ptr<boost::asio::ip::tcp::socket> socket_map_;
    boost::asio::ip::tcp::acceptor *acceptor_ = nullptr;
};



#endif  // __SERVER_H_5JDOLOB2E0L6__
