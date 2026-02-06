#include "SmartickDevice.h"

SmartickDevice::SmartickDevice(const String& type, const String& model, const String& version) {
    // Генерация уникального ID
    deviceID = "SMARTICK-" + String(ESP.getChipId(), HEX);
    deviceType = type;
    deviceModel = model;
    firmwareVersion = version;
    deviceName = deviceType + " " + String(ESP.getChipId(), HEX);
    
    // Настройки по умолчанию
    mqttServer = "broker.hivemq.com";
    mqttPort = 1883;
    mqttUser = "";
    mqttPass = "";
    
    autosave = true;
    webConfigEnabled = true;
    lastReconnectAttempt = 0;
    lastStateSend = 0;
    
    webServer = nullptr;
    
    // Инициализация состояния
    state.power = true;
    state.brightness = 100;
    state.color = 0xFFFFFF;
    state.speed = 50;
    
    // Топики
    topicInfo = "smartick/" + deviceID + "/info";
    topicCmd = "smartick/" + deviceID + "/cmd";
    topicState = "smartick/" + deviceID + "/state";
    topicDiscovery = "smartick/discovery";
}

SmartickDevice::~SmartickDevice() {
    if (webServer) {
        delete webServer;
    }
}

void SmartickDevice::begin() {
    Serial.begin(115200);
    Serial.println("\n=== SMARTICK DEVICE ===");
    Serial.println("ID: " + deviceID);
    Serial.println("Type: " + deviceType);
    Serial.println("Model: " + deviceModel);
    Serial.println("Version: " + firmwareVersion);
    
    // Загрузка настроек
    loadSettings();
    
    // Настройка WiFi
    setupWiFi();
    
    // Настройка MQTT
    setupMQTT();
    
    // Настройка веб-сервера
    if (webConfigEnabled) {
        setupWebServer();
    }
    
    Serial.println("Device initialized successfully!");
    Serial.println("IP: " + WiFi.localIP().toString());
    Serial.println("MQTT Server: " + mqttServer + ":" + String(mqttPort));
}

void SmartickDevice::loop() {
    // Обслуживание MQTT
    if (!mqttClient.connected()) {
        reconnectMQTT();
    }
    if (mqttClient.connected()) {
        mqttClient.loop();
    }
    
    // Обслуживание веб-сервера
    if (webServer && webConfigEnabled) {
        webServer->handleClient();
    }
    
    // Периодическая отправка состояния
    if (millis() - lastStateSend > 30000) { // Каждые 30 секунд
        sendDeviceState();
        lastStateSend = millis();
    }
}

void SmartickDevice::setupWiFi() {
    WiFiManagerParameter custom_name("name", "Device Name", deviceName.c_str(), 32);
    wifiManager.addParameter(&custom_name);
    
    wifiManager.setAPCallback([](WiFiManager* mgr) {
        Serial.println("Entered configuration mode");
        Serial.println("Connect to WiFi: Smartick-Config");
        Serial.println("Then open: 192.168.4.1");
    });
    
    if (!wifiManager.autoConnect("Smartick-Config")) {
        Serial.println("Failed to connect to WiFi");
        delay(3000);
        ESP.restart();
    }
    
    deviceName = custom_name.getValue();
    Serial.println("WiFi connected!");
    Serial.println("SSID: " + WiFi.SSID());
    Serial.println("IP: " + WiFi.localIP().toString());
}

void SmartickDevice::setupMQTT() {
    mqttClient.setClient(wifiClient);
    mqttClient.setServer(mqttServer.c_str(), mqttPort);
    mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->mqttCallback(topic, payload, length);
    });
    
    Serial.println("MQTT configured");
}

