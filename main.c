#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define ESC_KEY 27 // == ^[
#define PROMPT_DOLLAR_SYMBOL "$"

// NOTE i don't really like to manually set COMMANDS_LEN
const size_t COMMANDS_LEN = 3;
const char *COMMANDS[] = {"ls", "cat", "history"};
 
void clean_screen() {
    printf("%c[2J",ESC_KEY);
}

void cursor_top () {
    printf("%c[H",ESC_KEY);
}

char *trim_new_line_char(char *str) {
    char *new_str;
    for (int i = 0; i < strlen(str); i++ ){
        if (str[i] == '\n'){
            new_str[i] = '\0';
            str = new_str;
            return str;
        }

        new_str[i] = str[i];
    }
}

bool is_valid_command(char *buffer) {
    for (int i = 0; i < COMMANDS_LEN; i++){
        if (!strcmp(buffer, COMMANDS[i])) {
            return true;
        }
    }
    return false;
}

// TODO
void run_command(char *command){}

void run() {
    while (1) {
        char *buffer = NULL;
        size_t bufferlen = 0; 

        printf("%s ", PROMPT_DOLLAR_SYMBOL);

        if (getline(&buffer, &bufferlen, stdin) == -1) {
            printf("[Error] Failed to read line");
        }

        buffer = trim_new_line_char(buffer);
        if (!is_valid_command(buffer)) {
            printf("%s: command not found\n", buffer);
            continue;
        }
        printf("%s: is one of our commands\n", buffer);
        // TODO run_command(COMMANDS[i]);
    }
}

int main (void) {
    clean_screen();
    cursor_top();
    run();
}
