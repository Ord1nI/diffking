#include "mystring.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

string string_new_empty(size_t cap) {
    string str;
    str.length = 0;
    str.capacity = cap+1;

    str.str = (char*)calloc(str.capacity,1);

    return str;
}

string string_new(char* c_str) {
    assert(c_str != NULL);
    string my_str;
    my_str.length = strlen(c_str);
    my_str.capacity = my_str.length*_new_string_size(&my_str);

    my_str.str = (char*)calloc(my_str.capacity,1);

    memcpy(my_str.str, c_str, my_str.length+1);

    return my_str;
}

const char* string_at_pos(string* my_str, size_t pos) {
    assert(my_str != NULL);
    return pos < my_str->length ? my_str->str+pos:NULL;
}

void string_concatinate_c_str(string* my_str, char * c_str) {
    assert(c_str != NULL);

    size_t c_str_len = strlen(c_str);

    if (_string_need_grow(my_str, c_str_len)) {
        _string_grow(my_str);
    }


    memcpy(my_str->str + my_str->length, c_str, c_str_len+1);

    my_str->length+=c_str_len;
}

void string_push_back(string* my_str, char c) {
    assert(my_str != NULL);


    if (_string_need_grow(my_str, 1)) {
        _string_grow(my_str);
    }

    *(my_str->str+my_str->length) = c;
    *(my_str->str+my_str->length+1) = '\0';

    my_str->length++;
}

void string_insert(string* my_str, char c, size_t pos) {
    assert(my_str != NULL);


    if (_string_need_grow(my_str, 1)) {
        _string_grow(my_str);
    }

    memmove(my_str->str+pos+2, my_str->str+pos+1, my_str->length-pos);
    *(my_str->str+pos+1) = c;
    my_str->length++;
}

void string_shrink(string* my_str, size_t num_to_shrink) {
    assert(my_str != NULL);
    assert(num_to_shrink < my_str->length);

    if (num_to_shrink < my_str->length) {
        return;
    }

    my_str->length-=num_to_shrink;
    my_str->str[my_str->length] = '\0';
}

string string_substr(string* my_str, size_t start, size_t end) {
    assert(my_str != NULL);
    assert(end < my_str->length);

    string res_my_str;
    res_my_str.length = end-start+1;
    res_my_str.capacity = res_my_str.length*_new_string_size(&res_my_str);
    res_my_str.str = (char*)calloc(res_my_str.capacity,1);

    memcpy(res_my_str.str, my_str->str+start, res_my_str.length);
    *(res_my_str.str+res_my_str.length) = '\0';

    return res_my_str;

}

void string_destroy(string* my_str) {
    assert(my_str != NULL);

    free(my_str->str);
    my_str->str=NULL;
}

static bool _string_need_grow(string* my_str, size_t append_num) {
    if (my_str->length+append_num+1 <= my_str->capacity) {
        return false;
    }
    return true;
}

static float _new_string_size(string* my_str) {
    if (my_str->length > 1000){
        return SMALL_GROW_FACTOR;
    } else {
        return BIG_GROW_FACTOR;
    }
}

static void _string_grow(string* my_str) {
   assert(my_str->str != NULL);

   my_str->capacity*=_new_string_size(my_str);
   my_str->str = (char*)realloc(my_str->str, my_str->capacity);
}
