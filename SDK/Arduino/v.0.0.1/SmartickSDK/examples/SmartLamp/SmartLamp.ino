#include <SmartickSDK.h>
#include <FastLED.h>

#define LED_PIN 2
#define NUM_LEDS 256

CRGB leds[NUM_LEDS];

class SmartLamp : public SmartickDevice {
private:
    SmartickEffects* effects;
    uint8_t currentEffect = 0;
    
public:
    SmartLamp() : SmartickDevice("SmartLamp", "Matrix16x16", "1.0") {
        effects = new SmartickEffects(leds, NUM_LEDS, 16, 16);
    }
    
    ~SmartLamp() {
        delete effects;
    }
    
    void begin() override {
        // Инициализация LED
        FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
        FastLED.setBrightness(100);
        
        // Вызов родительского begin()
        SmartickDevice::begin();
        
        Serial.println("SmartLamp initialized");
    }
    
    void loop() override {
        SmartickDevice::loop();
        
        // Обновление эффектов
        if (getState().power) {
            updateEffect();
            FastLED.show();
        } else {
            effects->clear();
            FastLED.show();
        }
    }
    
protected:
    void onCommand(const String& cmd, const JsonDocument& data) override {
        if (cmd == "power") {
            bool state = data["value"];
            setPower(state);
        }
        else if (cmd == "brightness") {
            uint8_t brightness = data["value"];
            setBrightness(brightness);
            FastLED.setBrightness(brightness);
        }
        else if (cmd == "effect") {
            currentEffect = data["value"];
        }
        else if (cmd == "color") {
            uint8_t r = data["r"];
            uint8_t g = data["g"];
            uint8_t b = data["b"];
            setColor((r << 16) | (g << 8) | b);
        }
    }
    
    void createCustomInfo(JsonDocument& doc) override {
        doc["effects_count"] = 10;
        JsonArray effectsArray = doc.createNestedArray("effects");
        effectsArray.add("Solid");
        effectsArray.add("Rainbow");
        effectsArray.add("Fire");
        effectsArray.add("Twinkle");
        effectsArray.add("Breath");
    }
    
    void createCustomState(JsonDocument& doc) override {
        doc["effect"] = currentEffect;
    }
    
private:
    void updateEffect() {
        switch(currentEffect) {
            case 0: // Solid
                effects->solid(CRGB(getState().color));
                break;
            case 1: // Rainbow
                effects->rainbow(getState().speed);
                break;
            case 2: // Twinkle
                effects->twinkle(30, getState().speed);
                break;
            default:
                effects->solid(CRGB::White);
                break;
        }
    }
};

SmartLamp lamp;

void setup() {
    lamp.begin();
}

void loop() {
    lamp.loop();
}