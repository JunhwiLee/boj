#include <stdio.h>
int main(){
    int a = 8;
    int* p = &a;

    printf("a = %d\n", a);
    printf("p = %p\n", p);
    printf("pp = %p\n", &p);
    printf("a = %d\n", *p);
}