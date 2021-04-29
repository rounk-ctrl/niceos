#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"
#include <stdint.h>

#define BACKSPACE 0x0E
#define CapsLock 0x3A
#define ENTER 0x1C

static char key_buffer[256];
static int CapsLockStatus = 0;

#define SC_MAX 57
#define SC_MAX 58
/* UpperCase Chars */
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
        "/", "RShift", "Keypad *", "LAlt", "Spacebar", "CapsLock"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' ', '?'};

/* LowerCase Chars */
const char *Lsc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "q", "w", "e", 
        "r", "t", "y", "u", "i", "o", "p", "[", "]", "Enter", "Lctrl", 
        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", 
        "LShift", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar", "CapsLock"};
const char Lsc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' ', '?'};

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(0x60);
    
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        kprint_backspace(key_buffer);
        backspace(key_buffer);
    } else if (scancode == ENTER) {
        kprint("\n");
        user_input(key_buffer);
        key_buffer[0] = '\0';
    } else if (scancode == CapsLock) {
        /* Toggle caps lock */
        if (CapsLockStatus)
            CapsLockStatus = 0;
        else
            CapsLockStatus = 1;
    } else {
        char letter = sc_ascii[(int)scancode];
        if (CapsLockStatus == 0)
            letter = Lsc_ascii[(int)scancode];
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}
char smallsl[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char capsl[28] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char numbersl[11] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\0'};
char what[2] = {'[', ']'};
char newl = '\n';
void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
    kprint("\n");print_char(what[0], -1, -1, WHITE_ON_BLACK);print_char(capsl[14], -1, -1, GREEN_ON_BLACK);print_char(capsl[10], -1, -1, GREEN_ON_BLACK); print_char(what[1], -1, -1, WHITE_ON_BLACK); kprint(" Setting up Keyboard\n");print_char(newl, -1, -1, WHITE_ON_BLACK);
}
