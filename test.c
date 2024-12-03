#include <stdio.h>
#include <limits.h>

union u {
    int a;
    float b;
};

int main() {
    union u a;
    printf("%f",a.b);

}
