cmake_minimum_required(VERSION 3.31.6)

project(BlockchainStorage)

find_package(OpenSSL REQUIRED)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(include/)

add_executable(main include/Gui.hpp src/main.cpp src/Gui.cpp src/Deserializer.cpp src/BlockChainAlgo.cpp src/Hash.cpp src/Block.cpp src/File.cpp src/BlockChain.cpp)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
target_link_libraries(main OpenSSL::Crypto Qt5::Widgets)