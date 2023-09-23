#pragma once
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "FifoQueue.hpp"


class Connection
{
public:
    Connection(const std::string& url);
    ~Connection();
    const char* GetResponce();
    FifoQueue<const char*> queue;
private:
    static void* _startFlood(void* attr);


    pthread_t _thread;
    std::string _url;
    boost::asio::io_context _io_context;
    boost::asio::ip::tcp::resolver _resolver;
    boost::asio::ip::tcp::socket _socket;
};