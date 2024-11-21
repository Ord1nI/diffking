#include "vector.h"

#include <string.h>
#include <assert.h>
#include <stdbool.h>

vector vector_new(size_t cap, size_t ds) {
    vector vect;
    vect.length = 0;
    vect.capacity = cap;
    vect.data_size = ds;
    vect.data = malloc(cap * ds);

    return vect;
}

vector_with_iterator vector_with_iterator_new(size_t cap, size_t ds) {
    vector_with_iterator vect;
    vect.length = 0;
    vect.capacity = cap;
    vect.data_size = ds;
    vect.data = malloc(cap * ds);
    vect.pos = 0;

    return vect;
}

void vector_push_back(vector* vect,void* data) {
    assert(vect != NULL);
    assert(data != NULL);
    assert(vect->data != NULL);

    if (_vector_need_grow(vect)) {
        _vector_grow(vect);
    }

    memcpy(vect->data+(vect->length*vect->data_size),data,vect->data_size);
    vect->length+=1;
}

void* vector_pos(vector* vect, size_t pos) {
    assert(vect != NULL);
    assert(pos < vect->length);
    return vect->data+(pos*vect->data_size);
}

void* vector_begin(vector* vect) {
    assert(vect != NULL);
    return vect->data;
}

void* vector_end(vector* vect) {
    assert(vect != NULL);
    return vect->data+((vect->length-1)*vect->data_size);
}

void vector_destroy(vector* vect) {
    assert(vect != NULL);

    free(vect->data);
    vect->data = NULL;
}


static bool _vector_need_grow(vector* vect){
    assert(vect->length <= vect->capacity);
    if (vect->length == vect->capacity)
        return true;
    return false;
}
 
void* vector_with_iterator_next(vector_with_iterator* vect_with_iter) {
    assert(vect_with_iter != NULL);
    if (vect_with_iter->pos == vect_with_iter->length) {
        return NULL;
    }
    vect_with_iter->pos++;
    return (vect_with_iter->data+(vect_with_iter->pos * vect_with_iter->data_size));
}
 
void* vector_with_iterator_prev(vector_with_iterator* vect_with_iter) {
    assert(vect_with_iter != NULL);
    if (vect_with_iter->pos == vect_with_iter->length) {
        return NULL;
    }
    vect_with_iter->pos--;
    return (vect_with_iter->data+(vect_with_iter->pos * vect_with_iter->data_size));
}
void* vector_with_iterator_get(vector_with_iterator* vect_with_iter) {
    assert(vect_with_iter != NULL);
    return (vect_with_iter->data+(vect_with_iter->pos * vect_with_iter->data_size));
}

void* vector_with_iterator_move_to_pos(vector_with_iterator* vect_with_iter, size_t pos) {
    assert(pos <= vect_with_iter->length);
    if (pos <= vect_with_iter->length) {
        return NULL;
    }

    vect_with_iter->pos = pos;
    return (vect_with_iter->data+(vect_with_iter->pos * vect_with_iter->data_size));
}

static float _new_vector_size(vector* vect) {
    return vect->capacity>=GROW_AFTER_REACHING?SMALL_GROW_FACTOR:BIG_GROW_FACTOR;
}

static void _vector_grow(vector* vect){
    assert(vect->data != NULL);
    assert(vect->length == vect->capacity);

    vect->capacity*=_new_vector_size(vect);
    vect->data = realloc(vect->data, vect->capacity*vect->data_size);
}

