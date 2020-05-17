#ifndef __config_h
#define __config_h

#include "defs.h"
#include <stdint.h>

#define CONFIG_MAX_VALUES 32

typedef struct _config {
    int32_t     integer[CONFIG_MAX_VALUES];
    float       floats[CONFIG_MAX_VALUES];
    BOOL        booleans[CONFIG_MAX_VALUES];
} Config;

BOOL config_load(Config *config, const char *data, uint32_t length);

int32_t config_get_integer(Config* config, uint32_t id);
BOOL config_get_boolean(Config* config, uint32_t id);
float config_get_float(Config* config, uint32_t id);

Config G_CONFIG;

#endif  /* __config_h */