#ifndef _TREE_H_
#define _TREE_H_

#include <stdbool.h>

enum Node_Type {
    NUMBER = 0,
    FNUMBER,
    VARIABLE,
    OPERATION,
    FUNCTION,
    DIVNUMBER,
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
    FRAC,
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

union value{
    long long d;
    long double f;
};

typedef struct _node{
    union value value;
    enum Node_Type type;
    struct _node *left;
    struct _node *right;
}node;

node* node_new_ll(enum Node_Type type, long long value, node* left, node* right);
node* node_new_lf(enum Node_Type type, long double value, node* left, node* right);
node* node_new_number(long long value);
node* copy_node(node* to_copy);
node* copy_tree(node* strat_node);

void promote_left(node* n);
void promote_right(node* n);

bool compare_tree(node* left, node* right);

void tree_destroy(node* n);


#endif // _TREE_H_
