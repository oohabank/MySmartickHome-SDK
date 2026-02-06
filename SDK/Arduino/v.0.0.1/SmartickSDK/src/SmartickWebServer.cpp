#include "SmartickWebServer.h"

SmartickWebServer::SmartickWebServer() {
    server = new ESP8266WebServer(80);
    wifiManager = new WiFiManager();
}

SmartickWebServer::~SmartickWebServer() {
    if (server) delete server;
    if (wifiManager) delete wifiManager;
}

void SmartickWebServer::begin(const String& name, const String& type, 
                              const String& model, const String& id) {
    deviceName = name;
    deviceType = type;
    deviceModel = model;
    deviceID = id;
    
    // Настройка WiFiManager
    WiFiManagerParameter custom_name("name", "Device Name", deviceName.c_str(), 32);
    wifiManager->addParameter(&custom_name);
    
    wifiManager->setAPCallback([](WiFiManager* mgr) {
        Serial.println("Entered configuration mode");
    });
    
    // Настройка сервера
    setupRoutes();
    server->begin();
    
    Serial.println("Web server started");
}

void SmartickWebServer::setupRoutes() {
    server->on("/", HTTP_GET, [this]() { handleRoot(); });
    server->on("/config", HTTP_POST, [this]() { handleConfig(); });
    server->on("/reset", HTTP_POST, [this]() { handleReset(); });
    server->on("/api/info", HTTP_GET, [this]() { handleAPIInfo(); });
    server->on("/api/control", HTTP_POST, [this]() { handleAPIControl(); });
}

void SmartickWebServer::handleClient() {
    if (server) {
        server->handleClient();
    }
}

void SmartickWebServer::handleRoot() {
    String html = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Smartick Device Configuration</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; background: #f0f0f0; }
        .container { max-width: 500px; margin: 0 auto; background: white; padding: 20px; border-radius: 10px; }
        h1 { color: #667eea; }
        .form-group { margin: 15px 0; }
        label { display: block; margin-bottom: 5px; font-weight: bold; }
        input { width: 100%; padding: 10px; border: 1px solid #ccc; border-radius: 5px; }
        button { padding: 10px 20px; background: #667eea; color: white; border: none; border-radius: 5px; cursor: pointer; }
        .info { background: #f8fafc; padding: 10px; border-radius: 5px; margin: 10px 0; }
    </style>
</head>
<body>
    <div class="container">
        <h1>)" + deviceName + R"=====(</h1>
        <div class="info">
            <p><strong>Device ID:</strong> )=====" + deviceID + R"=====(</p>
            <p><strong>Type:</strong> )=====" + deviceType + R"=====(</p>
            <p><strong>Model:</strong> )=====" + deviceModel + R"=====(</p>
        </div>
        
        <form action="/config" method="POST">
            <div class="form-group">
                <label>Device Name:</label>
                <input type="text" name="device_name" value=")" + deviceName + R"=====(">
            </div>
            <div class="form-group">
                <label>WiFi SSID:</label>
                <input type="text" name="ssid" required>
            </div>
            <div class="form-group">
                <label>WiFi Password:</label>
                <input type="password" name="password" required>
            </div>
            <button type="submit">Save Configuration</button>
        </form>
        
        <hr>
        <form action="/reset" method="POST">
            <button type="submit" style="background: #dc3545;">Reset to Factory Settings</button>
        </form>
    </div>
</body>
</html>
)=====";
    
    server->send(200, "text/html", html);
}

void SmartickWebServer::handleConfig() {
    if (server->hasArg("ssid") && server->hasArg("password")) {
        String ssid = server->arg("ssid");
        String password = server->arg("password");
        String newName = server->arg("device_name");
        
        if (onConfigSave && newName.length() > 0) {
            onConfigSave(newName);
        }
        
        server->send(200, "text/plain", "Configuration saved. Rebooting...");
        delay(1000);
        ESP.restart();
    } else {
        server->send(400, "text/plain", "Missing parameters");
    }
}

void SmartickWebServer::handleReset() {
    if (onReset) {
        onReset();
    }
    
    server->send(200, "text/plain", "Device reset. Rebooting...");
    delay(1000);
    ESP.restart();
}

void SmartickWebServer::handleAPIInfo() {
    DynamicJsonDocument doc(512);
    
    doc["device"] = deviceType;
    doc["id"] = deviceID;
    doc["name"] = deviceName;
    doc["model"] = deviceModel;
    doc["ip"] = WiFi.localIP().toString();
    doc["rssi"] = WiFi.RSSI();
    
    String response;
    serializeJson(doc, response);
    server->send(200, "application/json", response);
}

void SmartickWebServer::addAPIEndpoint(const String& endpoint, 
                                      std::function<void(ESP8266WebServer*)> handler) {
    server->on(endpoint.c_str(), HTTP_GET, [this, handler]() {
        handler(server);
    });
}