void SmartickDevice::setupWebServer() {
    webServer = new ESP8266WebServer(80);
    
    webServer->on("/", HTTP_GET, [this]() {
        String html = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Smartick Device</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; background: #f0f0f0; }
        .container { max-width: 500px; margin: 0 auto; background: white; padding: 20px; border-radius: 10px; }
        h1 { color: #667eea; }
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
            <p><strong>Version:</strong> )=====" + firmwareVersion + R"=====(</p>
            <p><strong>IP:</strong> )=====" + WiFi.localIP().toString() + R"=====(</p>
            <p><strong>WiFi RSSI:</strong> )=====" + String(WiFi.RSSI()) + R"=====( dBm</p>
        </div>
        <p>This device is part of the Smartick ecosystem.</p>
    </div>
</body>
</html>
)=====";
        
        webServer->send(200, "text/html", html);
    });
    
    webServer->on("/api/info", HTTP_GET, [this]() {
        DynamicJsonDocument doc(512);
        doc["id"] = deviceID;
        doc["name"] = deviceName;
        doc["type"] = deviceType;
        doc["model"] = deviceModel;
        doc["version"] = firmwareVersion;
        doc["ip"] = WiFi.localIP().toString();
        doc["rssi"] = WiFi.RSSI();
        
        String response;
        serializeJson(doc, response);
        webServer->send(200, "application/json", response);
    });
    
    webServer->on("/api/state", HTTP_GET, [this]() {
        DynamicJsonDocument doc(256);
        doc["power"] = state.power;
        doc["brightness"] = state.brightness;
        doc["color"] = state.color;
        doc["speed"] = state.speed;
        
        String response;
        serializeJson(doc, response);
        webServer->send(200, "application/json", response);
    });
    
    webServer->on("/api/control", HTTP_POST, [this]() {
        if (webServer->hasArg("plain")) {
            String body = webServer->arg("plain");
            DynamicJsonDocument doc(256);
            DeserializationError error = deserializeJson(doc, body);
            
            if (!error) {
                onCommand("web", doc);
                webServer->send(200, "application/json", "{\"status\":\"ok\"}");
            } else {
                webServer->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
            }
        } else {
            webServer->send(400, "application/json", "{\"error\":\"No data\"}");
        }
    });
    
    webServer->begin();
    Serial.println("Web server started on port 80");
}

