#include "SmartickEffects.h"

SmartickEffects::SmartickEffects(CRGB* ledArray, uint16_t count, 
                               uint8_t width, uint8_t height) {
    leds = ledArray;
    numLeds = count;
    matrixWidth = width;
    matrixHeight = height;
    hue = 0;
    lastUpdate = 0;
}

uint16_t SmartickEffects::XY(uint8_t x, uint8_t y) {
    if (matrixWidth == 0 || matrixHeight == 0) {
        return (x + y * matrixWidth) % numLeds;
    }
    
    if (y % 2 == 0) {
        return y * matrixWidth + x;
    } else {
        return y * matrixWidth + (matrixWidth - 1 - x);
    }
}

void SmartickEffects::clear() {
    memset(leds, 0, numLeds * sizeof(CRGB));
}

void SmartickEffects::solid(CRGB color) {
    fill_solid(leds, numLeds, color);
}

void SmartickEffects::fade(uint8_t amount) {
    fadeToBlackBy(leds, numLeds, amount);
}

void SmartickEffects::rainbow(uint8_t speed) {
    if (millis() - lastUpdate > (100 - speed)) {
        lastUpdate = millis();
        fill_rainbow(leds, numLeds, hue, 7);
        hue++;
    }
}

void SmartickEffects::breath(CRGB color, uint8_t speed) {
    static uint8_t breathValue = 0;
    static bool increasing = true;
    
    uint8_t step = map(speed, 0, 100, 1, 10);
    
    if (increasing) {
        breathValue = qadd8(breathValue, step);
        if (breathValue >= 255) increasing = false;
    } else {
        breathValue = qsub8(breathValue, step);
        if (breathValue <= 0) increasing = true;
    }
    
    fill_solid(leds, numLeds, color);
    nscale8(leds, numLeds, breathValue);
}

void SmartickEffects::twinkle(uint8_t density, uint8_t speed) {
    fadeToBlackBy(leds, numLeds, map(speed, 0, 100, 1, 20));
    
    if (millis() - lastUpdate > (100 - speed)) {
        lastUpdate = millis();
        
        if (random8() < density) {
            int pos = random16(numLeds);
            leds[pos] = CHSV(random8(), 255, 255);
        }
    }
}

void SmartickEffects::runningLights(uint8_t speed, CRGB color) {
    static uint8_t position = 0;
    fadeToBlackBy(leds, numLeds, 50);
    
    uint8_t step = map(speed, 0, 100, 1, 10);
    
    for (int i = 0; i < 3; i++) {
        int pos = (position + i * 8) % numLeds;
        leds[pos] = color;
    }
    
    position += step;
}

// Остальные эффекты реализуются аналогично...

void SmartickEffects::coolDown(uint8_t* heat, uint8_t cooling) {
    for (int i = 0; i < numLeds; i++) {
        heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / numLeds) + 2));
    }
}

void SmartickEffects::spreadHeat(uint8_t* heat, uint16_t size) {
    for (int k = size - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }
}