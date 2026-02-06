#ifndef SMARTICKCONFIG_H
#define SMARTICKCONFIG_H

#include <ArduinoJson.h>

// Версия протокола
#define SMARTICK_PROTOCOL_VERSION "1.0"

// Стандартные команды
enum SmartickCommand {
    CMD_POWER = 0,
    CMD_BRIGHTNESS,
    CMD_COLOR,
    CMD_SPEED,
    CMD_EFFECT,
    CMD_GET_INFO,
    CMD_GET_STATE,
    CMD_DISCOVER,
    CMD_RESET,
    CMD_CUSTOM
};

// Стандартные топики
const char* SMARTICK_TOPIC_INFO = "smartick/%s/info";
const char* SMARTICK_TOPIC_CMD = "smartick/%s/cmd";
const char* SMARTICK_TOPIC_STATE = "smartick/%s/state";
const char* SMARTICK_TOPIC_DISCOVERY = "smartick/discovery";
const char* SMARTICK_TOPIC_ALL_CMD = "smartick/all/cmd";

// Стандартные параметры
struct SmartickParams {
    uint8_t brightness_min = 0;
    uint8_t brightness_max = 100;
    uint8_t speed_min = 0;
    uint8_t speed_max = 100;
    bool supports_color = true;
    bool supports_effects = true;
    uint8_t effects_count = 0;
};

#endif