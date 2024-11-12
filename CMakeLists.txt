# cmake_minimum_required(VERSION 3.10.0)
# project(server )

# include(/usr/local/cmake/SOCI.cmake)
# # list(APPEND CMAKE_MODULE_PATH "/usr/local/lib/cmake")
# # set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/local/lib/cmake/SOCI/")
# # find_package(SOCI REQUIRED )
# add_executable(server2 server2.cpp)

# target_link_libraries(server2
#         PRIVATE SOCI::soci_core
#         PRIVATE SOCI::soci_mysql
#         )

#         target_include_directories(server2 PRIVATE /usr/include/mysql/
#         )

cmake_minimum_required(VERSION 3.10.0)
project(TodoAppServer)

include(/usr/local/cmake/SOCI.cmake)

# Add source files
set(SOURCES
    main.cpp
    TodoApp.cpp
)

# Add header files
set(HEADERS
    TodoApp.h
)

# Define the executable
add_executable(TodoAppServer ${SOURCES} ${HEADERS})

# Link SOCI libraries
target_link_libraries(TodoAppServer
    PRIVATE SOCI::soci_core
    PRIVATE SOCI::soci_mysql
)

# Include MySQL headers
target_include_directories(TodoAppServer PRIVATE /usr/include/mysql/)
