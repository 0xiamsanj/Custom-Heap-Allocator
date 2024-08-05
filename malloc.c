#include "malloc.h"
#include <stdio.h>

int main(void){
    int size = 4;
    int* ptr = (int*)c_malloc(4*sizeof(int));
    printf("Memory allocated: %p",ptr);
    printf("\n");
    ptr[0] = 1;
    ptr[1] = 2;
    for(int i=0;i<size;i++){
        scanf("%d",&ptr[i]);
    }
    for(int i=0;i<size;i++){
        printf("\n%d",ptr[i]);
    }
}
