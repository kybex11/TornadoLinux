#include "commands.h"
#include "io.h"
#include <stdint.h>


int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

void reboot_system();

void execute_command(const char* command, size_t* row, size_t* col) {
    if (strcmp(command, "clear") == 0) {
        clear_screen();
        *row = 0;
        *col = 0;
    } else if (strcmp(command, "help") == 0) {
        print_string("Available commands: clear, help, reboot\n", row, col);
    } else if (strcmp(command, "reboot") == 0) {
        print_string("Rebooting...\n", row, col);
        reboot_system();
    } else {
        print_string("Unknown command: ", row, col);
        print_string(command, row, col);
        print_string("\n", row, col);
    }
}

void reboot_system() {
    outb(0x64, 0xFE); // Magic number to reboot system
}
