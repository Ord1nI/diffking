#include "myclib/string/mystring.h"
#include "parser.h"

#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

string delete_spaces(string str) {
    string new_string = string_new_empty(str.capacity);
    for (size_t i = 0; i < str.length; i++) {
        const char* digit = string_at_pos(&str,i);
        if (*digit != ' ') {
            string_push_back(&new_string, *digit);
        }
    }
    return new_string;
}


int which_func(char* str) {
    char* functions[] = {"log","ln","sin","cos","sqrt","tg","ctg","arcsin","arccos","arctg","arcctg"};
    for (int i = 0; i < sizeof(functions)/sizeof(char*); i++) {
        if (strcmp(functions[i], str) == 0) {
            return i;
        }
    }
}

void tree_destroy(node* n) {
    if (n->left != NULL) {
        tree_destroy(n->left);
    }
    if (n->right != NULL) {
        tree_destroy(n->right);
    }
    free(n);
}

node* parse(char* str) {
    return plus_minus(&str);
}

node* plus_minus(char** str) {
    node* left = mult(str);
    if (**str == PLUS || **str == MINUS) {
        node* res = malloc(sizeof(node));
        res->left = left;
        res->type = OPERATION;

        res->value = **str;

        (*str)++;
        res->right = plus_minus(str);

        return res;
    }
    return left;
}

node* mult(char** str) {
    node* left = power(str);
    if (**str == MUL || **str == DIV) {
        node* res = malloc(sizeof(node));

        res->left = left;
        res->type = OPERATION;

        res->value = **str;

        (*str)++;
        res->right = mult(str);

        return res;
    }
    return left;
}

node* power(char** str) {
    node* left = brackets(str);
    if (**str == POW) {
        node* res = malloc(sizeof(node));

        res->left = left;
        res->type = OPERATION;

        res->value = **str;

        (*str)++;
        res->right = power(str);

        return res;
    }
    return left;
}

node* brackets(char** str) {
    if (**str == LB || **str == LCB) {
        (*str)++;

        node* res = plus_minus(str);

        if (**str != RB && **str != RCB) {
            abort();
        }

        (*str)++;

        return res;
    }
    return function(str);
}

node* function(char** str) {

    if (**str == '\\') {
        node* res = malloc(sizeof(node));

        string text = string_new_empty(5);

        (*str)++;

        while(**str != '{') {
            string_push_back(&text,**str);
            (*str)++;
        }

        res->type = FUNCTION;
        res->value = which_func(text.str);
        res->left = brackets(str);
        res->right = NULL;

        string_destroy(&text);

        return res;
    }

    return getvar(str);
}



node* getvar(char** str) {
    if (isalpha(**str)) {
        node* res = malloc(sizeof(node));
        res->type = VARIABLE;
        res->value = **str;
        res->left = NULL;
        res->right = NULL;

        (*str)++;

        return res;
    }
    return getnum(str);

}

node* getnum(char** str) {
    node* res = malloc(sizeof(node));

    char* old_str = *str;

    res->value = 0;
    res->type = NUMBER;
    res->left = NULL;
    res->right = NULL;

    while(**str >= '0' && **str <= '9') {
        res->value *= 10;
        res->value += **str - '0';
        (*str)++;
    }

    if (old_str == *str) {
        abort();
    }

    return res;
}

static void sup_to_graph(FILE* f, node* n) {
    assert(n != NULL);

    switch(n->type) {
        case NUMBER:
            fprintf(f, "%d [label=\"%d\"]\n", n, n->value);
            break;
        case VARIABLE:
            fprintf(f, "%d [label=\"%c\"]\n", n, n->value);
            break;
        case OPERATION:
            fprintf(f, "%d [label=\"%c\"]\n", n, n->value);
            break;
        case FUNCTION:
            switch(n->value) {
                case LOG:
                    fprintf(f, "%d [label=\"log\"]\n", n);
                    break;
                case LN:
                    fprintf(f, "%d [label=\"ln\"]\n", n);
                    break;
                case SIN:
                    fprintf(f, "%d [label=\"sin\"]\n", n);
                    break;
                case COS:
                    fprintf(f, "%d [label=\"cos\"]\n", n);
                    break;
                case SQRT:
                    fprintf(f, "%d [label=\"sqrt\"]\n", n);
                    break;
                case TG:
                    fprintf(f, "%d [label=\"tg\"]\n", n);
                    break;
                case CTG:
                    fprintf(f, "%d [label=\"ctg\"]\n", n);
                    break;
                case ARCSIN:
                    fprintf(f, "%d [label=\"arcsin\"]\n", n);
                    break;
                case ARCCOS:
                    fprintf(f, "%d [label=\"arccos\"]\n", n);
                    break;
                case ARCTG:
                    fprintf(f, "%d [label=\"arctg\"]\n", n);
                    break;
                case ARCCTG:
                    fprintf(f, "%d [label=\"arcctg\"]\n", n);
                    break;
            }
            break;
    }

    if (n->left != NULL) {
        fprintf(f, "\"%d\" -> %d;\n", n, n->left);
        sup_to_graph(f, n->left);
    }

    if (n->right != NULL) {
        fprintf(f, "\"%d\"-> \"%d\";\n", n, n->right);
        sup_to_graph(f, n->right);
    }
}

void to_graph(node* n) {
    FILE *f = fopen("./graph.gv", "w");

    fputs("digraph G {\n", f);

    sup_to_graph(f, n);

    fputc('}', f);
    fclose(f);
}

