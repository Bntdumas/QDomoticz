#set CMAKE_PREFIX_PATH env to opt/qt

project(QDomoticz)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_AUTOMOC true)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)  
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions( -DQT_STRICT_ITERATORS )
add_definitions( -DQT_NO_CAST_FROM_ASCII )
add_definitions( -DQT_NO_CAST_TO_ASCII )
add_definitions( -DQT_NO_CAST_FROM_BYTEARRAY )
add_definitions( -DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

find_package(Qt5 5.5.0 CONFIG REQUIRED Core Network Widgets Gui)

add_subdirectory(app)

