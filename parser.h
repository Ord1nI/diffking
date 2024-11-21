#ifndef _PARSER_H_
#define _PARSER_H_

#include "myclib/string/mystring.h"

enum Tokens {
    LOG = 0,
    LN,
    SIN,
    COS,
    SQRT,
    TG,
    CTG,
    ARCSIN,
    ARCCOS,
    ARCTG,
    ARCCTG,

    POW = '^',
    PLUS = '+',
    MINUS = '-',
    MUL = '*',
    DIV = '/',
    LB = '(',
    RB = ')',
} TOKENS;

typedef struct _node{
    string text;
    struct _node *left;
    struct _node *right;
}node;

node* node_new(string text, node* left, node* right);
void tree_destroy(node* n);

int which_func(char* str);

void plase_mult(string *str);

node* parse(string str);
node* plus_minus(string str);
node* mult(string str);
node* brackets(string str);
node* power(string str);

node* function(string str);
node* ln(string str);

#endif // _PARSER_H_
