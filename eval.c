#include <stdio.h>
#include <stdlib.h>
#include "eval.h"

int eval(Node *node) {
    NodeType nd_type = node->type;
    int ret;
    switch (nd_type)
    {
        case ND_NUM:
            ret = node->val;
            break;
        case ND_VAR:
            ret = node->var->val;
            break;
        case ND_ADD:
            ret = eval(node->lhs) + eval(node->rhs);
            break;
        case ND_SUB:
            ret = eval(node->lhs) - eval(node->rhs);
            break;
        case ND_MUL:
            ret = eval(node->lhs) * eval(node->rhs);
            break;
        case ND_DIV:
            ret = eval(node->lhs) / eval(node->rhs);
            break;
        case ND_EQ:
            ret = eval(node->lhs) == eval(node->rhs);
            break;
        case ND_NEQ:
            ret = eval(node->lhs) != eval(node->rhs);
            break;
        case ND_ASSIGN:
            ret = eval(node->rhs);
            node->lhs->var->val = ret;
            break;
        }

    return ret;
}