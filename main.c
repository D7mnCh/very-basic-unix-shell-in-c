#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
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

void clean_screen() {
    printf("%c[2J",ESC_KEY);
}

void cursor_top () {
    printf("%c[H",ESC_KEY);
}

void run_ls_command(char *arg){
    // ls [empty] == ls .
    if (!arg) {
        arg = ".";
    }

    DIR *dir_stream = opendir(arg);
    if (dir_stream == NULL) {
        perror(arg);
        return;
    }

    struct dirent *dir = NULL;
    while (dir = readdir(dir_stream)) {
        printf("%s\t", dir->d_name);
    }
    printf("\n");

    if (closedir(dir_stream) != 0) {
        perror(arg);
        return;
    }
}

bool check_args_len(Command command, size_t num_args) {
    if (command == (Command)LS && num_args > 1u) {
        printf("expected ls command with one argument\n");
        return false;
    }else if (command == (Command)CAT && num_args > 1u) {
        printf("expected cat command with one argument\n");
        return false;
    }else if (command == (Command)HISTORY && num_args > 0) {
        printf("expected hisotry command with no argument\n");
        return false;
    }
    return true;
}
 

void run_command(Command command, char* arg, size_t num_args){
    if (check_args_len(command, num_args) == false) {
        return;
    }

    switch (command) {
        case LS: run_ls_command(arg);break;
        case CAT: printf("didn't impl cat yet\n");break;
        case HISTORY: printf("didn't implt history yet\n");break;
        default: printf("unreachable: should handled None Command \
                        varient before calling this function\n");
    }
}

// TODO make functions
void run() {
    while (1) {
        char *buffer = NULL;
        size_t bufferlen = 0; 

        printf("%s ", PROMPT_DOLLAR_SYMBOL);

        // TODO ignore any escape keycode as an input
        if (getline(&buffer, &bufferlen, stdin) == -1) {
            printf("[Error] Failed to read line");
        }

        char *token = strtok(buffer, " \n");
        if (token == NULL) {
            continue;
        }

        Command command = get_command(token);
        if (command == (Command)None) {
            continue;
        }

        size_t num_args = 0;
        char* arg = NULL;
        while (true) {
            token = strtok(NULL, " \n");
            if (token == NULL) {
                break;
            }
            arg = token;
            // printf("token -> %s\n", token);
            num_args++;
        }

        run_command(command, arg, num_args);
    }
}

int main (void) {
    clean_screen();
    cursor_top();
    run();
}
