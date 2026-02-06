#include <SmartickSDK.h>

// Создаем устройство
SmartickDevice device("BasicDevice", "Model1", "1.0");

void setup() {
    // Настраиваем обработчики команд
    device.setCommandHandler([](const String& cmd, const JsonDocument& data) {
        Serial.print("Command received: ");
        Serial.println(cmd);
        
        if (cmd == "power") {
            bool state = data["value"];
            device.getState().power = state;
            Serial.println(state ? "Device ON" : "Device OFF");
        }
        else if (cmd == "brightness") {
            uint8_t brightness = data["value"];
            device.getState().brightness = brightness;
            Serial.print("Brightness: ");
            Serial.println(brightness);
        }
        else if (cmd == "color") {
            uint32_t color = data["color"];
            device.getState().color = color;
            Serial.print("Color: 0x");
            Serial.println(color, HEX);
        }
    });
    
    // Настраиваем обработчик подключения
    device.setConnectHandler([]() {
        Serial.println("Connected to MQTT!");
    });
    
    // Запускаем устройство
    device.begin();
}

void loop() {
    device.loop();
    
    // Ваша основная логика здесь
    static unsigned long lastBlink = 0;
    if (device.getState().power && millis() - lastBlink > 1000) {
        Serial.println("Device is working...");
        lastBlink = millis();
    }
}