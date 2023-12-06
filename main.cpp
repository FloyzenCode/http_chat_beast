#include "./src/listener.hpp"
#include "./src/shared_state.hpp"
#include <boost/asio/signal_set.hpp>
#include <boost/smart_ptr.hpp>
#include <iostream>
#include <vector>

auto main(int argc, char *argv[]) -> int
{
    if (argc != 5)
    {
        std::cerr << "Usage: websocket-chat-multi <address> <port> <doc_root> <threads>\n"
                  << "Example:\n"
                  << "    websocket-chat-server 0.0.0.0 8080 . 5\n";
        return EXIT_FAILURE;
    }
    auto address = net::ip::make_address(argv[1]);
    auto port = static_cast<unsigned short>(std::atoi(argv[2]));
    auto doc_root = argv[3];
    auto const threads = std::max<int>(1, std::atoi(argv[4]));

    net::io_context ioc;

    boost::make_shared<listener>(
        ioc,
        tcp::endpoint{address, port},
        boost::make_shared<shared_state>(doc_root))
        ->run();

    net::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait(
        [&ioc](boost::system::error_code const &, int)
        { ioc.stop(); });

    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for (auto i = threads - 1; i > 0; --i)
        v.emplace_back(
            [&ioc]
            {
                ioc.run();
            });
    ioc.run();

    for (auto &t : v)
        t.join();

    return EXIT_SUCCESS;
}
