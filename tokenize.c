#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenize.h"

char *reserved_tokens[] = {
    "+", "-", "*", "/", "(", ")",
    "==", "!="
};
// added in the futured. (currently, RESERVED variable literally)
char *reserved_string_tokens[] = {

};
const int reserved_count = sizeof(reserved_tokens) / sizeof(char *);

Token *create_token(char *p, TokenType type) {
    Token *ret = malloc(sizeof(Token));
    ret->type = type;
    ret->raw = p;

    return ret;
}

int check_reserved(char *p) {
    int length = 0;
    char *reserved;
    for (int i = 0; i < reserved_count; i++)
    {
        reserved = reserved_tokens[i];
        length = strlen(reserved);
        if (strncmp(p, reserved, length) == 0)
        {
            return length;
        }
    }

    return 0;
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
        } else {
            int l = check_reserved(p);
            if (l) {
                token = create_token(p, TK_RESERVED);
                token->length = l;
                p += l;
            } else {
                char *raw = p;
                int l = 0;
                while (!check_reserved(p) && !isspace(*p))
                {
                    l++;
                    p++;
                }
                token = create_token(raw, TK_IDENT);
                token->length = l;
            }
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
    printf("[+] Length: %d\n", token->length);
    if (token->type == TK_NUM)
    {
        printf("[+] Number: %d\n", token->val);
    }
    printf("[+] raw string: %s\n", token->raw);
}

int is_reserved(Token *token, char *reserved) {
    if (token == NULL) {
        return 0;
    }

    if (token->type != TK_RESERVED) {
        return 0;
    }

    int l = token->length;

    if (strncmp(token->raw, reserved, l) == 0) {
        return 1;
    }

    return 0;
}