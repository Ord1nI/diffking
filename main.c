#include "myclib/string/mystring.h"
#include "parser.h"
#include "tree.h"
#include "dif.h"


int main() {
    string s = string_new("\\sin{x^2}");

    node* n = parse(s);

    to_graph(n, "./start.gv");

    dif(n);
    simplify_tree(n);

    to_graph(n, "./after_simp.gv");

    string a = build_tree(n);

    puts(a.str);



    string_destroy(&a);
    string_destroy(&s);
    tree_destroy(n);
}
