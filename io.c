#include "io.h"
#include <stdint.h>


void clear_screen() {
    uint16_t* video_memory = (uint16_t*) VIDEO_MEMORY;
    for (int i = 0; i < MAX_ROWS * MAX_COLS; i++) {
        video_memory[i] = (uint16_t) ' ' | (WHITE_ON_BLACK << 8);
    }
}

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
