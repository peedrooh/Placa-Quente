#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include "FS.h"
#include "SPIFFS.h"
#include "./config_item.h"

/* You only need to format SPIFFS the first time you run a
   test or else use the SPIFFS plugin to create a partition
   https://github.com/me−no−dev/arduino−esp32fs−plugin */
#define FORMAT_SPIFFS_IF_FAILED true

class ConfigFile {
    public:
        void begin();
        static const int NUM_CONF_ROWS = 3;
        static const int NUM_CONF_COLS = 3;
        ConfigItem *get_configs(configs config_index);
        const String *get_configs_titles();
        void update_config(ConfigItem &config_item, byte updated_config_value);
        void _read_file(const char * path);
        const char *_file_name = "/configurations.txt"; 
        void _delete_file(const char * path);
    
    private:
        fs::SPIFFSFS _spiffs;
        const String _configs_titles[NUM_CONF_COLS] = {
            "Unidade de Temperatura",
            "Tipo de Acionamento",
            "Parametros PID"
        };
        ConfigItem _config_items[NUM_CONF_ROWS][NUM_CONF_COLS] = {
            {ConfigItem(temp_config, "Celcius", 1), ConfigItem(temp_config, "Fahrenheit", 0), ConfigItem(temp_config, "Kelvin", 0)}, 
            {ConfigItem(load_control, "Ciclos Completos", 1), ConfigItem(load_control, "Dimmer", 0), ConfigItem(load_control, "", 0)}, 
            {ConfigItem(pid, "Padrao", 1), ConfigItem(pid, "Rapido", 0), ConfigItem(pid, "Suave", 0)}
        };
        void _list_dir(const char * dirname, uint8_t levels );
        void _write_file(const char * path, const char * message);
        void _append_file(const char * path, const char * message);
        void _rename_file(const char * path1, const char * path2);
        void _test_file_IO(const char * path);
};

#endif