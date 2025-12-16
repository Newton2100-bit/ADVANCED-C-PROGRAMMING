
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char default_value[128];

int startup_hook(void){
    rl_insert_text(default_value);   // Pre-fill buffer
    rl_point = rl_end;               // Move cursor to end
    return 0;
}

int main(void){
    strcpy(default_value, "Anonymous");   // the default text

    rl_startup_hook = startup_hook;

    char *input = readline("Enter your name: ");

    rl_startup_hook = NULL;  // cleanup hook

    printf("Your name is: %s\n", input);
}
