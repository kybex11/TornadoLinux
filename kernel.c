#include <stddef.h>
#include "io.h"
#include "keyboard.h"
#include "commands.h"


void kernel_main() {
    clear_screen();
    size_t row = 0;
    size_t col = 0;

    print_string("Welcome to Tornado Kernel!\n", &row, &col);
    print_string("Enter a command: ", &row, &col);

    // Save the current cursor position after the prompt for the input
    size_t input_row = row;
    size_t input_col = col;

    while (1) {
        keyboard_handler(&input_row, &input_col);  // Pass the input cursor position to the handler
    }
}
