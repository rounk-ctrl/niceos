#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>
#include "../localisation/en-us.h"
#include "../localisation/tr-tr.h"
// If you create files for languages, dont forget to include them!
// There is not much translations as the English and Turkish one is for demonstration reasons.
;   // Idk why this is needed but it will error if you delete this
void kernel_main() {
    isr_install();
    irq_install();

    asm("int $2");
    asm("int $3");

    clear_screen();
    // Check /localisation/language-country.h for more info.
    kprint(welcome_en);
    kprint(typehelplist_en);
}

void user_input(char *input) {
    if (strcmp(input, "HALT") == 0) {
        kprint("System Halted!\n");
        asm volatile("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
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
    } else if (strcmp(input, "CLS") == 0)
    { 
        clear_screen();
    }
    else if(strcmp(input, "") == 0){
        kprint("");
    }
    else if(strcmp(input, "HELP") == 0){
        // Check /localisation/language-country.h for more info.
        kprint(helpmessage_en);
    }
    else if(strcmp(input, "ABOUT") == 0){
        kprint("NiceOS Alpha!\n");
        kprint("Version 2.09\n");
        kprint("(C) NiceOS Team!\n");
	kprint("Contribute on GitHub!\n");
    }
    else if(strcmp(input, "CLEAR") == 0)
    { 
        clear_screen();
    }
    else if(strcmp(input, "HELLO") == 0)
    { 
        kprint("Hello, World!\n");
    }
    else if(strcmp(input, "SHELL") == 0)
    { 
        kprint("I see you are excited for a shell, but it is on its way!\n");
    }
    else if(strcmp(input, "TEST") == 0)
    {
	    // I dont know why vim has these weird tabs but yea
	    kprint("TEST\n");
    }
    else
    {
        kprint("Command: '");
        kprint(input);
        kprint("' not found.\n");
    }
    
    
    kprint("> ");
}
