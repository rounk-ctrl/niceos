#ifndef SCREEN_H
#define SCREEN_H
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Colors
#define DARKBLUE_ON_BLACK 0x01
#define DARKGREEN_ON_BLACK 0x02
#define CYAN_ON_BLACK 0x03
#define DARKRED_ON_BLACK 0x04
#define PURPLE_ON_BLACK 0x05
#define BROWN_ON_BLACK 0X06
#define WHITE_ON_BLACK 0x07
#define GRAY_ON_BLACK 0X08
#define BLUE_ON_BLACK 0x09
#define GREEN_ON_BLACK 0x0a
#define LIGHTBLUE_ON_BLACK 0x0b
#define RED_ON_BLACK 0x0c
#define PINK_ON_BLACK 0x0d
#define YELLOW_ON_BLACK 0x0e
#define LIGHTWHITE_ON_BLACK 0x0f
#define SOD_TEXT 0x4f
// ------------------------
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5
int strlen();
void clear_screen();
void kprint_at(char *message, int col, int row);
void kprint(char *message);
void kprint_backspace();
#endif