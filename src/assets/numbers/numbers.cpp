#include "numbers.h"


#define number_zero_width 8
#define number_zero_height 10
static const unsigned char number_zero_bitmap[] U8X8_PROGMEM = {
  0x3C, 0x7E, 0x66, 0x76, 0x7E, 0x7E, 0x6E, 0x66, 0x7E, 0x3C, };
Number* number_zero = new Number(number_zero_bitmap, number_zero_width, number_zero_height);



#define number_one_width 8
#define number_one_height 10
static const unsigned char number_one_bitmap[] U8X8_PROGMEM = {
  0x38, 0x38, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, };
Number* number_one = new Number(number_one_bitmap, number_one_width, number_one_height);


#define number_two_width 8
#define number_two_height 10
static const unsigned char number_two_bitmap[] U8X8_PROGMEM = {
  0x3C, 0x7E, 0x66, 0x60, 0x7C, 0x3E, 0x06, 0x06, 0x7E, 0x7E, };
Number* number_two = new Number(number_two_bitmap, number_two_width, number_two_height);


#define number_three_width 8
#define number_three_height 10
static const unsigned char number_three_bitmap[] U8X8_PROGMEM = {
  0x3C, 0x7E, 0x66, 0x60, 0x38, 0x78, 0x60, 0x66, 0x7E, 0x3C, };
Number* number_three = new Number(number_three_bitmap, number_three_width, number_three_height);


#define number_four_width 8
#define number_four_height 10
static const unsigned char number_four_bitmap[] U8X8_PROGMEM = {
  0x78, 0x7C, 0x6E, 0x66, 0x66, 0xFE, 0xFE, 0x60, 0x60, 0x60, };
Number* number_four = new Number(number_four_bitmap, number_four_width, number_four_height);


#define number_five_width 8
#define number_five_height 10
static const unsigned char number_five_bitmap[] U8X8_PROGMEM = {
  0x7E, 0x7E, 0x06, 0x06, 0x3E, 0x7E, 0x60, 0x66, 0x7E, 0x3C, };
Number* number_five = new Number(number_five_bitmap, number_five_width, number_five_height);


#define number_six_width 8
#define number_six_height 10
static const unsigned char number_six_bitmap[] U8X8_PROGMEM = {
  0x3C, 0x7E, 0x66, 0x06, 0x3E, 0x7E, 0x66, 0x66, 0x7E, 0x3C, };
Number* number_six = new Number(number_six_bitmap, number_six_width, number_six_height);


#define number_seven_width 8
#define number_seven_height 10
static const unsigned char number_seven_bitmap[] U8X8_PROGMEM = {
  0x7E, 0x7E, 0x66, 0x30, 0x18, 0x18, 0x3C, 0x3C, 0x18, 0x18, };
Number* number_seven = new Number(number_seven_bitmap, number_seven_width, number_seven_height);

#define number_eight_width 8
#define number_eight_height 10
static const unsigned char number_eight_bitmap[] U8X8_PROGMEM = {
  0x3C, 0x7E, 0x66, 0x66, 0x3C, 0x7E, 0x66, 0x66, 0x7E, 0x3C, };
Number* number_eight = new Number(number_eight_bitmap, number_eight_width, number_eight_height);


#define number_nine_width 8
#define number_nine_height 10
static const unsigned char number_nine_bitmap[] U8X8_PROGMEM = {
  0x3C, 0x7E, 0x66, 0x66, 0x7E, 0x7C, 0x60, 0x66, 0x7E, 0x3C, };
Number* number_nine = new Number(number_nine_bitmap, number_nine_width, number_nine_height);


Number* all_numbers[10] = {
    number_zero,
    number_one, 
    number_two, 
    number_three, 
    number_four, 
    number_five, 
    number_six, 
    number_seven, 
    number_eight, 
    number_nine 
};