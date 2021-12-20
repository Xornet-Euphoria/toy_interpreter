#include "tokenize.h"

typedef enum
{
    ND_ADD,
    ND_SUB,
    ND_NUM,
} NodeType;

typedef struct Node Node;

struct Node {
    NodeType type;
    Node *lhs;
    Node *rhs;
    int val;
};

typedef struct {
    Token *head;
    Node *ret;
} Context;

extern void expr_parse(Context *ctx);