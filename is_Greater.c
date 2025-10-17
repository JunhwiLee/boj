#include <stdio.h>

int isGreater(int x, int y) {
  int k = (~x) + 1;
  int z = k + y;
  return ((z ^ ((x ^ y) & (z ^ y))) >> 31) & 1;
}

int main(){
    int a = 0x7fffffff;
    int b = 0x80000000;
    int check = 1;
    for(int i = -10000; i<=10000; i++){
        for(int j = -10000; j<=10000; j++){
            if((i > j ? 1 : 0) != isGreater(i, j)){
                printf("%d %d", i, j);
                check = 0;
            }
        }
    }
    if(check)
        printf("All Clear\n");
}