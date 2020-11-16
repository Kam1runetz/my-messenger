//
// Created by w1ckedente on 16.11.2020.
//

#include <boost/asio.hpp>
#include <chrono>
#include <cstring>
#include <iostream>
#include <myprotocol.hpp>
#include <myprotocoldefs.hpp>

const char address[] = "localhost";
const char port[] = "4567";

int main(int argc, char **argv) {
  boost::asio::io_service ioService;
  boost::asio::ip::tcp::resolver resolver(ioService);
  boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(),
                                              address, port);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

  boost::asio::ip::tcp::socket socket(ioService);
  socket.connect(endpoint);

  MyProtocolPkg pkg;
  MyProtocolPkg recv;
  std::string message(argv[1]);
  memcpy(pkg.Content.messagePkg.Message, message.c_str(), MessageLength);

  for (int i = 0; i < 10; ++i) {
    try {
      boost::asio::write(socket,
                         boost::asio::buffer(&pkg, sizeof(MyProtocolPkg)));
      boost::asio::read(socket,
                        boost::asio::buffer(&recv, sizeof(MyProtocolPkg)));
      std::cout << "[" << i << "] Received: " << recv.Content.messagePkg.Message
                << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(5));
    } catch (std::exception &e) {
      std::cout << "Exception: " << e.what() << std::endl;
    }
  }
  socket.close();
  return 0;
}