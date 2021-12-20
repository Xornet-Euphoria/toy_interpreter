#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenize.h"

Token *create_token(char *p, TokenType type) {
    Token *ret = malloc(sizeof(Token));
    ret->type = type;
    ret->raw = p;

    return ret;
}

Token *craete_number_token(char *p, int num) {
    Token *ret = malloc(sizeof(Token));
    ret->type = TK_NUM;
    ret->val = num;
    ret->raw = p;

    return ret;
}

// return pointer of head token. tokens are in linked list.
Token *tokenize(char *p) {
    Token *ret = NULL;
    Token *current = NULL;
    Token *token;
    while (*p)
    {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (isdigit(*p)) {
            token = create_token(p, TK_NUM);
            int n = strtol(p, &p, 0);
            token->val = n;
        }
        else if (*p == '+' || *p == '-')
        {
            token = create_token(p, TK_RESERVED);
            p += 1;
        }
        else
        {
            token = create_token(p, TK_OTHER);
            int length = strlen(token->raw);
            p += length;
        }

        if (ret == NULL)
        {
            ret = token;
        } else {
            current->next = token;
        }

        current = token;
    }

    if (current) {
        current->next = NULL;
    }

    return ret;
}

void dump_token(Token *token) {
    printf("[+] Type: %d\n", token->type);
    if (token->type == TK_NUM) {
        printf("[+] Number: %d\n", token->val);
    }
    printf("[+] raw string: %s\n", token->raw);
}

int is_reserved(Token *token, char operator) {
    if (token->type != TK_RESERVED) {
        return 0;
    }

    if (token->raw[0] == operator) {
        return 1;
    }

    return 0;
}