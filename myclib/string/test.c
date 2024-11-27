#include "mystring.h"
#include <stdio.h>


int main() {
    string str = string_new("privetiki");
    string_push_back(&str,'a');
    string str2 = string_substr(&str,4,str.length-1);
    printf("%zu",str2.length);
    string_destroy(&str);
    string_destroy(&str2);
    string str3 = string_new("privetiki");
    string_insert(&str3,'4',3);
    string_insert(&str3,'4',3);
    string_insert(&str3,'4',3);
    string_insert(&str3,'4',3);
    puts(str3.str);
    string_delete(&str3,);
    puts(str3.str);
}
