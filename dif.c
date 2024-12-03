#include "myclib/string/mystring.h"

#include "dif.h"
#include "tree.h"

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>


void dif(node* n) {
    switch(n->type) {
        case VARIABLE:

            if(n->left != NULL || n->right != NULL) {
                abort();
            }

            n->type = NUMBER;
            n->value.d = 1;

            return;

        case OPERATION:

            dif_operators(n);
            return;

        case FUNCTION:

            dif_function(n);
            return;

        case NUMBER:

            if(n->left != NULL || n->right != NULL) {
                abort();
            }

            n->value.d = 0;

            return;
    }
}

static inline void dif_operators(node* n) {
    switch(n->value.d) {
        case MUL:

            dif_mul(n);
            return;

        case PLUS:

            dif(n->left);
            dif(n->right);
            return;

        case MINUS:

            dif(n->left);
            dif(n->right);
            return;

        case DIV:

            dif_div(n);
            return;

        case POW: {

            dif_pow(n);
            return;

        }
        abort();
    }
}

static inline void dif_function(node* n) {
    switch(n->value.d) {
        case LOG:
        case LN: {
            dif_ln(n);
        }
            return;
        case SIN: {
            dif_sin(n);
        }
            return;
        case COS: {
            dif_cos(n);
        }
            return;
        case SQRT: {
            dif_sqrt(n);
        }
            return;
        case TG: {
            dif_tg(n);
        }
            return;
        case CTG: {
            dif_ctg(n);
        }
            return;
        case ARCSIN: {
            dif_arcsin(n);
        }
            return;
        case ARCCOS: {
            dif_arccos(n);
        }
            return;
        case ARCTG: {
            dif_arctg(n);
        }
            return;
        case ARCCTG: {
            dif_arcctg(n);
        }
            return;
    }
}


static inline void dif_div(node* n) {

    node* du = dif_cp(n->left);
    node* dv = dif_cp(n->right);

    node* new_left_left_node = node_new_ll(OPERATION, MUL, du, n->right);
    node* new_left_right_node = node_new_ll(OPERATION, MUL, dv, n->left);

    node* new_right_left_node = copy_tree(n->right);
    node* new_right_right_node = node_new_number(2);

    node* new_left_node = node_new_ll(OPERATION, MINUS, new_left_left_node, new_left_right_node);
    node* new_right_node = node_new_ll(OPERATION, POW, new_right_left_node, new_right_right_node);

    n->type = OPERATION;
    n->value.d = DIV;
    n->left = new_left_node;
    n->right = new_right_node;
}

static inline void dif_mul(node* n) {

    node* du = dif_cp(n->left);
    node* dv = dif_cp(n->right);

    node* new_left_node = node_new_ll(OPERATION, MUL, du, n->right);
    node* new_right_node = node_new_ll(OPERATION, MUL, dv, n->left);

    n->type = OPERATION;
    n->value.d = PLUS;
    n->left = new_left_node;
    n->right = new_right_node;
}

static inline void dif_pow(node* n) {

    node* main_cp = copy_tree(n);
    main_cp->right = node_new_ll(OPERATION, MINUS, main_cp->right, node_new_number(1)) ;

    node* new_right_node = node_new_ll(OPERATION, MUL, n->right, main_cp);

    dif(n->left);

    n->value.d = MUL;
    n->left = n->left;
    n->right = new_right_node;
}

static inline void dif_ln(node* n) {

    node* new_left = dif_cp(n->left);


    n->type = OPERATION;
    n->value.d = DIV;
    n->left = new_left;
    n->right = n->left;
}

static inline void dif_sin(node* n) {
    node* new_right_node = copy_tree(n);
    new_right_node->value.d = COS;

    dif(n->left);

    n->type = OPERATION;
    n->value.d = MUL;
    n->right = new_right_node;
}

static inline void dif_cos(node* n) {
    node* new_right_right_node = copy_tree(n);
    new_right_right_node->value.d = SIN;

    dif(n->left);

    node* new_left_node = node_new_number(-1);
    node* new_right_node = node_new_ll(OPERATION, MUL, n->left, new_right_right_node);

    n->type = OPERATION;
    n->value.d = MUL;
    n->left = new_left_node;
    n->right = new_right_node;

}

static inline void dif_sqrt(node* n) {
    node* new_right_node = node_new_ll(OPERATION, DIV, node_new_number(1), node_new_number(2));

    n->type = OPERATION;
    n->value.d = POW;
    n->right = new_right_node;

    dif(n);
}

static inline void dif_tg(node* n) {

    node* new_right_left_node = node_new_ll(FUNCTION, COS, n->left, NULL);

    node* new_right_node = node_new_ll(OPERATION, POW, new_right_left_node, node_new_number(2));

    n->type = OPERATION;
    n->value.d = DIV;
    n->left = dif_cp(n->left);
    n->right = new_right_node;
}
static inline void dif_ctg(node* n) {

    node* new_right_right_left_node = node_new_ll(FUNCTION, COS, n->left, NULL);

    node* new_right_right_node = node_new_ll(OPERATION, POW, new_right_right_left_node, node_new_number(2));

    node* new_right_node = node_new_ll(OPERATION, DIV, dif_cp(n->left), new_right_right_node);

    n->type = OPERATION;
    n->value.d = MUL;
    n->left = node_new_number(-1);
    n->right = new_right_node;

}

