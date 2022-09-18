#include <iostream>
#include <optional>
#include <boost/asio.hpp>

/*All credits to
https://dens.website/tutorials/cpp-asio/async-tcp-server
*/

/*
BoostExo % nc -v 127.0.0.1 15001
Connection to 127.0.0.1 port 15001 [tcp/*] succeeded!
jjlkll
*/



class session : public std::enable_shared_from_this<session>
{
public:

    session(boost::asio::ip::tcp::socket&& socket)
    : socket(std::move(socket))
    {
    }

    void start()
    {
        boost::asio::async_read_until(socket, streambuf, '\n', [self = shared_from_this()] (boost::system::error_code error, std::size_t bytes_transferred)
        {
            //flush if you want results to be printed right away
            std::cout << std::istream(&self->streambuf).rdbuf() << std::flush;
        });
    }

private:

    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
};

class server
{
public:

    server(boost::asio::io_context& io_context, std::uint16_t port)
    : io_context(io_context)
    , acceptor  (io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
    }

    void async_accept()
    {
        socket.emplace(io_context);

        acceptor.async_accept(*socket, [&] (boost::system::error_code error)
        {
            std::make_shared<session>(std::move(*socket))->start();
            async_accept();
        });
    }

private:

    boost::asio::io_context& io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
};

int main()
{
    std::cout << "starting\n" << std::flush;
    boost::asio::io_context io_context;
    server srv(io_context, 15001);
    srv.async_accept();
    io_context.run();
    return 0;
}
