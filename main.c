#include "myclib/string/mystring.h"
#include "parser.h"
#include "dif.h"


int main() {
    string s = string_new("x^-2-\\sin{15}");
    node* n = parse(s);
    to_graph(n);
    string a = dif(n);
    puts(a.str);
    string_destroy(&s);
    string_destroy(&a);
}
