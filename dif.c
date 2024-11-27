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
            string_push_back(&res,'0');
            return res;
    }
}

string dif_operators(node* n) {
    string left;
    string right;
    switch(n->value) {
        case MUL:
            if (n->left->type == NUMBER) {
                char num[sizeof(char)*(int)log10(n->left->value)+1];
                sprintf(num, "%d", n->left->value);

                left = string_new_empty(10);
                right = dif(n->right);

                string_concatinate_c_str(&left, num);
                string_push_back(&left, '*');
                string_concatinate_c_str(&left, right.str);
                string_destroy(&right);
                return left;
            }
            if (n->right->type == NUMBER) {
                char num[sizeof(char)*(int)log10(n->right->value)+1];
                sprintf(num, "%d", n->right->value);

                left = dif(n->left);

                string_concatinate_c_str(&left, num);
                string_push_back(&left, '*');
                string_concatinate_c_str(&left, left.str);

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
            string_push_back(&left, '-');
            string_concatinate_c_str(&left, right.str);
            string_destroy(&right);
            return left;
        case DIV:

            if (n->left->type == NUMBER && n->right->type == NUMBER) {
                char num[sizeof(char)*(int)log10(n->left->value)+1];
                char num2[sizeof(char)*(int)log10(n->right->value)+1];
                sprintf(num, "%d", n->left->value);
                sprintf(num2, "%d", n->right->value);

                left = string_new(num);
                string_push_back(&left, '/');
                string_concatinate_c_str(&left, num2);

                return left;
            }

            if (n->left->type == NUMBER) {
                char num[sizeof(char)*(int)log10(n->left->value)+1];
                sprintf(num, "%d", n->left->value);

                left = string_new(num);

                node* tmp_node = (node*)malloc(sizeof(node));
                tmp_node->type = OPERATION;
                tmp_node->value = POW;
                tmp_node->left = n->right;
                tmp_node->right = (node*)malloc(sizeof(node));
                tmp_node->right->type = NUMBER;
                tmp_node->right->value = -1;

                right =  dif_operators(tmp_node);

                string_push_back(&left, '*');
                string_concatinate_c_str(&left, right.str);

                string_destroy(&right);
                free(tmp_node->right);
                free(tmp_node);

                return left;

            if (n->right->type == NUMBER) {
                char num[sizeof(char)*(int)log10(n->right->value)+1];
                sprintf(num, "%d", n->right->value);

                left = string_new(num);

                right =  dif_operators(tmp_node);

                string_push_back(&left, '*');
                string_concatinate_c_str(&left, right.str);

                string_destroy(&right);
                free(tmp_node->right);
                free(tmp_node);

                return left;
            }
            }
        case POW:
            if (n->left->type == VARIABLE && n->right->type == NUMBER) {
                char num[sizeof(char)*(int)log10(n->right->value)+1];
                sprintf(num, "%d", n->right->value);

                left = string_new(num);

                string_push_back(&left, 'x');
                string_push_back(&left, '^');

                sprintf(num, "%d", n->right->value-1);
                string_concatinate_c_str(&left, num);

                return left;
            }
            return left;
            break;

    }
}
