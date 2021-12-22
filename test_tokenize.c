#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

#define INPUT_MAX 256


int main(int argc, char *argv[]) {
    char input[INPUT_MAX];
    Token *tk_head;
    int res;
    while (1)
    {
        printf("[<-] ");
        fgets(input, INPUT_MAX, stdin);
        if (strncmp(input, "exit\n", 5) == 0) {
            printf("[->] bye!!\n");
            break;
        }

        tk_head = tokenize(input);

        // free tokens
        Token *next_token;
        while (tk_head)
        {
            dump_token(tk_head);
            next_token = tk_head->next;
            tk_head = next_token;
        }
    }

    return 0;
}