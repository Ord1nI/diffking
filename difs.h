#ifndef _DIFS_H_
#define _DIFS_H_

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

string parse(string str);
string plus_minus(string str);
string mult(string str);
string brackets(string str);
string power(string str);

string function(string str);
string ln(string str);

#endif // _DIFS_H_
