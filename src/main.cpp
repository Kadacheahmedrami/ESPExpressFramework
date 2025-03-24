#include "ESPExpress.h"
#include <WiFi.h>
#include <SPIFFS.h>
#include "websocket/websocket.h"      // Import WebSocket routes
#include "routeExamples/routeExamples.h"  // Import HTTP route examples

const char* ssid = "Tenda1200";         // WiFi SSID
const char* password = "78787878";      // WiFi password

ESPExpress app(80);                   // Server instance on port 80

void setup() {
  Serial.begin(115200);                // Start serial communication
  delay(1000);
  
  WiFi.begin(ssid, password);          // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: "); 
  Serial.println(WiFi.localIP());

  if (!SPIFFS.begin(true)) {           // Mount SPIFFS
    Serial.println("Failed to mount SPIFFS");
    return;
  }
  
  app.use([](Request &req, Response &res, std::function<void()> next) { // Log request path
    Serial.print("Request received for: "); 
    Serial.println(req.path); 
    next();
  });
  
  app.enableCORS("*");                // Enable CORS for all origins
  
  registerRouteExamples(app);         // Register HTTP route examples
  registerWebSocketRoutes(app);       // Register WebSocket routes
  
  Serial.println("Starting ESPExpress server...");
  app.listen("Server is running..."); // Start the server
}

void loop() {
  app.wsLoop();                       // Process WebSocket events
}
