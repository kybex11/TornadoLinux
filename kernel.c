#include <stdint.h>
#include <stddef.h>

size_t strlen(const char* str) {
    size_t len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

void print_string(const char* str) {
    uint16_t* video_memory = (uint16_t*) 0xB8000;
    for (size_t i = 0; i < strlen(str); i++) {
        video_memory[i] = (uint16_t) str[i] | 0x0F << 8;
    }
}

void kernel_main() {
    print_string("Hello, World!");
}

void _start() {
    kernel_main();
    while (1) {}
}