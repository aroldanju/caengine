#include "config.h"
#include <memory.h>

BOOL config_load(Config *config, const char *data, uint32_t length) {
    memcpy(config, data, length);
    return TRUE;
}

int32_t config_get_integer(Config* config, uint32_t id) {
    return config->integer[id];
}

BOOL config_get_boolean(Config* config, uint32_t id) {
    return config->booleans[id];
}

float config_get_float(Config* config, uint32_t id) {
    return config->floats[id];
}