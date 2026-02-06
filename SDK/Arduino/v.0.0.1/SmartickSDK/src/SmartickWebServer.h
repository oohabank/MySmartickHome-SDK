#ifndef SMARTICKWEBSERVER_H
#define SMARTICKWEBSERVER_H

#include <ESP8266WebServer.h>
#include <WiFiManager.h>

class SmartickWebServer {
private:
    ESP8266WebServer* server;
    WiFiManager* wifiManager;
    
    String deviceName;
    String deviceType;
    String deviceModel;
    String deviceID;
    
    // Callback функции
    std::function<void(const String&)> onConfigSave;
    std::function<void()> onReset;
    
public:
    SmartickWebServer();
    ~SmartickWebServer();
    
    void begin(const String& name, const String& type, 
               const String& model, const String& id);
    void handleClient();
    
    void setOnConfigSave(std::function<void(const String&)> callback) {
        onConfigSave = callback;
    }
    
    void setOnReset(std::function<void()> callback) {
        onReset = callback;
    }
    
    // API endpoints
    void addAPIEndpoint(const String& endpoint, 
                       std::function<void(ESP8266WebServer*)> handler);
    
private:
    void setupRoutes();
    void handleRoot();
    void handleConfig();
    void handleReset();
    void handleAPIInfo();
    void handleAPIControl();
    
    String getHTMLTemplate();
};

#endif