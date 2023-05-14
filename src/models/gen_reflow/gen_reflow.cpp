#include "gen_reflow.h"
#include "assets/headers/headers.h"

#define HEADER_DASHED_BACK 2
#define ANSWER_X_POS 93
#define ANSWER_Y_POS 26

void GenericReflow::draw_confirmation_screen(U8G2 &u8g2, byte is_yes) {
    // Header Draw
    u8g2.setBitmapMode(false);
    u8g2.setDrawColor(1);
    u8g2.drawXBM(0, 0, all_headers[HEADER_DASHED_BACK]->header_width, all_headers[HEADER_DASHED_BACK]->header_height, all_headers[HEADER_DASHED_BACK]->get_header());

    // Font Settings and text draw
    u8g2.setBitmapMode(true);
    u8g2.setFont(u8g2_font_haxrcorp4089_tr);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    u8g2.drawStr(6, 1, "R. Gener.");

    u8g2.drawStr(7, 23, "Deseja iniciar o");
    u8g2.drawStr(7, 35, "refluxo generico");
    u8g2.drawStr(7, 47, "agora?");

    if(is_yes) {
        this->_draw_facus_answer(u8g2, ANSWER_X_POS, ANSWER_Y_POS);
    } else {
        this->_draw_facus_answer(u8g2, ANSWER_X_POS, ANSWER_Y_POS+15);
    }

    u8g2.drawStr(96, 27, "Sim");

    u8g2.drawStr(96, 42, "Nao");
}

void GenericReflow::_draw_facus_answer(U8G2 &u8g2, uint8_t x, uint8_t y) {
    u8g2.drawLine(x, y, x+19, y);
    u8g2.drawLine(x+20, y+1, x+20, y+12);
    u8g2.drawLine(x, y+12, x+19, y+12);
    u8g2.drawLine(x, y+13, x+19, y+13);
    u8g2.drawLine(x, y+1, x, y+12);
    u8g2.drawLine(x-1, y+1, x-1, y+12);
    // u8g2.drawBox(94, 28, 19, 11);
}