#include "tokenize.h"

typedef enum
{
    ND_ADD,
    ND_SUB,
    ND_MUL,
    ND_DIV,
    ND_EQ,
    ND_NEQ,
    ND_NUM,
    ND_ASSIGN,
    ND_VAR,
} NodeType;

typedef struct Var Var;

struct Var {
    char *name;
    int val;
    Var *next;
};

typedef struct Node Node;

struct Node {
    NodeType type;
    Node *lhs;
    Node *rhs;
    Var *var;  // used type == ND_VAR
    int val;   // used type == ND_NUM
};

typedef struct
{
    Token *head;
    Node *ret;
    Var *var_head;
} Context;

extern void expr_parse(Context *ctx);