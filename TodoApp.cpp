#include "TodoApp.h"

using namespace std;
using namespace httplib;

void TodoApp::DbConnect(const string& dbName, const string& dbUser, const string& dbPassword) {
    try {
        sql.open(soci::mysql, "db=" + dbName + " user=" + dbUser + " password='" + dbPassword + "'");
        if (sql.is_connected()) {
            cout << "Connection established with Database" << endl;
        } else {
            cout << "Error connecting to the database" << endl;
            throw runtime_error("Database connection failed.");
        }
    } catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
}

void TodoApp::CORS() {
    svr.set_post_routing_handler([](const auto& req, auto& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Headers", "Content-Range, Accept-Range, Content-Type, Content-Length, Accept-Encoding, X-CSRF-Token, Authorization, accept, origin, Cache-Control, X-Requested-With");
        res.set_header("Access-Control-Allow-Methods", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    });
}

void TodoApp::createTodo() {
    svr.Post("/createTodo", [&](const Request& req, Response& res) {
        auto data = req.body;
        cout << "Request data: " << data << endl;

        nlohmann::json jObj = nlohmann::json::parse(data);
        string eventName = jObj["event"];
        string eventDate = jObj["date"];

        if (eventName.empty() || eventDate.empty()) {
            res.status = 400;
            res.set_content("{\"error\": \"Invalid JSON format\",\"success\": \"false\"}", "application/json ");
            return;
        }

        sql << "INSERT INTO todo(event, date) VALUES(:event, :date)", soci::use(eventName), soci::use(eventDate);
        res.status = 200;
        res.set_content("{\"message\": \"Todo Entry Created Successfully\",\"success\": \"true\"}", "application/json ");
    });
}

void TodoApp::getTodos() {
    svr.Get("/getTodo", [&](const Request& req, Response& res) {
        try {
            soci::rowset<soci::row> results = (sql.prepare << "SELECT * FROM todo");
            nlohmann::json response_json = nlohmann::json::array();

            for (auto it = results.begin(); it != results.end(); ++it) {
                soci::row const& row = *it;
                nlohmann::json ex1;
                ex1["event"] = row.get<string>(0);
                ex1["date"] = row.get<string>(1);
                response_json.push_back(ex1);
            }

            nlohmann::json responseObj;
            responseObj["data"] = response_json;

            res.status = 200;
            res.set_content(responseObj.dump(), "application/json");
        } catch (const std::exception& ex) {
            cout << ex.what() << endl;
            res.set_content("{\"error\": \"Unable to fetch todos\",\"success\": \"false\"}", "application/json ");
        }
    });
}

void TodoApp::deleteTodo() {
    svr.Delete("/todoComplete", [&](const Request& req, Response& res) {
        auto data = req.body;
        cout << "Request data: " << data << endl;

        nlohmann::json jObj = nlohmann::json::parse(data);
        string eventName = jObj["event"];
        string eventDate = jObj["date"];

        if (eventName.empty() || eventDate.empty()) {
            res.status = 400;
            res.set_content("{\"error\": \"Invalid JSON format\",\"success\": \"false\"}", "application/json ");
            return;
        }

        try {
            sql << "DELETE FROM todo WHERE event=:eventName AND date=:eventDate", soci::use(eventName), soci::use(eventDate);
            res.status = 200;
            res.set_content("{\"message\": \"Todo removed successfully from database.\"}", "application/json ");
        } catch (const std::exception& ex) {
            cout << ex.what() << endl;
            res.status = 500;
            res.set_content("{\"error\": \"Unable to remove todo from database.\",\"success\": \"false\"}", "application/json ");
        }
    });
}

void TodoApp::homepage() {
    svr.Get("/", [&](const Request& req, Response& res) {
        res.set_content("Welcome to home page", "text/plain");
    });
}

void TodoApp::startServer() {
    cout << "Server started at: http://localhost:8080/" << endl;
    svr.listen("0.0.0.0", 8080);
}

TodoApp::~TodoApp() {
    sql.close();
    svr.stop();
    cout << "Server closed" << endl;
}
