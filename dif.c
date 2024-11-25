#include "myclib/string/mystring.h"

#include "dif.h"
#include "parser.h"
#include "stdlib.h"

#include <math.h>


string dif(node* n) {
    string res;
    switch(n->type) {
        case VARIABLE:
            if(n->left != NULL || n->right != NULL) {
                abort();
            }
            res = string_new_empty(2);
            string_push_back(&res,'1');
            return res;
        case OPERATION:
            return dif_operators(n);
        case FUNCTION:
        case NUMBER:
            if(n->left != NULL || n->right != NULL) {
                abort();
            }
            res = string_new_empty(2);
            string_push_back(&res,'1');
            return res;
    }
}

string dif_operators(node* n) {
    string left;
    string right;
    switch(n->value) {
        case MUL:
            if (n->left->type == VARIABLE || n->right->type == VARIABLE) {
                left = dif(n->left);
                right = dif(n->right);
                string_push_back(&left, '*');
                string_concatinate_c_str(&left, right.str);
                string_destroy(&right);
                return left;
            }
        case PLUS:
            left = dif(n->left);
            right = dif(n->right);
            string_push_back(&left, '+');
            string_concatinate_c_str(&left, right.str);
            string_destroy(&right);
            return left;
        case MINUS:
            left = dif(n->left);
            right = dif(n->right);
            string_push_back(&left, '+');
            string_concatinate_c_str(&left, right.str);
            string_destroy(&right);
            return left;
        case DIV:
            break;
        case POW:
            if (n->left->type == VARIABLE && n->right->type == NUMBER) {
                left = string_new_empty(sizeof(char)*(int)log10(n->right->value));
                sprintf(left.str, "%d", n->right->value);
            }
            return left;
            break;

    }
}
