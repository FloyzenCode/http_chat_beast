cmake_minimum_required(VERSION 3.20)

project(HTTP_BOOST)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR /Users/floyz/cpp-tools/boost_1_82_0)
set(Boost_LIBRARY_DIR /Users/floyz/cpp-tools/boost_1_82_0/stage/lib)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost COMPONENTS filesystem thread REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(http 
                src/beast.hpp
                src/http_session.cpp
                src/http_session.hpp
                src/listener.cpp
                src/listener.hpp
                main.cpp
                src/net.hpp
                src/shared_state.cpp
                src/shared_state.hpp
                src/websocket_session.cpp
                src/websocket_session.hpp
                html/chat_client.html
)