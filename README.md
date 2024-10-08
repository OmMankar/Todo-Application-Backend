# Todo-Application-Backend (C++)

## Overview
  - The ToDo Application Backend is a simple backend solution written in C++ that allows users to
    manage their tasks (ToDos).
  - It uses various libraries to handle HTTP requests, parse JSON data, and interact with a MySQL
    database for task storage.

## Technologies Used:
- **httplib** : For handling HTTP server functionality.
- **nlohmann::json**: For parsing JSON requests and responses.
- **SOCI**: For interacting with a MySQL database.
  
  The application supports basic CRUD (Create, Read, Update, Delete) operations on ToDo tasks.

## Features
- **Server Setup**

  The server is set up using the httplib library and listens for incoming requests at http://localhost:8080.
- **Database Connection**
  
  The backend connects to a MySQL database named todoApp using the SOCI library.
  It ensures the database connection is successful and gracefully handles any errors during the connection process.
## CRUD Operations
- **Create ToDo (POST /createTodo)**

  Accepts JSON data containing event and date fields.

  Validates the input and inserts the data into the MySQL database.

  If either event or date is missing, the server responds with an error message.

- **Retrieve ToDos (GET /getTodo)**

  Fetches all ToDo entries from the database.

  Converts the results into a JSON array.

  Sends the JSON array in the response.



- **Delete ToDo (DELETE /todoComplete)**

  Deletes a specific ToDo based on the event and date provided in the request.

  Responds with a success message if the deletion is successful.

- **Home Page (GET /)**

  A simple homepage that responds with the text "Welcome to home page" when accessing the root endpoint.

## JSON Parsing

  The nlohmann::json library is used for parsing incoming JSON requests and generating responses in JSON format.

  This ensures clear communication between the client and server using JSON standards.

## Error Handling

  Each HTTP method includes robust error handling for:

  Malformed or incorrect JSON requests.

  Incomplete data inputs (e.g., missing event or date).

  Database-related errors, such as failed queries or connection issues.

## Conclusion

  The ToDo Application Backend provides basic functionality to manage tasks using modern C++ libraries for HTTP handling, JSON parsing, and MySQL database interactions.   

  It serves as a fundamental example of task management using a C++ backend.
