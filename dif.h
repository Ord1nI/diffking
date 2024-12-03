#ifndef _DIF_H_
#define _DIF_H_

#include "myclib/string/mystring.h"
#include "tree.h"

node* dif_cp(node* n);

void dif(node* n);

static inline void dif_operators(node* n);
static inline void dif_function(node* n);

static inline void dif_plus(node* n);
static inline void dif_minus(node* n);
static inline void dif_div(node* n);
static inline void dif_mul(node* n);
static inline void dif_pow(node* n);

static inline void dif_ln(node* n);
static inline void dif_sin(node* n);
static inline void dif_cos(node* n);
static inline void dif_sqrt(node* n);
static inline void dif_tg(node* n);
static inline void dif_ctg(node* n);
static inline void dif_arcsin(node* n);
static inline void dif_arccos(node* n);
static inline void dif_arctg(node* n);
static inline void dif_arcctg(node* n);

void simplify_tree(node* n);
static void _simplify_tree(node* n);
static inline void simplify_operations(node* n);
static inline void simplify_mul(node* n);
static inline void simplify_plus(node* n);
static inline void simplify_div(node* n);
static inline void simplify_pow(node* n);
static inline void simplify_minus(node* n);

string build_tree(node* n);

static long long powll(long long x, long long y);

#endif // _DIF_H_
