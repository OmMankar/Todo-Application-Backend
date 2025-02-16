# TodoApp
## Overview
TodoApp is a C++ server application that provides a simple REST API for managing a to-do list. It connects to a MySQL database to store and retrieve todo entries, and it uses the following libraries:

- cpp-httplib for HTTP server handling.
- SOCI for database connectivity.
- nlohmann/json for JSON parsing.
## Features
- Create Todo: Add a new to-do entry to the database.
- Get Todos: Retrieve all existing to-do entries.
- Delete Todo: Delete a to-do entry based on specific criteria.
- Homepage: Simple welcome message.
  

## Prerequisites
- C++17 or later.
- MySQL server.
- Required C++ Libraries files:
    - **cpp-httplib**: HTTP server header only library ([cpp-httplib](https://github.com/yhirose/cpp-httplib))
    - **nlohmann/json**: JSON parser header only library ([nlohmann/json](https://github.com/nlohmann/json))
    - **SOCI**: Database library with MySQL support ([SOCI](https://github.com/SOCI/soci))
   

 

## Directory Structure
```

   ├── main.cpp              # Main entry point
   ├── TodoApp.h             # TodoApp header file
   ├── TodoApp.cpp           # TodoApp implementation
   ├──CMakeLists.txt            # CMake build file
   ├──README.md                 # Project documentation
```
## Setup


 ### 1. Clone the repository:
  ```
  git clone https://github.com/OmMankar/Todo-Application-Backend.git
  cd Todo-Application-Backend
  ```
 ### 2. Clone and Build dependencies:
 - Installing prerequisites (ubuntu)
  ```
  sudo apt install git cmake gcc g++ build-essential  libmysqlclient-dev
  ```
- Fetching Dependancies
  ```
  git submodule update --init --recursive
  ```


- Building soci
  ```
    cd thirdparty/soci
    mkdir -p build
    cd build
    git checkout v4.0.1
    cmake -DSOCI_TESTS=OFF -DSOCI_CXX11=ON  ..
    make -j `nproc`
    sudo make install

  ```

 ### 3. Database Setup:

  - Set up a MySQL database with a table named todo:

  sql
  ```
  CREATE DATABASE todoApp;
USE todoApp;

CREATE TABLE todo (
    id INT AUTO_INCREMENT PRIMARY KEY,
    event VARCHAR(255) NOT NULL,
    date VARCHAR(255) NOT NULL
);
  ```

 ### 4. Build the project:

  -If using CMake, create a CMakeLists.txt file and build:

  bash
  ```
  mkdir build
  cd build
  cmake ..
  make
  ```
 ### 5. Run the Application:

  bash
  ```
  ./TodoApp
  ```
  The server will start at http://localhost:8080/.

## API Endpoints
 - ### Create Todo

    -  **Endpoint:** /createTodo
    -  **Method:** POST
    -  **Data:** {"event": "EventName", "date": "YYYY-MM-DD"}
    -  **Example:**
      bash
      ```
      curl -X POST http://localhost:8080/createTodo -d '{"event":"Meeting","date":"2023-11-14"}'
      ```
 - ### Get Todos

    -  **Endpoint:** /getTodo
    -  **Method:** GET
    -  **Example:**
    bash
    ```
    curl http://localhost:8080/getTodo
    ```
  - ### Delete Todo

    -  **Endpoint:** /todoComplete
    -  **Method:** DELETE
    -  **Data:** {"event": "EventName", "date": "YYYY-MM-DD"}
    -  **Example:**
    bash
    ```
    curl -X DELETE http://localhost:8080/todoComplete -d '{"event":"Meeting","date":"2023-11-14"}'
    ```
  
## Code Structure
- **DbConnect():** Connects to the MySQL database.
- **CORS():** Sets CORS headers.
- **createTodo():** Adds a new to-do entry.
- **getTodos():** Retrieves all to-do entries.
- **deleteTodo():** Deletes a to-do entry based on the provided event and date.
- **startServer():** Starts the HTTP server on localhost:8080.
