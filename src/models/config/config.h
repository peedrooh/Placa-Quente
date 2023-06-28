#ifndef CONFIG_H
#define CONFIG_H

#include <U8g2lib.h>
#include "models/config_file/config_file.h"

// class ConfigItem {
//     public:
//         ConfigItem(String title, byte is_selected);
//         String title;
//         byte is_selected;
// };

class Config {
    public:
        void draw_config_menu(U8G2 &u8g2, int current_config);
        void draw_config_selector(U8G2 &u8g2, int current_config, int current_item);
        ConfigItem config_items[2][3] = {
            {ConfigItem(temp_config, "Celcius", 1), ConfigItem(temp_config, "Fahrenheit", 0), ConfigItem(temp_config, "", 0)},
            {ConfigItem(load_control, "Ciclos Completos", 1), ConfigItem(load_control, "Dimmer", 0), ConfigItem(load_control, "", 0)}
        };
    private:
        void _draw_header(U8G2 &u8g2, byte header_type);
        void _draw_scroll_bar(U8G2 &u8g2, int current_config);
        void _draw_config_menu_items(U8G2 &u8g2, int current_config);
        const char * _items_titles[3] = {
            "Unidade de Temperatura",
            "Tipo de Acionamento",
            "",
        };

};

#endif