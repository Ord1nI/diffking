#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BIG_GROW_FACTOR 1.5
#define GROW_AFTER_REACHING 5000
#define SMALL_GROW_FACTOR 1.25


typedef struct {
    void* data;
    size_t length;
    size_t capacity;
    size_t data_size;
}vector;
 
typedef struct {
    void* data;
    size_t length;
    size_t capacity;
    size_t data_size;
    size_t pos;
}vector_with_iterator;


vector vector_new(size_t cap, size_t ds);
void vector_push_back(vector* vect, void* data);
void* vector_begin(vector* vect);
void* vector_pos(vector* vect, size_t pos);
void* vector_end(vector* vect);
void vector_destroy(vector* vect);
static bool _vector_need_grow(vector* vect);
static void _vector_grow(vector* vect);

vector_with_iterator vector_with_iterator_new(size_t cap, size_t ds);
void* vector_with_iterator_move_to_pos(vector_with_iterator* vect_with_iter, size_t pos);
void* vector_with_iterator_next(vector_with_iterator* vect_with_iter);
void* vector_with_iterator_prev(vector_with_iterator* vect_with_iter);
void* vector_with_iterator_get(vector_with_iterator* vect_with_iter);

