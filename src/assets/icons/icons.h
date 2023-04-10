#ifndef ICONS_H
#define ICONS_H

#include "icon.h"
#include <U8g2lib.h>

extern Icon* all_icons[12];

class Icons {
    public:
        void add_icon();
        int _icons_number;
        Icon* _icons[];
};

#endif