static inline void dif_arcsin(node* n) {

    node* new_right_left_right_node = node_new_ll(OPERATION, POW, n->left, node_new_number(2));
    node* new_right_left_node = node_new_ll(OPERATION, MINUS, node_new_number(1), new_right_left_right_node);
    node* new_right_node = node_new_ll(FUNCTION, SQRT, new_right_left_node, NULL);

    n->type = OPERATION;
    n->value.d = DIV;
    n->left = dif_cp(n->left);
    n->right = new_right_node;
}

static inline void dif_arccos(node* n) {

    node* new_right_left_right_node = node_new_ll(OPERATION, POW, n->left, node_new_number(2));
    node* new_right_left_node = node_new_ll(OPERATION, MINUS, node_new_number(1), new_right_left_right_node);
    node* new_right_node = node_new_ll(FUNCTION, SQRT, new_right_left_node, NULL);

    node* new_left_node = node_new_ll(OPERATION, MUL, node_new_number(-1), dif_cp(n->left));

    n->type = OPERATION;
    n->value.d = DIV;
    n->left = new_left_node;
    n->right = new_right_node;
}

static inline void dif_arctg(node* n) {
    node* new_right_right_node = node_new_ll(OPERATION, POW, n->left, node_new_number(2));
    node* new_right_node = node_new_ll(OPERATION, PLUS, node_new_number(1), new_right_right_node);

    n->type = OPERATION;
    n->value.d = DIV;
    n->left = dif_cp(n->left);
    n->right = new_right_node;

}

static inline void dif_arcctg(node* n) {

    node* new_right_right_node = node_new_ll(OPERATION, POW, n->left, node_new_number(2));
    node* new_right_node = node_new_ll(OPERATION, PLUS, node_new_number(1), new_right_right_node);

    node* new_left_node = node_new_ll(OPERATION, MUL, node_new_number(-1), dif_cp(n->left));

    n->type = OPERATION;
    n->value.d = DIV;
    n->left = new_left_node;
    n->right = new_right_node;
}

node* dif_cp(node* n) {

    node* cp = copy_tree(n);
    dif(cp);

    return cp;
}

void simplify_tree(node* n) {
    if(n->left != NULL) {
        simplify_tree(n->left);
    }

    if(n->right != NULL) {
        simplify_tree(n->right);
    }

    _simplify_tree(n);
}

static void _simplify_tree(node* n) {

    switch(n->type) {
        case OPERATION:

            simplify_operations(n);

            return;
        case FUNCTION:

            if (n->left->type == OPERATION) simplify_tree(n->left);

            return;

    }
}

static inline void simplify_operations(node* n) {
    switch(n->value.d) {
        case MUL:
            simplify_mul(n);
            return;
        case PLUS:
            simplify_plus(n);
            return;
        case MINUS:
            simplify_minus(n);
            return;
        case DIV:
            simplify_div(n);
            return;

        case POW:
            simplify_pow(n);
            return;
    }
}

static inline void simplify_mul(node* n) {
    if(n->left->type == NUMBER) {

        if(n->left->value.d == 1) {
            promote_right(n);
            return;
        }

        if(n->left->value.d == 0) {
            tree_destroy(n->left);
            tree_destroy(n->right);
            n->left = NULL;
            n->right = NULL;

            n->type = NUMBER;
            n->value.d = 0;

            return;
        }

        if(n->right->type == NUMBER) {

            n->value.d = n->left->value.d * n->right->value.d;
            n->type = NUMBER;

            free(n->left);
            free(n->right);

            n->left = NULL;
            n->right = NULL;
            return;
        }

        if(n->right->type == FNUMBER) {
            n->value.f = n->left->value.d * n->right->value.f;
            n->type = FNUMBER;

            free(n->left);
            free(n->right);

            n->left = NULL;
            n->right = NULL;
            return;

        }

        if (n->right->type == OPERATION && n->right->value.d == MUL) {

        }


    }

    if(n->left->type == FNUMBER) {
        if(n->right->type == NUMBER) {

            n->value.f = n->left->value.f * n->right->value.f;
            n->type = NUMBER;

            free(n->left);
            free(n->right);

            n->left = NULL;
            n->right = NULL;
            return;
        }

        if(n->right->type == FNUMBER) {
            n->value.f = n->left->value.f * n->right->value.f;
            n->type = FNUMBER;

            free(n->left);
            free(n->right);

            n->left = NULL;
            n->right = NULL;
            return;

        }

        if (n->right->type == OPERATION && n->right->value.d == MUL) {

        }


    }

    if(n->left->type == DIVNUMBER) {

    }

    if (compare_tree(n->left, n->right)) {
        n->value.d = POW;

        tree_destroy(n->right->left);
        tree_destroy(n->right->right);
        n->right->left = NULL;
        n->right->right = NULL;

        n->right->type = NUMBER;
        n->right->value.d = 2;
    }

}

