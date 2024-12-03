#include "mystring.h"
#include <stdio.h>

int main() {
    string str = string_new_empty(2);
    string_concatinate_c_str(&str,"14");
    string_push_back(&str,'a');
    string_push_back(&str,'a');
    string_push_back(&str,'a');
    puts(str.str);
    string_destroy(&str);
}
