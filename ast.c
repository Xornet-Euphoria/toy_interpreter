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

void next_head_ctx(Context *ctx) {
    ctx->head = ctx->head->next;
}

void prim_parse(Context *ctx) {
    Token *head = ctx->head;

    if (is_reserved(head, "(")) {
        next_head_ctx(ctx);
        expr_parse(ctx);

        if (is_reserved(ctx->head, ")")) {
            next_head_ctx(ctx);
            return;
        } else {
            fprintf(stderr, "[!] `)` is expected, but %c is given", ctx->head->raw[0]);
            exit(1);
        }
    }
    if (head->type != TK_NUM)
    {
        fprintf(stderr, "[!] `TK_NUM (%d)` is expected, but %d is given as primary.", TK_NUM, head->type);
        exit(1);
    }

    Node *ret = create_num_node(head->val);
    next_head_ctx(ctx);
    ctx->ret = ret;
}

void un_parse(Context *ctx) {
    if (is_reserved(ctx->head, "+")) {
        next_head_ctx(ctx);
        prim_parse(ctx);
    } else if (is_reserved(ctx->head, "-")) {
        next_head_ctx(ctx);
        prim_parse(ctx);
        Node *lhs = create_num_node(0);
        Node *rhs = ctx->ret;
        Node *node = create_operator_node(ND_SUB, lhs, rhs);
        ctx->ret = node;
    }
    else
    {
        prim_parse(ctx);
    }
}

void mul_parse(Context *ctx) {
    un_parse(ctx);
    Node *node = ctx->ret;

    while (1) {
        if (is_reserved(ctx->head, "*")) {
            next_head_ctx(ctx);
            un_parse(ctx);
            Node *rhs = ctx->ret;
            node = create_operator_node(ND_MUL, node, rhs);
        } else if (is_reserved(ctx->head, "/")) {
            next_head_ctx(ctx);
            un_parse(ctx);
            Node *rhs = ctx->ret;
            node = create_operator_node(ND_DIV, node, rhs);
        } else {
            ctx->ret = node;
            return;
        }
    }
}

void add_parse(Context *ctx) {
    mul_parse(ctx);
    Node *node = ctx->ret;

    while (1) {
        if (is_reserved(ctx->head, "+")) {
            next_head_ctx(ctx);
            mul_parse(ctx);
            Node *rhs = ctx->ret;
            node = create_operator_node(ND_ADD, node, rhs);
        } else if (is_reserved(ctx->head, "-")) {
            next_head_ctx(ctx);
            mul_parse(ctx);
            Node *rhs = ctx->ret;
            node = create_operator_node(ND_SUB, node, rhs);
        } else {
            ctx->ret = node;
            return;
        }
    }
}

void expr_parse(Context *ctx) {
    add_parse(ctx);
    Node *node = ctx->ret;

    while (1) {
        if (is_reserved(ctx->head, "==")) {
            next_head_ctx(ctx);
            add_parse(ctx);
            Node *rhs = ctx->ret;
            node = create_operator_node(ND_EQ, node, rhs);
        } else if (is_reserved(ctx->head, "!=")) {
            next_head_ctx(ctx);
            add_parse(ctx);
            Node *rhs = ctx->ret;
            node = create_operator_node(ND_NEQ, node, rhs);
        } else {
            ctx->ret = node;
            return;
        }
    }
}