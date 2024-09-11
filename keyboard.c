#include "keyboard.h"
#include "io.h"
#include "commands.h"
#include <stdint.h>


char input_buffer[256];
size_t buffer_index = 0;

char scancode_to_char(uint8_t scancode) {
    const char ASCII[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (scancode >= 0x02 && scancode <= 0x0A) {
        return ASCII[scancode - 0x02];
    }
    return '?'; // Unrecognized key
}

void keyboard_handler(size_t* input_row, size_t* input_col) {
    uint8_t scancode = inb(0x60); 
    char key = scancode_to_char(scancode);

    if (key == '\n') {
        input_buffer[buffer_index] = '\0';  // Null-terminate the input string
        execute_command(input_buffer, input_row, input_col);  // Execute the command
        buffer_index = 0;  // Reset the input buffer index

        // Reset the input cursor position for the next command prompt
        print_string("Enter a command: ", input_row, input_col);
    } else if (key == '\b') {  // Backspace
        if (buffer_index > 0) {
            buffer_index--;
            *input_col = *input_col - 1;
            print_char(' ', input_row, input_col);  // Clear the character visually
        }
    } else {  // Regular character
        input_buffer[buffer_index++] = key;
        print_char(key, input_row, input_col);  // Display the character on screen
    }
}
