#ifndef SHARED_STATE_HPP
#define SHARED_STATE_HPP

#include <boost/smart_ptr.hpp>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_set>

class websocket_session;

class shared_state
{
    std::string const doc_root_;
    std::mutex mutex_;
    std::unordered_set<websocket_session *> sessions_;

public:
    explicit shared_state(std::string doc_root);

    std::string const &
    doc_root() const noexcept
    {
        return doc_root_;
    }

    void join(websocket_session *session);
    void leave(websocket_session *session);
    void send(std::string message);
};

#endif
