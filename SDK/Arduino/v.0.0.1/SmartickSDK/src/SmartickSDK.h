#ifndef SMARTICKSDK_H
#define SMARTICKSDK_H

#include "SmartickDevice.h"
#include "SmartickConfig.h"
#include "SmartickWebServer.h"
#include "SmartickEffects.h"

// Вспомогательные макросы для быстрого старта
#define SMARTICK_BEGIN(device) device.begin()
#define SMARTICK_LOOP(device) device.loop()

// Макрос для создания устройства
#define CREATE_SMARTICK_DEVICE(type, model, version) \
    SmartickDevice device(type, model, version)

#endif