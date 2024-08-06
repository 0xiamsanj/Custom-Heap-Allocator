#include "include/calloc.h"
#include <stdio.h>

int main(void){
    int size = 4;
    int* ptr = (int*)calloc(size,sizeof(int));
    printf("Memory allocated: %p",ptr);
    printf("\nEnter the values in the array");
    for(int i=0;i<size;i++){
        scanf("%d",&ptr[i]);
    }
    for(int i=0;i<size;i++){
        printf("\n%d",ptr[i]);
    }
}
