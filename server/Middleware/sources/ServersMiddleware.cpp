//
// Created by w1ckedente on 17.11.2020.
//
#include <ServersMiddleware.hpp>
#include <array>
#include <boost/asio.hpp>
#include <myprotocol.hpp>

ServersMiddleware::ServersMiddleware(ApplicationServer* aApplicationServer)
    : applicationServer(aApplicationServer) {}

boost::asio::const_buffer ServersMiddleware::ProcessData(
    std::array<std::uint8_t, PackageSize>& data) {
  auto request = *reinterpret_cast<MyProtocolPkg*>(data.data());
  MyProtocolPkg response;
  applicationServer->HandleRequest(request, response);
  return boost::asio::const_buffer(&response, PackageSize);
}
