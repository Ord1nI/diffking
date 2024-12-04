#include "myclib/string/mystring.h"
#include "parser.h"
#include "tree.h"
#include "dif.h"


int main() {
    string s = string_new("(x^2)/(\\ln{x})");

    node* n = parse(s);

    to_graph(n, "./start.gv");

    dif(n);

    to_graph(n, "./after_dif.gv");
    simplify_tree(n);

    to_graph(n, "./after_simp.gv");

    string a = build_tree(n);

    puts(a.str);

    string_destroy(&a);
    string_destroy(&s);
    tree_destroy(n);
}
