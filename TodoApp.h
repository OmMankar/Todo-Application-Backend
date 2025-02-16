#ifndef TODO_APP_H
#define TODO_APP_H

#include "thirdparty/cpp-httplib/httplib.h"
#include "thirdparty/json/single_include/nlohmann/json.hpp"
// #include <soci/mysql/soci-mysql.h>
#include "soci/mysql/soci-mysql.h"
#include "soci/rowset.h"
#include "soci/soci.h"
#include<string>
#include<vector>

using namespace std;

class TodoApp {
private:
    soci::session sql;
    httplib::Server svr;

public:
    void DbConnect(const string& dbName, const string& dbUser, const string& dbPassword);
    void CORS();
    void createTodo();
    void getTodos();
    void deleteTodo();
    void homepage();
    void startServer();
    ~TodoApp();
};

#endif // TODO_APP_H
