#ifndef SMARTICKEFFECTS_H
#define SMARTICKEFFECTS_H

#include <FastLED.h>

class SmartickEffects {
protected:
    CRGB* leds;
    uint16_t numLeds;
    uint8_t matrixWidth;
    uint8_t matrixHeight;
    
public:
    SmartickEffects(CRGB* ledArray, uint16_t count, 
                   uint8_t width = 0, uint8_t height = 0);
    
    // Базовые эффекты
    void solid(CRGB color);
    void fade(uint8_t amount);
    void rainbow(uint8_t speed);
    void breath(CRGB color, uint8_t speed);
    void twinkle(uint8_t density, uint8_t speed);
    void runningLights(uint8_t speed, CRGB color);
    
    // Матричные эффекты
    void matrixRain(uint8_t speed, CRGB color);
    void fire(uint8_t cooling, uint8_t sparking);
    void plasma(uint8_t speed);
    void snow(uint8_t density, uint8_t speed);
    
    // Вспомогательные функции
    uint16_t XY(uint8_t x, uint8_t y);
    void clear();
    
private:
    uint8_t hue;
    uint32_t lastUpdate;
    
    // Внутренние функции
    void coolDown(uint8_t* heat, uint8_t cooling);
    void spreadHeat(uint8_t* heat, uint16_t size);
};

#endif