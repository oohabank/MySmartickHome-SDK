#ifndef SMARTICKDEVICE_H
#define SMARTICKDEVICE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

class SmartickDevice {
public:
    // Структура состояния устройства
    struct DeviceState {
        bool power = true;
        uint8_t brightness = 100;
        uint32_t color = 0xFFFFFF;
        uint8_t speed = 50;
        
        // Дополнительные параметры
        DynamicJsonDocument* customData = nullptr;
        
        DeviceState() : customData(nullptr) {}
        ~DeviceState() {
            if (customData) delete customData;
        }
    };
    
    // Callback типы
    typedef std::function<void(const String&, const JsonDocument&)> CommandCallback;
    typedef std::function<void()> ConnectCallback;
    typedef std::function<void()> DisconnectCallback;
    
    // Конструкторы
    SmartickDevice(const String& type, const String& model, const String& version = "1.0.0");
    virtual ~SmartickDevice();
    
    // Основные методы
    virtual void begin();
    virtual void loop();
    
    // Настройка
    void setDeviceName(const String& name);
    void setMQTTConfig(const String& server, int port = 1883, 
                      const String& user = "", const String& pass = "");
    void enableWebConfig(bool enable = true);
    void enableAutosave(bool enable = true);
    
    // Управление состоянием
    virtual void setPower(bool state);
    virtual void setBrightness(uint8_t brightness);
    virtual void setColor(uint32_t color);
    virtual void setSpeed(uint8_t speed);
    
    // Отправка данных
    virtual void sendDeviceInfo();
    virtual void sendDeviceState();
    void sendCustomData(const String& topic, const JsonDocument& data);
    void sendDiscovery();
    
    // Callback'и
    void setCommandHandler(CommandCallback handler);
    void setConnectHandler(ConnectCallback handler);
    void setDisconnectHandler(DisconnectCallback handler);
    
    // Геттеры
    String getDeviceID() const { return deviceID; }
    String getDeviceName() const { return deviceName; }
    String getDeviceType() const { return deviceType; }
    String getDeviceModel() const { return deviceModel; }
    String getFirmwareVersion() const { return firmwareVersion; }
    String getIPAddress() const { return WiFi.localIP().toString(); }
    bool isConnected() const { return mqttClient.connected(); }
    DeviceState& getState() { return state; }
    
    // EEPROM
    virtual void saveSettings();
    virtual void loadSettings();
    
protected:
    // Виртуальные методы для переопределения
    virtual void onConnect();
    virtual void onDisconnect();
    virtual void onCommand(const String& cmd, const JsonDocument& data);
    virtual void onWebRequest(ESP8266WebServer* server);
    virtual void saveCustomSettings(JsonDocument& doc);
    virtual void loadCustomSettings(JsonDocument& doc);
    virtual void createCustomInfo(JsonDocument& doc);
    virtual void createCustomState(JsonDocument& doc);
    
    // Внутренние переменные
    String deviceID;
    String deviceName;
    String deviceType;
    String deviceModel;
    String firmwareVersion;
    
    DeviceState state;
    
    // Сеть
    WiFiClient wifiClient;
    PubSubClient mqttClient;
    WiFiManager wifiManager;
    ESP8266WebServer* webServer;
    
    // Конфигурация
    String mqttServer;
    int mqttPort;
    String mqttUser;
    String mqttPass;
    
    // Топики
    String topicInfo;
    String topicCmd;
    String topicState;
    String topicDiscovery;
    
    // Callback'и
    CommandCallback commandHandler;
    ConnectCallback connectHandler;
    DisconnectCallback disconnectHandler;
    
    // Флаги
    bool autosave;
    bool webConfigEnabled;
    unsigned long lastReconnectAttempt;
    unsigned long lastStateSend;
    
private:
    void setupWiFi();
    void setupMQTT();
    void setupWebServer();
    void reconnectMQTT();
    void mqttCallback(char* topic, byte* payload, unsigned int length);
    void handleWebRequest();
    
    // Структура для EEPROM
    struct SavedConfig {
        char deviceName[32];
        bool power;
        uint8_t brightness;
        uint32_t color;
        uint8_t speed;
        uint8_t checksum;
    };
};

#endif