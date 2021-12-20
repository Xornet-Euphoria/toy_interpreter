#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"

Node *create_num_node(int n) {
    Node *ret = malloc(sizeof(Node));

    ret->type = ND_NUM;
    ret->val = n;

    return ret;
}

Node *create_operator_node(NodeType type, Node *lhs, Node *rhs) {
    Node *ret = malloc(sizeof(Node));

    ret->type = type;
    ret->lhs = lhs;
    ret->rhs = rhs;

    return ret;
}

Node *prim_parse(Token *head) {
    if (head->type != TK_NUM) {
        fprintf(stderr, "[!] `TK_NUM (%d)` is expected, but %d is given as primary.", TK_NUM, head->type);
        exit(1);
    }

    return create_num_node(head->val);
}

Node *expr_parse(Token *head) {
    Node *node = prim_parse(head);
    head = head->next;

    while (head) {
        if (is_reserved(head, '+')) {
            head = head->next;
            Node *rhs = prim_parse(head);
            head = head->next;
            node = create_operator_node(ND_ADD, node, rhs);
        } else if (is_reserved(head, '-')) {
            head = head->next;
            Node *rhs = prim_parse(head);
            head = head->next;
            node = create_operator_node(ND_SUB, node, rhs);
        }
    }

    return node;
}