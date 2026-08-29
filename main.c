#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define ESC_KEY 27 // == ^[
#define PROMPT_DOLLAR_SYMBOL "$"

typedef enum {
    LS,
    CAT,
    HISTORY,
    None
}Command;

// Desrialization
Command get_command(char *command_buffer) {
    if (!strcmp(command_buffer, "ls")) {
        return (Command)LS;
    }else if (!strcmp(command_buffer, "cat")) {
        return (Command)CAT;
    } else if (!strcmp(command_buffer, "history")) {
        return (Command)HISTORY;
    }else {
        printf("%s: command not found\n", command_buffer);
        return (Command)None;
    }
}

void is_full_command_valid(Command command, size_t num_args) {
    // TODO i need also to check if the argument is valid
    if (command == (Command)LS && num_args > 1) {
        printf("expected ls with one argument\n");
    }else if (command == (Command)CAT && num_args > 1) {
        printf("expected cat with one argument\n");
    }else if (command == (Command)HISTORY && num_args > 0) {
        printf("expected hisotry with no argument\n");
    }
}
 
void clean_screen() {
    printf("%c[2J",ESC_KEY);
}

void cursor_top () {
    printf("%c[H",ESC_KEY);
}

void run_command(char *buffer){}
void run_ls_command(char *buffer){}

// TODO make functions
void run() {
    while (1) {
        char *buffer = NULL;
        size_t bufferlen = 0; 

        printf("%s ", PROMPT_DOLLAR_SYMBOL);

        if (getline(&buffer, &bufferlen, stdin) == -1) {
            printf("[Error] Failed to read line");
        }

        char *token = strtok(buffer, " \n");
        // printf("command is : %s\n", token);
        Command command = get_command(token);
        if (command == (Command)None) {
            continue;
        }

        // NOTE you didn't store arg token
        size_t num_args = 0;
        while (true) {
            token = strtok(NULL, " \n");
            if (token == NULL) {
                break;
            }
            // printf("token -> %s\n", token);
            num_args++;
        }

        is_full_command_valid(command, num_args);
    }
}

int main (void) {
    clean_screen();
    cursor_top();
    run();
}
