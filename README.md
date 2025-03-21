<!DOCTYPE html>
<html lang="en">

<body>
  <h1>ESPExpress</h1>
  <p>
    <a href="https://github.com/yourusername/ESPExpress" class="badge">
      <img src="https://img.shields.io/badge/build-passing-brightgreen" alt="Build Status">
    </a>
    <a href="LICENSE" class="badge">
      <img src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License: MIT">
    </a>
    <a href="https://platformio.org" class="badge">
      <img src="https://img.shields.io/badge/PlatformIO-compatible-brightgreen" alt="PlatformIO Compatible">
    </a>
  </p>
  <p>
    <strong>ESPExpress</strong> is a lightweight <strong>back end</strong> C++ framework for ESP microcontrollers that mimics the popular Express.js syntax. It empowers you to rapidly build robust web applications and APIs on embedded devices with minimal overhead.
  </p>
  <hr>

  <div class="section">
    <h2>✨ Features</h2>
    <ul>
      <li><strong>Express.js Inspired API:</strong> Easily define routes for HTTP methods like GET, POST, PUT, DELETE, and OPTIONS.</li>
      <li><strong>Middleware Support:</strong> Chain middleware functions for logging, authentication, and request manipulation.</li>
      <li><strong>Static File Serving:</strong> Serve files directly from SPIFFS with automatic content type detection.</li>
      <li><strong>Template Rendering:</strong> Render dynamic HTML pages using a simple templating engine with variable substitution.</li>
      <li><strong>CORS Handling:</strong> Built-in support for cross-origin resource sharing (CORS) for seamless API integrations.</li>
    </ul>
  </div>

  <div class="section">
    <h2>🚀 Quick Start</h2>
    <h3>Installation</h3>
    <p>Clone the repository and add ESPExpress to your PlatformIO project:</p>
    <pre><code>git clone https://github.com/yourusername/ESPExpress.git</code></pre>
    <p>Then, structure your project as follows:</p>
    <pre><code>your_project/
├── lib/
│   └── ESPExpress/
│       ├── src/
│       │   ├── ESPExpress.cpp
│       │   └── ESPExpress.h
│       └── library.json
└── src/
    └── main.cpp</code></pre>
    
    <h3>Example Code</h3>
    <p>Here's a minimal example to get your ESPExpress server up and running:</p>
    <pre><code>#include &lt;WiFi.h&gt;
#include &lt;SPIFFS.h&gt;
#include "ESPExpress.h"

// Replace with your WiFi credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Create an instance of the ESPExpress server on port 80
ESPExpress app(80);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi
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

  // Serve the index.html file on the root "/"
  app.get("/", [](Request &req, Response &res) {
    res.sendFile("/www/index.html");
  });

  // Additional routes
  app.get("/user/:id", [](Request &req, Response &res) {
    String userId = req.getParam("id");
    res.send("&lt;h1&gt;User Profile&lt;/h1&gt;&lt;p&gt;User ID: " + userId + "&lt;/p&gt;");
  });

  // Start the server
  app.listen("Server is running...");
}

void loop() {
  // The server runs in a loop inside app.listen(), no need for code here.
}</code></pre>
  </div>

  <div class="section">
    <h2>📚 Documentation</h2>
    <p>For detailed documentation on all functions, middleware, routing, and configuration options, please visit our <a href="https://github.com/yourusername/ESPExpress/wiki">Wiki</a> or refer to the inline comments in the source code.</p>
  </div>

  <div class="section">
    <h2>🤝 Contributing</h2>
    <p>Contributions are welcome! To contribute to ESPExpress:</p>
    <ol>
      <li><strong>Fork</strong> the repository.</li>
      <li>Create a new branch for your feature or bug fix:
        <pre><code>git checkout -b feature/YourFeature</code></pre>
      </li>
      <li>Commit your changes:
        <pre><code>git commit -am 'Add new feature'</code></pre>
      </li>
      <li>Push to your branch:
        <pre><code>git push origin feature/YourFeature</code></pre>
      </li>
      <li>Open a <strong>Pull Request</strong> on GitHub.</li>
    </ol>
  </div>

  <div class="section">
    <h2>📝 License</h2>
    <p>This project is licensed under the MIT License. See the <a href="LICENSE">LICENSE</a> file for details.</p>
  </div>

  <div class="section">
    <h2>📞 Contact</h2>
    <p>For support, questions, or suggestions, please <a href="https://github.com/yourusername/ESPExpress/issues">open an issue</a> or contact <a href="mailto:your.email@example.com">your.email@example.com</a>.</p>
  </div>

  <hr>
  <p>Happy coding with ESPExpress, and build amazing back end applications on your ESP microcontrollers!</p>
</body>
</html>
