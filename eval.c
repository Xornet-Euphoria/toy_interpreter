#include "eval.h"

int eval(Node *node) {
    if (node->type == ND_NUM) {
        return node->val;
    }

    if (node->type == ND_ADD) {
        return eval(node->lhs) + eval(node->rhs);
    }

    if (node->type == ND_SUB) {
        return eval(node->lhs) - eval(node->rhs);
    }
}