#include "./config_item.h"

ConfigItem::ConfigItem(configs config_type, String title, byte is_selected) {
    this->config_type = config_type;
    this->title = title;
    this->is_selected = is_selected;
}