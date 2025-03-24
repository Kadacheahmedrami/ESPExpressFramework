#include "websocket.h"

void registerWebSocketRoutes(ESPExpress &app) {
  // Capture app by reference so that we can use it inside the lambda.
  app.ws("/ws", [&app](uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
      case WStype_CONNECTED:
        Serial.printf("WebSocket client #%u connected\n", num);
        break;
      case WStype_DISCONNECTED:
        Serial.printf("WebSocket client #%u disconnected\n", num);
        break;
      case WStype_TEXT:
        Serial.printf("Received text from client #%u: %s\n", num, payload);
        // Echo back the message
        app.wsSendTXT(num, String((char*)payload));
        break;
      default:
        break;
    }
  });
}