void SmartickDevice::reconnectMQTT() {
    if (millis() - lastReconnectAttempt < 5000) {
        return;
    }
    
    lastReconnectAttempt = millis();
    Serial.print("Connecting to MQTT...");
    
    if (mqttClient.connect(deviceID.c_str(), mqttUser.c_str(), mqttPass.c_str())) {
        Serial.println("connected!");
        
        // Подписываемся на топики
        mqttClient.subscribe(topicCmd.c_str());
        mqttClient.subscribe("smartick/all/cmd");
        
        // Отправляем информацию
        sendDeviceInfo();
        sendDiscovery();
        
        onConnect();
        if (connectHandler) {
            connectHandler();
        }
    } else {
        Serial.print("failed, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" try again in 5 seconds");
    }
}

void SmartickDevice::mqttCallback(char* topic, byte* payload, unsigned int length) {
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';
    
    Serial.print("MQTT message [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.println(message);
    
    DynamicJsonDocument doc(256);
    DeserializationError error = deserializeJson(doc, message);
    
    if (error) {
        Serial.print("JSON parse error: ");
        Serial.println(error.c_str());
        return;
    }
    
    if (doc.containsKey("cmd")) {
        String command = doc["cmd"].as<String>();
        onCommand(command, doc);
        
        if (commandHandler) {
            commandHandler(command, doc);
        }
        
        // Сохраняем настройки если включен автосейв
        if (autosave) {
            saveSettings();
        }
        
        // Отправляем обновленное состояние
        sendDeviceState();
    }
}

void SmartickDevice::sendDeviceInfo() {
    DynamicJsonDocument doc(1024);
    
    doc["device"] = deviceType;
    doc["id"] = deviceID;
    doc["name"] = deviceName;
    doc["model"] = deviceModel;
    doc["version"] = firmwareVersion;
    doc["ip"] = WiFi.localIP().toString();
    doc["rssi"] = WiFi.RSSI();
    
    // Добавляем пользовательские данные
    createCustomInfo(doc);
    
    String output;
    serializeJson(doc, output);
    
    mqttClient.publish(topicInfo.c_str(), output.c_str());
    Serial.println("Device info sent");
}

void SmartickDevice::sendDeviceState() {
    DynamicJsonDocument doc(512);
    
    doc["id"] = deviceID;
    doc["power"] = state.power;
    doc["brightness"] = state.brightness;
    doc["color"] = state.color;
    doc["speed"] = state.speed;
    doc["rssi"] = WiFi.RSSI();
    
    // Добавляем пользовательские данные
    createCustomState(doc);
    
    String output;
    serializeJson(doc, output);
    
    mqttClient.publish(topicState.c_str(), output.c_str());
    Serial.println("Device state sent");
}

void SmartickDevice::sendCustomData(const String& topic, const JsonDocument& data) {
    String output;
    serializeJson(data, output);
    
    mqttClient.publish(topic.c_str(), output.c_str());
    Serial.println("Custom data sent to topic: " + topic);
}

void SmartickDevice::sendDiscovery() {
    sendDeviceInfo();
    mqttClient.publish(topicDiscovery.c_str(), deviceID.c_str());
}

void SmartickDevice::saveSettings() {
    SavedConfig config;
    
    strncpy(config.deviceName, deviceName.c_str(), sizeof(config.deviceName));
    config.power = state.power;
    config.brightness = state.brightness;
    config.color = state.color;
    config.speed = state.speed;
    
    // Расчет контрольной суммы
    config.checksum = 0;
    uint8_t* data = (uint8_t*)&config;
    for (size_t i = 0; i < sizeof(SavedConfig) - 1; i++) {
        config.checksum ^= data[i];
    }
    
    EEPROM.begin(sizeof(SavedConfig));
    EEPROM.put(0, config);
    
    // Сохраняем пользовательские настройки
    DynamicJsonDocument customDoc(256);
    saveCustomSettings(customDoc);
    String customData;
    serializeJson(customDoc, customData);
    
    // Записываем пользовательские данные в EEPROM
    size_t offset = sizeof(SavedConfig);
    for (size_t i = 0; i < customData.length(); i++) {
        if (offset + i < 512) { // Ограничиваем размер EEPROM
            EEPROM.write(offset + i, customData[i]);
        }
    }
    if (offset + customData.length() < 512) {
        EEPROM.write(offset + customData.length(), '\0');
    }
    
    EEPROM.commit();
    EEPROM.end();
    
    Serial.println("Settings saved to EEPROM");
}

void SmartickDevice::loadSettings() {
    SavedConfig config;
    
    EEPROM.begin(sizeof(SavedConfig));
    EEPROM.get(0, config);
    
    // Проверка контрольной суммы
    uint8_t checksum = 0;
    uint8_t* data = (uint8_t*)&config;
    for (size_t i = 0; i < sizeof(SavedConfig) - 1; i++) {
        checksum ^= data[i];
    }
    
    if (checksum == config.checksum) {
        deviceName = String(config.deviceName);
        state.power = config.power;
        state.brightness = config.brightness;
        state.color = config.color;
        state.speed = config.speed;
        
        // Загружаем пользовательские настройки
        size_t offset = sizeof(SavedConfig);
        String customData;
        char ch = EEPROM.read(offset);
        while (ch != '\0' && offset < 512) {
            customData += ch;
            offset++;
            ch = EEPROM.read(offset);
        }
        
        if (customData.length() > 0) {
            DynamicJsonDocument customDoc(256);
            DeserializationError error = deserializeJson(customDoc, customData);
            if (!error) {
                loadCustomSettings(customDoc);
            }
        }
        
        Serial.println("Settings loaded from EEPROM");
    } else {
        Serial.println("Invalid EEPROM checksum, using default settings");
    }
    
    EEPROM.end();
}

// Виртуальные методы (по умолчанию пустые)
void SmartickDevice::onConnect() {}
void SmartickDevice::onDisconnect() {}
void SmartickDevice::onCommand(const String& cmd, const JsonDocument& data) {}
void SmartickDevice::onWebRequest(ESP8266WebServer* server) {}
void SmartickDevice::saveCustomSettings(JsonDocument& doc) {}
void SmartickDevice::loadCustomSettings(JsonDocument& doc) {}
void SmartickDevice::createCustomInfo(JsonDocument& doc) {}
void SmartickDevice::createCustomState(JsonDocument& doc) {}

// Setter методы
void SmartickDevice::setDeviceName(const String& name) {
    deviceName = name;
    if (autosave) saveSettings();
}

void SmartickDevice::setMQTTConfig(const String& server, int port, const String& user, const String& pass) {
    mqttServer = server;
    mqttPort = port;
    mqttUser = user;
    mqttPass = pass;
}

void SmartickDevice::setPower(bool powerState) {
    state.power = powerState;
    sendDeviceState();
}

void SmartickDevice::setBrightness(uint8_t brightness) {
    state.brightness = brightness;
    sendDeviceState();
}

void SmartickDevice::setColor(uint32_t color) {
    state.color = color;
    sendDeviceState();
}

void SmartickDevice::setSpeed(uint8_t speed) {
    state.speed = speed;
    sendDeviceState();
}

void SmartickDevice::setCommandHandler(CommandCallback handler) {
    commandHandler = handler;
}

void SmartickDevice::setConnectHandler(ConnectCallback handler) {
    connectHandler = handler;
}

void SmartickDevice::setDisconnectHandler(DisconnectCallback handler) {
    disconnectHandler = handler;
}

void SmartickDevice::enableWebConfig(bool enable) {
    webConfigEnabled = enable;
}

void SmartickDevice::enableAutosave(bool enable) {
    autosave = enable;
}