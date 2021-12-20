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

extern Node *expr_parse(Token *head);