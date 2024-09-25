cmake_minimum_required(VERSION 3.10.0)
project(server )

include(/usr/local/cmake/SOCI.cmake)
# list(APPEND CMAKE_MODULE_PATH "/usr/local/lib/cmake")
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/local/lib/cmake/SOCI/")
# find_package(SOCI REQUIRED )
add_executable(server server.cpp)

target_link_libraries(server
        PRIVATE SOCI::soci_core
        PRIVATE SOCI::soci_mysql
        )

        target_include_directories(server PRIVATE /usr/include/mysql/
        )
