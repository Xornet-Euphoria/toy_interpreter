typedef enum
{
    TK_RESERVED,
    TK_NUM,
    TK_EOF,
    TK_IDENT,
    TK_OTHER // for debug and eliminated in the future
} TokenType;

typedef struct Token Token;

struct Token {
    TokenType type;
    Token *next;
    int val;
    char *raw;
    int length;
};

extern Token *tokenize(char *p);
extern void dump_token(Token *token);
extern int is_reserved(Token *token, char *reserved);