#ifndef HTTP_SESSION_HPP
#define HTTP_SESSION_HPP

#include "net.hpp"
#include "beast.hpp"
#include "shared_state.hpp"
#include <boost/optional.hpp>
#include <boost/smart_ptr.hpp>
#include <cstdlib>
#include <memory>

class http_session : public boost::enable_shared_from_this<http_session>
{
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    boost::shared_ptr<shared_state> state_;

    boost::optional<http::request_parser<http::string_body>> parser_;

    struct send_lambda;

    void fail(beast::error_code ec, char const *what);
    void do_read();
    void on_read(beast::error_code ec, std::size_t);
    void on_write(beast::error_code ec, std::size_t, bool close);

public:
    http_session(
        tcp::socket &&socket,
        boost::shared_ptr<shared_state> const &state);

    void run();
};

#endif
