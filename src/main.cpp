#include <WiFi.h>
#include <SPIFFS.h>
#include "ESPExpress.h"

// Replace with your WiFi credentials
const char* ssid = "Tenda1200";
const char* password = "78787878";

// Create an instance of the ESPExpress server on port 80
ESPExpress app(80);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize SPIFFS for static file serving and template rendering
  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount SPIFFS");
    return;
  }
  
  // -------------------------
  // Middleware Example
  // -------------------------
  // Log every request to the Serial Monitor.
  app.use([](Request &req, Response &res, std::function<void()> next) {
    Serial.print("Request received for: ");
    Serial.println(req.path);
    next();
  });
  
  // -------------------------
  // Enable CORS
  // -------------------------
  // Allow any origin (you can change "*" to a specific domain if needed)
  app.enableCORS("*");
  
  // -------------------------
  // Route Definitions
  // -------------------------
  
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
  
  // -------------------------
  // Static File Serving
  // -------------------------
  // Map URL path "/static" to SPIFFS folder "/www"
  // For example, a file located at /www/info.html will be available at http://<device_ip>/static/info.html
  app.serveStatic("/static", "/www");
  
  // -------------------------
  // Template Rendering
  // -------------------------
  // GET route that renders a template located at "/www/template.html" on SPIFFS.
  // The template file should include placeholders in the form {{title}} and {{message}}.
  app.get("/template", [](Request &req, Response &res) {
    std::map<String, String> vars;
    vars["title"] = "ESPExpress Template";
    vars["message"] = "Hello from a rendered template!";
    app.render(res, "/www/template.html", vars);
  });
  
  // -------------------------
  // Start the server
  // -------------------------
  Serial.println("Starting ESPExpress server...");
  app.listen("Server is running...");
}

void loop() {
  // Nothing here because the server runs in an infinite loop inside app.listen()
}
