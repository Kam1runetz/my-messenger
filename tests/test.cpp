// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#include <gtest/gtest.h>
#include <Server.hpp>
#include <PlainRequestHandler.hpp>
#include <thread>
#include <chrono>

const char address[] = "localhost";
const char port[] = "4567";

TEST(Empty, EmptyTest) {
    Server server(address, port, new PlainRequestHandler);
    std::thread serverThread(&Server::Run, &server);

    std::this_thread::sleep_for(std::chrono::seconds(5));
    server.Stop();
    serverThread.join();
    EXPECT_TRUE(true);
}
