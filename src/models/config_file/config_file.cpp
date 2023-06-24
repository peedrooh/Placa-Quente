#include "config_file.h"


void ConfigFile::begin() {
    if(!this->_spiffs.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    
    if(!this->_spiffs.exists(this->_file_name)) {
        this->_spiffs.open(this->_file_name, FILE_WRITE);
        const String *titles = this->get_configs_titles();
        char all_config[1000];
        uint16_t all_config_index = 0;
        for(int i = 0; i < this->NUM_CONF_ROWS; i++) {
            for(int j = 0; j < strlen(titles[i].c_str()); j++) {
                all_config[all_config_index] = titles[i][j];
                all_config_index++;
            }
            all_config[all_config_index] = '\n';
            all_config_index++;
            for(int j = 0; j < this->NUM_CONF_COLS; j++) {
                // Add config type
                all_config[all_config_index] = this->_config_items[i][j].config_type + 48;
                all_config_index++;
                all_config[all_config_index] = ' '; // Add space
                all_config_index++;
                for(int k = 0; k < strlen(this->_config_items[i][j].title.c_str()); k++) {
                    all_config[all_config_index] = this->_config_items[i][j].title.c_str()[k];
                    all_config_index++;
                } // Add title
                all_config[all_config_index] = ' '; // Add space
                all_config_index++;
                // Add attribute
                all_config[all_config_index] = this->_config_items[i][j].is_selected + 48;
                all_config_index++;
                all_config[all_config_index] = '\n'; // Skip line
                all_config_index++;
            }
        }
        File file = this->_spiffs.open(this->_file_name, FILE_WRITE);
        for(int i = 0; i < all_config_index; i++) {
            file.print(all_config[i]);
        }
    }

}

ConfigItem *ConfigFile::get_configs(configs config_index) {
    return this->_config_items[config_index];
}

const String *ConfigFile::get_configs_titles() {
    return this->_configs_titles;
}

void ConfigFile::update_config(ConfigItem &config_item, byte updated_config_value) {
    config_item.is_selected = updated_config_value;
    File file = this->_spiffs.open(this->_file_name, FILE_READ);
    size_t file_size = file.size();
    Serial.println(file_size);
    if(!file || file.isDirectory()){
        return;
    }

    char all_config[file_size+10];
    uint16_t all_config_index = 0;
    char line[50];
    uint16_t line_index = 0;
    bool is_next_line = false;
    while(all_config_index < file_size - 1) {
        int letter = file.read();

        if(letter == 10) {
            line[line_index] = '\n';
            if(
                line[2] == config_item.title[0]
            ) {
                for(int i = 0; i < line_index - 1; i++) {
                    all_config[all_config_index] = line[i];
                    all_config_index++;
                }
                // Add config state
                all_config[all_config_index] = updated_config_value + 48; 
                all_config_index++;
                all_config[all_config_index] = '\n'; 
                all_config_index++;

            } else {
                for(int i = 0; i <= line_index; i++) {
                    all_config[all_config_index] = line[i];
                    all_config_index++;
                }
            }

            line_index = 0;
        } else {
            line[line_index] = letter;
            line_index++;
        }


    }
    // Write configs
    file = this->_spiffs.open(this->_file_name, FILE_WRITE);
    for(int i = 0; i < all_config_index; i++) {
        // Serial.print(all_config[i]);
        file.print(all_config[i]);
    }
}

void ConfigFile::_list_dir(const char * dirname, uint8_t levels) {
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = this->_spiffs.open(dirname);
    if(!root){
        Serial.println("− failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" − not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                this->_list_dir(file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void ConfigFile::_read_file(const char * path){
    Serial.printf("Reading file: %s\r\n", path);

    File file = this->_spiffs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("− failed to open file for reading");
        return;
    }

    Serial.println("− read from file:");
    while(file.available()){
        int x = file.read();
        Serial.write(x);
    }
}

void ConfigFile::_write_file(const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = this->_spiffs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("− failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("− file written");
    }else {
        Serial.println("− frite failed");
    }
}

void ConfigFile::_append_file(const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);

    File file = this->_spiffs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("− failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("− message appended");
    } else {
        Serial.println("− append failed");
    }
}

void ConfigFile::_rename_file(const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\r\n", path1, path2);
    if (this->_spiffs.rename(path1, path2)) {
        Serial.println("− file renamed");
    } else {
        Serial.println("− rename failed");
    }
}

void ConfigFile::_delete_file(const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(this->_spiffs.remove(path)){
        Serial.println("− file deleted");
    } else {
        Serial.println("− delete failed");
    }
}


void ConfigFile::_test_file_IO(const char * path) {
    Serial.printf("Testing file I/O with %s\r\n", path);

    static uint8_t buf[512];
    size_t len = 0;
    File file = this->_spiffs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("− failed to open file for writing");
        return;
    }

    size_t i;
    Serial.print("− writing" );
    uint32_t start = millis();
    for(i=0; i<2048; i++){
        if ((i & 0x001F) == 0x001F){
            Serial.print(".");
        }
        file.write(buf, 512);
    }
    Serial.println("");
    uint32_t end = millis() - start;
    Serial.printf(" − %u bytes written in %u ms\r\n", 2048 * 512, end);
    file.close();

    file = this->_spiffs.open(path);
    start = millis();
    end = start;
    i = 0;
    if(file && !file.isDirectory()){
        len = file.size();
        size_t flen = len;
        start = millis();
        Serial.print("− reading" );
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            if ((i++ & 0x001F) == 0x001F){
                Serial.print(".");
            }
            len = len - toRead;
        }
        Serial.println("");
        end = millis() - start;
        Serial.printf("- %u bytes read in %u ms\r\n", flen, end);
        file.close();
    } else {
        Serial.println("- failed to open file for reading");
    }
}