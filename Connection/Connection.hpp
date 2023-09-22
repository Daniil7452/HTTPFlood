#pragma once
/*
    Не уверен, можно ли было использовать boost::asio.
    Если нет, могу переделать на curl.
*/

#include <iostream>
#include <string>
#include <boost/asio.hpp>



class Connection
{
public:
    Connection(const std::string& url);
    const char* GetResponce();

private:
    std::string _url;
    boost::asio::io_context _io_context;
    boost::asio::ip::tcp::resolver _resolver;
    boost::asio::ip::tcp::socket _socket;
};