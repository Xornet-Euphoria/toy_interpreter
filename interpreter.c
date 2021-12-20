#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eval.h"

#define INPUT_MAX 256


int main(int argc, char *argv[]) {
    char input[INPUT_MAX];
    Token *tk_head;
    Node *nd_head;
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
        nd_head = expr_parse(tk_head);

        res = eval(nd_head);
        printf("[->] %d\n", res);
    }
}