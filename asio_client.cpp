#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/tcp.hpp>
//#include <boost/system/detail/error_code.hpp>
#include <iostream>
namespace asio = boost::asio;
int main() 
{
asio::io_context context;

  asio::ip::tcp::socket socket{context};
  socket.connect(
      asio::ip::tcp::endpoint{asio::ip::make_address_v4("127.0.0.1"), 1337});
  while (true) {
    std::string line;
    std::getline(std::cin, line);
    line.append("\n");

    boost::system::error_code ec;
    auto send_n = socket.send(asio::buffer(line), {}, ec);
    assert(!ec);
    assert(send_n == line.size());
  }
}