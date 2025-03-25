#include "routeExamples.h"

void registerRouteExamples(ESPExpress &app) {
  // Serve a simple welcome page on the root "/"
  app.get("/", [](Request &req, Response &res) {
    res.send(R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Welcome to ESPExpress</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
        }
        .welcome-container {
            text-align: center;
            background-color: white;
            padding: 2rem;
            border-radius: 10px;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }
        h1 {
            color: #333;
        }
    </style>
</head>
<body>
    <div class="welcome-container">
        <h1>Welcome to ESPExpress</h1>
        <p>Your lightweight web server is up and running!</p>
    </div>
</body>
</html>
)");
  });

  // Rest of the route handlers remain the same as in the previous example
  app.get("/user/:id", [](Request &req, Response &res) {
    String userId = req.getParam("id");
    res.send("<h1>User Profile</h1><p>User ID: " + userId + "</p>");
  });

  app.post("/data", [](Request &req, Response &res) {
    res.send("<h1>POST Data Received</h1><p>Body: " + req.body + "</p>");
  });

  app.put("/update", [](Request &req, Response &res) {
    res.send("<h1>PUT Update</h1><p>Update data: " + req.body + "</p>");
  });

  app.del("/delete", [](Request &req, Response &res) {
    res.send("<h1>DELETE Request</h1><p>Resource deleted.</p>");
  });

  app.options("/test", [](Request &req, Response &res) {
    res.status(204).end();  // No Content response
  });

  app.get("/template", [&app](Request &req, Response &res) {
    std::map<String, String> vars;
    vars["title"] = "ESPExpress Template";
    vars["message"] = "Hello from a rendered template!";
    app.render(res, "/www/template.html", vars);
  });

  app.serveStatic("/static", "/www");
}