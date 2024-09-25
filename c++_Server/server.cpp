// #define CPPHTTPLIB_OPENSSL_SUPPORT
#include "/home/om/projects/cpp-httplib/httplib.h"
#include "/home/om/projects/json-develop/single_include/nlohmann/json.hpp"
// #include <soci/mysql/soci-mysql.h>
#include "soci/mysql/soci-mysql.h"
#include "soci/rowset.h"
#include "soci/soci.h"
#include<string>
#include<vector>


using namespace httplib;

using namespace std;
int main(){
  try{

  
  
Server svr;

//database config
soci::session sql{};
    sql.open(soci::mysql, "db=todoApp user=root password='root'");
    if (sql.is_connected()) {
      cout<<"connection establiseh with Database"<<endl;

    }
    else{
      cout<<"Error connecting database";
      return 0 ;
    }


// Creating a todo application
#if 1
//ading todos
svr.Post("/createTodo",[&](const Request& req, Response& res){
  
  // Data doesnt get parsed we need to parse it using json/nolhman
  auto data=req.body;
  cout<<"Request data\n"<<data<<endl;
  
  //parsing a json file to json object
  nlohmann::json jObj=nlohmann::json::parse(data);

  std::string eventName=jObj["event"];
   std::string eventDate=jObj["date"];
    //input dat incomplete
   if(eventName==""||eventDate=="")
   {
        res.status = 400;
       res.set_content("{\"error\": \"Invalid JSON format\",\"success\":\"false\"}", "application/json ");
       return 0;
   }
  
   //sending data to Db
   
   sql<<"INSERT INTO todo(event,date)VALUES(:event,:date)",soci::use(eventName),soci::use(eventDate);

  res.status = 200;
       res.set_content("{\"message\": \"Todo Entry Created Successfully\",\"success\":\"true\"}", "application/json ");
       return 0 ;

});

svr.Get("/getTodo", [&](const Request& req, Response& res) {
  try{
    // Fetching all todos
    const soci::rowset<soci::row> results = (sql.prepare << "SELECT * FROM todo");
    nlohmann::json response_json = nlohmann::json::array();

    // Iteration through the resultset
    for (auto it = results.begin(); it != results.end(); ++it) {
        soci::row const& row = *it;

        
        nlohmann::json ex1;
        ex1["event"] = row.get<std::string>(0);
        ex1["date"] = row.get<std::string>(1);
        response_json.push_back(ex1);
    }

    nlohmann::json responseObj;
    responseObj["data"] = response_json;

    // Convert JSON to string and send the data by using .dump()
    res.status = 200;
    res.set_content(responseObj.dump(), "application/json"); // Convert to string using dump()

    }
    catch(const std::exception& ex){
    cout<<ex.what()<<endl;
       res.set_content("{\"error\": \"Enable to create todo\" ,\"success\": \"false\"}", "application/json ");
      
    } 
    return 0;
});

/********************************delete an todo********************/
svr.Delete("/todoComplete",[&](const Request &req,Response & res){
  // Data doesnt get parsed we need to parse it using json/nolhman
  auto data=req.body;
  cout<<"Request data\n"<<data<<endl;
  
  //parsing a json file to json object
  nlohmann::json jObj=nlohmann::json::parse(data);

   std::string eventName=jObj["event"];
   std::string eventDate=jObj["date"];
    //input dat incomplete
   if(eventName==""||eventDate=="")
   {
        res.status = 400;
       res.set_content("{\"error\": \"Invalid JSON format\",\"success\": \"false\"}", "application/json ");
      
   }
  try{
        sql<<"DELETE FROM todo where event=:eventName AND date=:eventDate",soci::use(eventName),soci::use(eventDate); 
         res.status=200;
               res.set_content("{\"message\": \"removed todo successfully from db.\"}", "application/json ");

        
    }
    catch(const std::exception& ex){
    cout<<ex.what()<<endl;
     res.status=500;
     res.set_content("{\"error\": \"Unable to remove todo from database.\",\"success\": \"false\"}", "application/json ");
    
  }
  return 0;
});

//default page
svr.Get("/",[&](const Request & req,Response & res){
  //homepage
  
  res.set_content("Welcome to home page","text/plain");
});



cout<<"server started at :http://localhost:8080/" <<endl;
svr.listen("0.0.0.0", 8080);

#endif
sql.close();
  }
  catch(const std::exception& ex){
    cout<<ex.what()<<endl;
  }
  return 0;
}
