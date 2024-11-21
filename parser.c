#include "myclib/string/mystring.h"
#include "parser.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>




node* node_new(string text, node* left, node* right) {

    node* res = (node*)malloc(sizeof(node));
    res->text = text;
    res->left = left;
    res->right = right;

    return res;
}

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

void plase_mult(string *str) {
    char prev = *string_at_pos(str,0);
    const char* cur = string_at_pos(str, 1);
    while(*cur != '\0') {
        if (isdigit(prev) && (isalpha(*cur) || *cur == '\\')) {
            string_insert(str,'*',cur-1-str->str);
        }
        else if (isalpha(prev) && isdigit(*cur)) {
            string_insert(str,'*',cur-1-str->str);
        }
        else if (prev == ')' && *cur == '(') {
            string_insert(str,'*',cur-1-str->str);
        }
        prev = *cur;
        cur++;
    }
}

int which_func(char* str) {
    char* functions[] = {"log","ln","sin","cos","sqrt","tg","ctg","arcsin","arccos","arctg","arcctg"};
    for (int i = 0; i < sizeof(functions)/sizeof(char*);i++) {
        if (strcmp(functions[i], str) == 0) {
            return i;
        }
    }
}

node* parse(string str) {
    string newstr = delete_spaces(str);
    plase_mult(&newstr);
    string_destroy(&str);
    return plus_minus(newstr);
}

void tree_destroy(node* n) {
    if (n->left != NULL) {
        tree_destroy(n->left);
    }
    if (n->right != NULL) {
        tree_destroy(n->right);
    }
    string_destroy(&n->text);
    free(n);
}

node* plus_minus(string str) {
    for (size_t i = 0; i < str.length ; i++) {
        const char* digit = string_at_pos(&str,i);
        if (*digit == LB) {
            digit++;
            i++;
            while(*digit != RB) {
                digit++;
                i++;
            }
        }
        if (*digit == PLUS || *digit == MINUS) {
            node* res = node_new(string_new_empty(2), NULL, NULL);
            string_push_back(&(res->text),*digit);
            res->left = mult(string_substr(&str, 0, i-1));
            res->right = plus_minus(string_substr(&str, i+1, str.length-1));
            string_destroy(&str);
            return res;
        }

    }
    return mult(str);
}

node* mult(string str) {
    for (size_t i = 0; i < str.length ; i++) {
        const char* digit = string_at_pos(&str,i);
        if (*digit == LB) {
            digit++;
            i++;
            while(*digit != RB) {
                digit++;
                i++;
            }
        }
        if (*digit == MUL || *digit == DIV) {
            node* res = node_new(string_new_empty(1), NULL, NULL);
            string_push_back(&(res->text),*digit);
            res->left = power(string_substr(&str,0,i-1));
            res->right = mult(string_substr(&str,i+1,str.length-1));
            string_destroy(&str);
            return res;
        }
    }
    return power(str);
}

node* power(string str) {
    for (size_t i = 0; i < str.length ; i++) {
        const char* digit = string_at_pos(&str,i);
        if (*digit == LB) {
            digit++;
            i++;
            while(*digit != RB) {
                digit++;
                i++;
            }
        }
        if (*digit == POW) {
            node* res = node_new(string_new_empty(1), NULL, NULL);
            string_push_back(&(res->text),*digit);
            res->left = brackets(string_substr(&str,0,i-1));
            res->right = power(string_substr(&str,i+1,str.length-1));
            string_destroy(&str);
            return res;
        }
    }
    return brackets(str);
}

node* brackets(string str) {
    if (*string_at_pos(&str,0) == LB) {
        return plus_minus(string_substr(&str,1,str.length-2));
    }
    return function(str);
}

node* function(string str) {

    const char* digit = string_at_pos(&str,0);

    string func = string_new_empty(10);
    if (*digit == '\\') {
        digit++;
        while(*digit != '{') {
            string_push_back(&func,*digit);
            digit++;
        }
    } else {

        return node_new(str,NULL,NULL);

    }

    switch (which_func(func.str)) {
        case LOG:
        case LN:
            return ln(string_substr(&str,digit-str.str,str.length-1));
        case SIN:
        case COS:
        case SQRT:
        case TG:
        case CTG:
        case ARCSIN:
        case ARCCOS:
        case ARCTG:
        case ARCCTG:
    }
    string_destroy(&func);
    return node_new(str,NULL,NULL);
}

node* ln(string str) {
    return node_new(str,NULL,NULL);
}

/* node* sin(string str) { */

/* } */

/* node* cos(string str) { */

/* } */

/* node* sqrt(string str) { */

/* } */

/* node* tg(string str) { */

/* } */

/* node* ctg(string str) { */

/* } */

/* node* arcsin(string str) { */

/* } */

/* node* arccos(string str) { */

/* } */

/* node* arctg(string str) { */

/* } */

/* node* arcctg(string str) { */

/* } */
