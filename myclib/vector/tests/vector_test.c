#include "../vector.h"
#include <stdio.h>
#include <assert.h>


int main() {
    vector vect = vector_new(4,sizeof(int));

    for(int i = 0; i<100; i++) {
        vector_push_back(&vect, &i);
    }
     
    for (int i = 0; i<100; i++) {
        printf("%d\n",*((int*)vector_pos(&vect,i)));
        assert(*((int*)vector_pos(&vect,i)) == i);
    }
    vector_destroy(&vect);
}
