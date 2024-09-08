#include <stdint.h>
#include <stddef.h>

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

static inline void outb(uint16_t port, uint8_t data) {
    __asm__ volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

void reboot_system();

#define VIDEO_MEMORY 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

char input_buffer[256];
size_t buffer_index = 0;

void print_char(char character, size_t* row, size_t* col) {
    uint16_t* video_memory = (uint16_t*) VIDEO_MEMORY;
    if (character == '\n') {
        *row = *row + 1;
        *col = 0;
    } else {
        video_memory[*row * MAX_COLS + *col] = (uint16_t) character | (WHITE_ON_BLACK << 8);
        *col = *col + 1;
        if (*col >= MAX_COLS) {
            *col = 0;
            *row = *row + 1;
        }
    }
}

void print_string(const char* str, size_t* row, size_t* col) {
    while (*str != '\0') {
        print_char(*str, row, col);
        str++;
    }
}

void clear_screen() {
    uint16_t* video_memory = (uint16_t*) VIDEO_MEMORY;
    for (int i = 0; i < MAX_ROWS * MAX_COLS; i++) {
        video_memory[i] = (uint16_t) ' ' | (WHITE_ON_BLACK << 8);
    }
}

char scancode_to_char(uint8_t scancode) {
    const char ASCII[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (scancode >= 0x02 && scancode <= 0x0A) {
        return ASCII[scancode - 0x02];
    }
    return '?'; //
}

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

void keyboard_handler(size_t* row, size_t* col) {
    uint8_t scancode = inb(0x60); 
    char key = scancode_to_char(scancode);

    if (key == '\n') {
        input_buffer[buffer_index] = '\0'; 
        execute_command(input_buffer, row, col);  
        buffer_index = 0; 
    } else if (key == '\b') {
        if (buffer_index > 0) {
            buffer_index--;
            *col = *col - 1;
            print_char(' ', row, col);
        }
    } else {
        input_buffer[buffer_index++] = key;
        print_char(key, row, col);
    }
}

void reboot_system() {
    outb(0x64, 0xFE);
}

void kernel_main() {
    clear_screen();
    size_t row = 0;
    size_t col = 0;

    print_string("Welcome to My OS!\n", &row, &col);
    print_string("Enter a command: ", &row, &col);

    while (1) {
        keyboard_handler(&row, &col);
    }
}
