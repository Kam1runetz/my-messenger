//
// Created by w1ckedente on 17.11.2020.
//

#ifndef MESSENGER_SERVERSMIDDLEWARE_HPP
#define MESSENGER_SERVERSMIDDLEWARE_HPP

#include <ApplicationServer.hpp>
#include <array>
#include <boost/asio.hpp>
#include <memory>
#include <myprotocol.hpp>

class ServersMiddleware {
 public:
  explicit ServersMiddleware(ApplicationServer *aApplicationServer);
  ~ServersMiddleware() = default;

  static const std::size_t PackageSize = sizeof(MyProtocolPkg);

  boost::asio::const_buffer ProcessData(
      std::array<std::uint8_t, PackageSize> &data);

 private:
  std::shared_ptr<ApplicationServer> applicationServer;
};

#endif  // MESSENGER_SERVERSMIDDLEWARE_HPP
