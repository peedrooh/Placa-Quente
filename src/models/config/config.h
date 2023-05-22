#ifndef CONFIG_H
#define CONFIG_H

#include <U8g2lib.h>

class ConfigItem {
    public:
        ConfigItem(String title, byte is_selected);
        String title;
        byte is_selected;
};

class Config {
    public:
        void draw_config_menu(U8G2 &u8g2, int current_config);
        void draw_config_selector(U8G2 &u8g2, int current_config, int current_item);
        ConfigItem config_items[3][3] = {
            {ConfigItem("Celcius", 1), ConfigItem("Fahrenheit", 0), ConfigItem("Kelvin", 0)},
            {ConfigItem("Ciclos Completos", 1), ConfigItem("Dimmer", 0), ConfigItem("", 0)},
            {ConfigItem("Padrao", 1), ConfigItem("Rapido", 0), ConfigItem("Estavel", 0)}
        };
    private:
        void _draw_header(U8G2 &u8g2, byte header_type);
        void _draw_scroll_bar(U8G2 &u8g2, int current_config);
        void _draw_config_menu_items(U8G2 &u8g2, int current_config);
        const char * _items_titles[4] = {
            "Unidade de Temperatura",
            "Tipo de Acionamento",
            "Parametros PID",
            "",
        };

};

#endif