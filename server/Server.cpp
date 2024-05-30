#include "Server.h"
#include<boost/make_shared.hpp>
#include <iostream>

struct Session : std::enable_shared_from_this<Session>
{
    Session(boost::asio::io_context &context,std::shared_ptr<boost::asio::ip::tcp::socket> socket, Server &net)
      : context(context), socket(std::move(socket)),net(net){}
  boost::asio::io_context &context;
  std::shared_ptr<boost::asio::ip::tcp::socket> socket;
  std::string received_line;
  std::vector<char> unused_bytes;
  Server &net;
  void run() {
  std::array<char, 150> buff;
  socket->async_receive(
      boost::asio::buffer(buff),
      [&, unused_bytes_ref = std::ref(this->unused_bytes),
       self = shared_from_this()](const boost::system::error_code &er,
                                  size_t bytes) mutable {
        if (er) {
          std::cout << er.message() << "\n";
          return;
        }
        if (bytes == 0) {
          std::cout << "Received 0\n";
          return;
        }
        std::string recieve_string;
        if (!unused_bytes_ref.get().empty()) {
          std::cout << "Parapapa \n";
          std::abort();
        }
        for (int i =0; i<bytes -1; i++) {
          recieve_string.push_back(buff.at(i));
        }
        net.sendData(std::move(recieve_string));
        self->run();
      });
}
};

Server::Server( boost::asio::io_context &context_,std::string adr, unsigned short port) : context_(context_)
{
    boost::asio::ip::tcp::endpoint endpoint (boost::asio::ip::make_address_v4(adr),port);
    acceptor_ = new boost::asio::ip::tcp::acceptor{context_, endpoint};
    socket_map_ = std::make_shared<boost::asio::ip::tcp::socket>(context_);
    acceptor_->async_accept(*socket_map_,boost::bind(&Server::handle_accept,this,socket_map_));
}

void Server::sendData(std::string data)
{
    static int a = 0;
    if(a == 0)
    {
      a++;
      on_message_(std::stoi(data),"");
    }
    else 
    on_message_(1,data);
}

void Server::handle_accept(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
  std::cout << "New connection" << std::endl;
  auto ses = std::make_shared<Session>(context_, std::move(socket), *this);
  ses->run();
}
