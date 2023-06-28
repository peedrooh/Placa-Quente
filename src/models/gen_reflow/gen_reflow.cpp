#include "gen_reflow.h"
#include "assets/headers/headers.h"

#define HEADER_DASHED_BACK 2
#define CONFIRM_ANSWER_X_POS 93
#define CONFIRM_ANSWER_Y_POS 26

#define PLOT_START_X 20
#define PLOT_END_X 125
#define PLOT_START_Y 3
#define PLOT_END_Y 50

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
    u8g2.drawStr(6, 0, "R. Gener.");

    u8g2.drawStr(7, 23, "Deseja iniciar o");
    u8g2.drawStr(7, 35, "refluxo generico");
    u8g2.drawStr(7, 47, "agora?");

    if(is_yes) {
        this->_draw_focus_answer(u8g2, CONFIRM_ANSWER_X_POS, CONFIRM_ANSWER_Y_POS);
    } else {
        this->_draw_focus_answer(u8g2, CONFIRM_ANSWER_X_POS, CONFIRM_ANSWER_Y_POS+15);
    }

    u8g2.drawStr(96, 27, "Sim");

    u8g2.drawStr(96, 42, "Nao");
}

void GenericReflow::_draw_focus_answer(U8G2 &u8g2, uint8_t x, uint8_t y) {
    u8g2.drawLine(x, y, x+19, y);
    u8g2.drawLine(x+20, y+1, x+20, y+12);
    u8g2.drawLine(x, y+12, x+19, y+12);
    u8g2.drawLine(x, y+13, x+19, y+13);
    u8g2.drawLine(x, y+1, x, y+12);
    u8g2.drawLine(x-1, y+1, x-1, y+12);
    // u8g2.drawBox(94, 28, 19, 11);
}

void GenericReflow::draw_temp_graph(U8G2 &u8g2, byte is_celcius) {
    this->_draw_XY_axis(u8g2, is_celcius);

    for(int i = 0; i < 330; i++) {
        // x ranges from 20 to 125
        // equal to 0 to 95
        //    0 ----- 0
        // time ----- x
        //  270 ----- 95
        //  x = time.95/330
        // But we must add the 20 that we removed in the begining of the calculations, so
        // x = ((time*95)/330)+20
        float x = ((this->_points[i][0]*95)/330)+20;
        float y = 54 - ((this->_points[i][1]*48)/250);
        // if(!is_celcius) {
        //     y = 54 - ((this->_points[i][1]*48)/392);
        // }
        u8g2.drawPixel(x, y);
    }
}

void GenericReflow::_draw_XY_axis(U8G2 &u8g2, byte is_celcius) {

    u8g2.drawLine(PLOT_START_X, PLOT_START_Y, PLOT_START_X, PLOT_END_Y);
    u8g2.drawLine(PLOT_START_X, PLOT_END_Y, PLOT_END_X, PLOT_END_Y);

    for(int i = 1; i <= 3; i++) {
        u8g2.drawLine(PLOT_START_X+1+(i*28), PLOT_END_Y, PLOT_START_X+1+(i*28), PLOT_END_Y+2);
    }
    for(int i = 0; i < 4; i++) {
        u8g2.drawLine(PLOT_START_X-2, 44-(i*10), PLOT_START_X, 44-(i*10));
    }

    u8g2.drawBox(19, 4, 3, 2);
    u8g2.drawLine(18, 5, 18, 6);
    u8g2.drawLine(22, 5, 22, 6);

    u8g2.drawBox(123, 49, 2, 3);
    u8g2.drawLine(122, 48, 123, 48);
    u8g2.drawLine(122, 52, 123, 52);

    
    u8g2.setBitmapMode(true);
    u8g2.setFont(u8g2_font_haxrcorp4089_tr);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    u8g2.drawStr(109, 37, "t[s]");

    u8g2.drawStr(12, 52, "0");

    u8g2.drawStr(44, 52, "90");
    u8g2.drawStr(70, 52, "180");
    u8g2.drawStr(97, 52, "270");
    if(is_celcius) {
        u8g2.drawStr(25, 1, "T[C]");

        u8g2.drawStr(0, 5, "200");
        u8g2.drawStr(3, 15, "150");
        u8g2.drawStr(3, 25, "100");
        u8g2.drawStr(6, 35, "50");
    } else {
        u8g2.drawStr(25, 1, "T[F]");

        u8g2.drawStr(0, 5, "392");
        u8g2.drawStr(3, 15, "302");
        u8g2.drawStr(3, 25, "212");
        u8g2.drawStr(6, 35, "122");

    }
}

void GenericReflow::add_point_in_graph(uint16_t time, float temperature) {
    if(time < 0) return;
    if(time > 330) return;

    this->_points[time - 1][0] = time;
    this->_points[time - 1][1] = temperature;
}

void GenericReflow::reset_graph() {
    for(int i = 0; i < 330; i++) {
        this->_points[i][0] = i;
        this->_points[i][0] = 0;
    }
}