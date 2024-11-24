#include "myclib/string/mystring.h"
#include "parser.h"


int main() {
    node* n = parse("x^2-32*x+3*\\cos{x^2+2}*x^x*2");
    to_graph(n);
    tree_destroy(n);
}
