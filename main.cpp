#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// SD card CS pin
#define CS_PIN 5

// Web server on port 80
WebServer server(80);

// Function to guess MIME type
String getContentType(String filename) {
  if (filename.endsWith(".htm") || filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".jpg") || filename.endsWith(".jpeg")) return "image/jpeg";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  return "text/plain";
}

// Serve file or directory
bool handleFile(String path) {
  Serial.println("Request path: " + path);

  // Default to index.html if directory is requested
  if (path.endsWith("/")) path += "index.html";

  File file = SD.open(path);
  if (!file || file.isDirectory()) {
    return false;
  }

  String contentType = getContentType(path);
  server.streamFile(file, contentType);
  file.close();
  return true;
}

// Main request handler
void handleNotFound() {
  if (!handleFile(server.uri())) {
    server.send(404, "text/plain", "404: File Not Found");
  }
}

void setup() {
  Serial.begin(115200);

  // Init SD card
  if (!SD.begin(CS_PIN)) {
    Serial.println("SD Card Mount Failed!");
    return;
  }
  Serial.println("SD card initialized.");

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Route all requests to SD handler
  server.onNotFound(handleNotFound);

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
