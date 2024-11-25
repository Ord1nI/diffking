#ifndef _PARSER_H_
#define _PARSER_H_

#include "myclib/string/mystring.h"

#include <stdio.h>

enum Node_Type {
    NUMBER = 0,
    VARIABLE,
    OPERATION,
    FUNCTION,
};

enum Math_func{
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
};

enum Tokens {
    LB = '(',
    RB = ')',
    MUL = '*',
    PLUS = '+',
    MINUS = '-',
    DIV = '/',
    POW = '^',
    LCB = '{',
    RCB = '}',
};

typedef struct _node{
    long long value;
    enum Node_Type type;
    struct _node *left;
    struct _node *right;
}node;

void tree_destroy(node* n);

int which_func(char* str);

void delete_spaces(string str);
void plase_mult(string str);

node* parse(string str);
node* plus_minus(char** str);
node* mult(char** str);
node* brackets(char** str);
node* power(char** str);
node* function(char** str);
node* getvar(char** str);
node* getnum(char** str);


static void sup_to_graph(FILE* f, node* n);
void to_graph(node* n);

#endif // _PARSER_H_
