#include "routeExamples.h"

void registerRouteExamples(ESPExpress &app) {
  // Serve the index.html file on the root "/"
  app.get("/", [](Request &req, Response &res) {
    res.sendFile("/www/index.html");
  });

  // GET route with a dynamic parameter: /user/:id
  app.get("/user/:id", [](Request &req, Response &res) {
    String userId = req.getParam("id");
    res.send("<h1>User Profile</h1><p>User ID: " + userId + "</p>");
  });

  // POST route to test receiving a body payload.
  app.post("/data", [](Request &req, Response &res) {
    res.send("<h1>POST Data Received</h1><p>Body: " + req.body + "</p>");
  });

  // PUT route example.
  app.put("/update", [](Request &req, Response &res) {
    res.send("<h1>PUT Update</h1><p>Update data: " + req.body + "</p>");
  });

  // DELETE route example.
  app.del("/delete", [](Request &req, Response &res) {
    res.send("<h1>DELETE Request</h1><p>Resource deleted.</p>");
  });

  // OPTIONS route example (useful for CORS preflight requests).
  app.options("/test", [](Request &req, Response &res) {
    res.status(204).end();  // No Content response
  });

  // Template Rendering: GET /template
  // Capture app by reference so that we can call app.render() inside the lambda.
  app.get("/template", [&app](Request &req, Response &res) {
    std::map<String, String> vars;
    vars["title"] = "ESPExpress Template";
    vars["message"] = "Hello from a rendered template!";
    app.render(res, "/www/template.html", vars);
  });

  // Static File Serving: Map URL path "/static" to SPIFFS folder "/www"
  app.serveStatic("/static", "/www");
}
