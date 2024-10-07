#include "./TodoApp.h"

int main() {
    try {
        // Create the TodoApp object 
        TodoApp app;

        // Adding middlewares
        app.CORS();

        // Add routes
        app.createTodo();
        app.getTodos();
        app.deleteTodo();
        app.homepage();

        // Establish DB connection
        app.DbConnect("todoApp", "root", "root");

        // Start the server
        app.startServer();

    } catch (const std::exception& ex) {
        cerr << "Exception: " << ex.what() << endl;
    }
    return 0;
}
