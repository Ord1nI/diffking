#ifndef MYSTRING_H_
#define MYSTRING_H_

#include <string.h>
#include <stdbool.h>

#define BIG_GROW_FACTOR 2
#define SMALL_GROW_FACTOR 1.5

typedef struct {
    char* str;
    size_t length;
    size_t capacity;
}string;


string string_new_empty(size_t len);
string string_new(char* c_str);

void string_concatinate_c_str(string* my_str, char * c_str);
void string_push_back(string* my_str, char c);

void string_insert(string* my_str, char c, size_t pos);

void string_delete(string* my_str, size_t pos);

string string_substr(string* my_str, size_t start, size_t end);

const char* string_at_pos(string* my_str, size_t pos);

void string_destroy(string* my_str);

static bool _string_need_grow(string* my_str, size_t append_num);
static void _string_grow(string* my_str);
static float _new_string_size(string* my_str);

#endif // MYSTRING_H_
