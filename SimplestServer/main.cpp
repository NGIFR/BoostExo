//Credits to https://dens.website/tutorials/cpp-asio/simplest-server

//tools netcat:
//choco install netcat

//test:
/*PS C:\Users\ngi33> nc -u 127.0.0.1 15001
Hello
Hello*/

#include <boost/asio.hpp>
#include <cstdint>

int main()
{
    std::uint16_t port = 15001;
    //auto addr = boost::asio::ip::address::from_string("127.0.0.1");
    boost::asio::io_context io_context;
    boost::asio::ip::udp::endpoint receiver(boost::asio::ip::udp::v4(), port);
    boost::asio::ip::udp::socket socket(io_context, receiver);

    for (;;)
    {
        char buffer[65536];
        boost::asio::ip::udp::endpoint sender;
        std::size_t bytes_transferred = socket.receive_from(boost::asio::buffer(buffer), sender);
        socket.send_to(boost::asio::buffer(buffer, bytes_transferred), sender);
    }

    return 0;
}