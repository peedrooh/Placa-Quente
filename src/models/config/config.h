#ifndef CONFIG_H
#define CONFIG_H

#include <U8g2lib.h>

class Config {
    public:
        void draw_config_menu(U8G2 &u8g2, int current_config);
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