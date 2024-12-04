#include "tree.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>


node* node_new_ll(enum Node_Type type, long long value, node* left, node* right) {
    node* n = (node*)malloc(sizeof(node));
    n->type = type;
    n->value.d = value;
    n->left = left;
    n->right = right;
    return n;
}

node* node_new_lf(enum Node_Type type, long double value, node* left, node* right) {
    node* n = (node*)malloc(sizeof(node));
    n->type = type;
    n->value.f = value;
    n->left = left;
    n->right = right;
    return n;
}

node* node_new_number(long long value) {
    node* n = (node*)malloc(sizeof(node));
    n->type = NUMBER;
    n->value.d = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

node* copy_node(node* to_copy) {
    node* n = (node*)malloc(sizeof(node));
    memcpy(n, to_copy, sizeof(node));
    return n;
}

node* copy_tree(node* start_node) {
    node* res = copy_node(start_node);

    if(start_node->left != NULL) {
        res->left = copy_tree(start_node->left);
    }
    if(start_node->right != NULL) {
        res->right = copy_tree(start_node->right);
    }
    return res;
}

void promote_left(node* n) {

    free(n->right);

    node* to_free = n->left;

    memmove(n, n->left, sizeof(node));

    free(to_free);

}

void promote_right(node* n) {

    free(n->left);

    node* to_free = n->right;

    memmove(n, n->right, sizeof(node));

    free(to_free);
}

bool compare_tree(node* left, node* right) {

    if (left == NULL && right == NULL) {
        return true;
    }

    if (left == NULL || right == NULL) {
        return false;
    }

    if (left->type == right->type &&
        ((compare_tree(left->left, right->left) && compare_tree(left->right, right->right)) ||
        (compare_tree(left->left, right->right) && compare_tree(left->right, right->left)))){

        if (left->type == FNUMBER) {
            if (fabsl(left->value.f - right->value.f) < 0.000001f) {
                return true;
            }
        }

        if (left->value.d == right->value.d) {
            return true;
        }
    }

    return false;

}

void tree_destroy(node* n) {
    if (n == NULL) {
        return;
    }

    if (n->left != NULL) {
        tree_destroy(n->left);
    }
    if (n->right != NULL) {
        tree_destroy(n->right);
    }
    free(n);
}
