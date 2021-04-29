#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>
#include "../localisation/en-us.h"
#include "../localisation/tr-tr.h"
;
char smalls[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char caps[28] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char numbers[11] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\0'};
char period = '.';
char space = ' ';
char new = '\n';
void kernel_main() {
    isr_install();
    asm("int $19");
    irq_install();
    // Check /localisation/language-country.h for more info.
    // Localisation is not our top priority.
    kprint(welcome_en);
    print_char(caps[13], -1, -1, GREEN_ON_BLACK);print_char(smalls[8], -1, -1, GREEN_ON_BLACK);print_char(smalls[2], -1, -1, GREEN_ON_BLACK);print_char(smalls[4], -1, -1, GREEN_ON_BLACK);print_char(caps[14], -1, -1, GREEN_ON_BLACK);print_char(caps[18], -1, -1, GREEN_ON_BLACK);
    print_char(new, -1, -1, CYAN_ON_BLACK);
    kprint("Type ");print_char(caps[7], -1, -1, BLUE_ON_BLACK);print_char(caps[4], -1, -1, BLUE_ON_BLACK);print_char(caps[11], -1, -1, BLUE_ON_BLACK);print_char(caps[15], -1, -1, BLUE_ON_BLACK);
    kprint(" for a list of command.\n> ");
}
void user_input(char *input) {
    if (strcmp(input, "halt") == 0) {
        kprint("System Halted!\n");
        asm volatile("hlt");
    } else if (strcmp(input, "page") == 0) {
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    }
    else if (strcmp(input, "cls") == 0)
    {
        clear_screen();
    }
    
    else if(strcmp(input, "") == 0){
        kprint("");
    }
    else if(strcmp(input, "help") == 0){
        kprint(helpmessage_en);
    }
    else if(strcmp(input, "about") == 0){
        print_char(caps[13], -1, -1, GREEN_ON_BLACK);print_char(smalls[8], -1, -1, GREEN_ON_BLACK);print_char(smalls[2], -1, -1, GREEN_ON_BLACK);print_char(smalls[4], -1, -1, GREEN_ON_BLACK);print_char(caps[14], -1, -1, GREEN_ON_BLACK);print_char(caps[18], -1, -1, GREEN_ON_BLACK);
        kprint(" ");
        print_char(caps[0], -1, -1, RED_ON_BLACK);print_char(smalls[11], -1, -1, RED_ON_BLACK);print_char(smalls[15], -1, -1, RED_ON_BLACK);print_char(smalls[7], -1, -1, RED_ON_BLACK);print_char(smalls[0], -1, -1, RED_ON_BLACK);print_char(new, -1, -1, RED_ON_BLACK);
        kprint("Version ");print_char(numbers[1], -1, -1, CYAN_ON_BLACK);print_char(period, -1, -1, CYAN_ON_BLACK);print_char(numbers[9], -1, -1, CYAN_ON_BLACK);print_char(numbers[8], -1, -1, CYAN_ON_BLACK);
        kprint("\n");
	kprint("Contribute on GitHub!\n");
    }
    else if(strcmp(input, "clear") == 0)
    {
        clear_screen();
    }
    else if(strcmp(input, "hello") == 0)
    {
        kprint("Hello, World!\n");
    }
    else if(strcmp(input, "gui") == 0)
    {
        kprint("I see you are excited for a gui, but it is on its way!\n");
    }
    else if(strcmp(input, "die") == 0){
        clear_screen();
        print_char(caps[18], -1, -1, SOD_TEXT);print_char(smalls[24], -1, -1, SOD_TEXT);print_char(smalls[18], -1, -1, SOD_TEXT);print_char(smalls[19], -1, -1, SOD_TEXT);print_char(smalls[4], -1, -1, SOD_TEXT);print_char(smalls[12], -1, -1, SOD_TEXT);
        print_char(space, -1, -1, SOD_TEXT);
        print_char(smalls[2], -1, -1, SOD_TEXT);print_char(smalls[17], -1, -1, SOD_TEXT);print_char(smalls[0], -1, -1, SOD_TEXT);print_char(smalls[18], -1, -1, SOD_TEXT);print_char(smalls[7], -1, -1, SOD_TEXT);print_char(smalls[4], -1, -1, SOD_TEXT);print_char(smalls[3], -1, -1, SOD_TEXT);
        kprint("\n");
        print_char(caps[15], -1, -1, SOD_TEXT);print_char(smalls[11], -1, -1, SOD_TEXT);print_char(smalls[4], -1, -1, SOD_TEXT);print_char(smalls[0], -1, -1, SOD_TEXT);print_char(smalls[18], -1, -1, SOD_TEXT);print_char(smalls[4], -1, -1, SOD_TEXT);
        print_char(space, -1, -1, SOD_TEXT);
        print_char(smalls[17], -1, -1, SOD_TEXT);print_char(smalls[4], -1, -1, SOD_TEXT);print_char(smalls[1], -1, -1, SOD_TEXT);print_char(smalls[14], -1, -1, SOD_TEXT);print_char(smalls[14], -1, -1, SOD_TEXT);print_char(smalls[19], -1, -1, SOD_TEXT);
        kprint("\n");
        asm volatile("hlt");
    }
    else if(strcmp(input, "color") == 0)
    {
	print_char(caps[19], -1, -1, GREEN_ON_BLACK);
    print_char(new, -1, -1);
	print_char(caps[12], -1, -1, BLUE_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[16], -1, -1, RED_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[8], -1, -1, WHITE_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[9], -1, -1, DARKGREEN_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[7], -1, -1, CYAN_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[2], -1, -1, DARKRED_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[10], -1, -1, BROWN_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[10], -1, -1, PURPLE_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[21], -1, -1, GRAY_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[11], -1, -1, LIGHTBLUE_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[3], -1, -1, PINK_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[1], -1, -1, YELLOW_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[9], -1, -1, DARKBLUE_ON_BLACK);
    print_char(new, -1, -1);
    print_char(caps[19], -1, -1, LIGHTWHITE_ON_BLACK);
    print_char(new, -1, -1);
    }
    else
    {
        kprint("'");
        kprint(input);
        kprint("' is not a command\n");
    }
    kprint("> ");
}