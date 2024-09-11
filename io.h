#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdint.h>

#define VIDEO_MEMORY 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

void clear_screen();
void print_char(char character, size_t* row, size_t* col);
void print_string(const char* str, size_t* row, size_t* col);

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__ ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}


#endif
