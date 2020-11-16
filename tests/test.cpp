// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#include <gtest/gtest.h>

#include <PlainRequestHandler.hpp>
#include <Server.hpp>
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include <chrono>
#include <cstring>
#include <myprotocol.hpp>
#include <thread>

const char address[] = "localhost";
const char port[] = "4567";

TEST(Empty, EmptyTest) {
  Server server(address, port, new PlainRequestHandler);
  std::thread serverThread(&Server::Run, &server);
  std::this_thread::sleep_for(std::chrono::seconds(60));
  server.Stop();
  serverThread.join();

  EXPECT_TRUE(true);
}
