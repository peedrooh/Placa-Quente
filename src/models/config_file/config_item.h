#ifndef CONFIG_ITEM_H
#define CONFIG_ITEM_H

#include <Arduino.h>

enum configs {temp_config, load_control, pid};

class ConfigItem {
    public:
        ConfigItem(configs config_type, String title, byte is_selected);
        configs config_type;
        String title;
        byte is_selected;
};

#endif