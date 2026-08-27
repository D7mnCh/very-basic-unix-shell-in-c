#include<stdio.h>
#define ESC_KEY 27 // == ^[
#define Prompt_symbol "$"

void clean_screen() {
    printf("%c[2J",ESC_KEY);
}

void cursor_top () {
    printf("%c[H",ESC_KEY);
}

void run() {
    // used of dyn allocation if buffer set to NULL cuz
    //of using of getline
    // TODO remove above comment by allocating memory
    while (1) {
        char *buffer = NULL;
        size_t bufferlen = 0; 

        printf("%s ", Prompt_symbol);
        if (getline(&buffer, &bufferlen, stdin) == -1) {
            printf("[Error] Failed to read line");
        }
    }
}

int main (void) {
    clean_screen();
    cursor_top();
    run();
}