static inline void simplify_div(node* n) {

}

static inline void simplify_pow(node* n) {

}

static inline void simplify_plus(node* n) {
    if (n->left->type == NUMBER) {
        if (n->left->value.d == 0) {
            promote_right(n);
            return;
        }

        if (n->right->type == NUMBER) {
            n->value.d = n->left->value.d + n->right->value.d;
            n->type = NUMBER;

            free(n->left);
            free(n->right);

            n->left = NULL;
            n->right = NULL;
            return;
        }

        if (n->right->type == FNUMBER) {
            n->value.f = n->left->value.d + n->right->value.f;
            n->type = FNUMBER;

            free(n->left);
            free(n->right);

            n->left = NULL;
            n->right = NULL;
            return;
        }
    }

    if (n->right->type == NUMBER) {
        if (n->right->value.d == 0) {
            promote_left(n);
            return;
        }
    }


}

static inline void simplify_minus(node* n) {
    if (n->left->type == NUMBER) {

        if (n->right->type == NUMBER) {
            n->value.d = n->left->value.d - n->right->value.d;
            n->type = NUMBER;

            free(n->left);
            free(n->right);

            n->left = NULL;
            n->right = NULL;
            return;
        }

        if (n->right->type == FNUMBER) {
            n->value.f = n->left->value.d - n->right->value.f;
            n->type = FNUMBER;

            free(n->left);
            free(n->right);

            n->left = NULL;
            n->right = NULL;
            return;
        }
    }

    if (n->right->type == NUMBER) {
        if (n->right->value.d == 0) {
            promote_left(n);
            return;
        }
    }


}

string build_tree(node* n) {

    assert(n != NULL);

    string res;
    switch (n->type) {
        case VARIABLE:

            if(n->left != NULL || n->right != NULL) {
                abort();
            }

            res = string_new_empty(2);
            string_push_back(&res,n->value.d);

            return res;

        case DIVNUMBER:
        case OPERATION: {

            string left = string_new_empty(10);
            string right = string_new_empty(10);

            if (n->left->type == OPERATION) {
                string_push_back(&left, '(');
            }

            if (n->right->type == OPERATION) {
                string_push_back(&right, '(');
            }

            string tmp_left = build_tree(n->left);
            string_concatinate_c_str(&left, tmp_left.str);
            string_destroy(&tmp_left);

            string tmp_right = build_tree(n->right);
            string_concatinate_c_str(&right, tmp_right.str);
            string_destroy(&tmp_right);

            if (n->left->type == OPERATION) {
                string_push_back(&left, ')');
            }

            if (n->right->type == OPERATION) {
                string_push_back(&right, ')');
            }

            string_push_back(&left, n->value.d);
            string_concatinate_c_str(&left, right.str);

            string_destroy(&right);

            return left;

        }
        case FUNCTION:

            switch(n->value.d) {
                case LOG:
                    res = string_new("\\log{");
                    break;
                case LN:
                    res = string_new("\\ln{");
                    break;
                case SIN:
                    res = string_new("\\sin{");
                    break;
                case COS:
                    res = string_new("\\cos{");
                    break;
                case SQRT:
                    res = string_new("\\sqrt{");
                    break;
                case TG:
                    res = string_new("\\tg{");
                    break;
                case CTG:
                    res = string_new("\\ctg{");
                    break;
                case ARCSIN:
                    res = string_new("\\arcsin{");
                    break;
                case ARCCOS:
                    res = string_new("\\arccos{");
                    break;
                case ARCTG:
                    res = string_new("\\arctg{");
                    break;
                case ARCCTG:
                    res = string_new("\\arcctg{");
                    break;

            }
            string tmp = build_tree(n->left);

            string_concatinate_c_str(&res, tmp.str);
            string_push_back(&res, '}');

            string_destroy(&tmp);
            return res;

        case NUMBER: {

            if(n->left != NULL || n->right != NULL) {
                abort();
            }

            char num[22];
            sprintf(num,"%lld", n->value.d);

            res = string_new_empty(5);
            string_concatinate_c_str(&res, num);

            return res;
        }

        case FNUMBER: {

            if(n->left != NULL || n->right != NULL) {
                abort();
            }

            char num[22];
            sprintf(num,"%.5Lf", n->value.f);

            res = string_new_empty(5);
            string_concatinate_c_str(&res, num);

            return res;
        }
    }
}

static long long powll(long long x, long long y) {
    if (y == 0) {
        return 1;
    }

    long long res = 1;

    while (y > 0) {
        if (y % 2 == 1) {
            res *= x;
        }
        x *= x;
        y /= 2;
    }
    return res;
}
