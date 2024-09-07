#include <stdint.h>
#include <stddef.h>

#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

static size_t cursor_x = 0;
static size_t cursor_y = 0;

size_t strlen(const char* str) {
    size_t len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

void scroll_screen() {
    uint16_t* video_memory = (uint16_t*) VIDEO_MEMORY;
    // Scroll the screen up by one line
    for (size_t i = SCREEN_WIDTH; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i - SCREEN_WIDTH] = video_memory[i];
    }
    // Clear the last line
    for (size_t i = SCREEN_WIDTH * (SCREEN_HEIGHT - 1); i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i] = ' ' | (0x0F << 8); // Space character with default color
    }
}

void print_string(const char* str) {
    uint16_t* video_memory = (uint16_t*) VIDEO_MEMORY;

    while (*str != '\0') {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
            if (cursor_y >= SCREEN_HEIGHT) {
                scroll_screen();
                cursor_y = SCREEN_HEIGHT - 1;
            }
        } else {
            video_memory[cursor_y * SCREEN_WIDTH + cursor_x] = (uint16_t) *str | (0x0F << 8); // White on black
            cursor_x++;
            if (cursor_x >= SCREEN_WIDTH) {
                cursor_x = 0;
                cursor_y++;
                if (cursor_y >= SCREEN_HEIGHT) {
                    scroll_screen();
                    cursor_y = SCREEN_HEIGHT - 1;
                }
            }
        }
        str++;
    }
}

void kernel_main() {
    print_string("Hi!");
    print_string("Penis sowkepa actions, otorvat, kastrirovat");
}
