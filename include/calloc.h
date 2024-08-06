#include "malloc.h"
#define align4(x) (((((x)-1)>>2)<<2)+4)     //Aligning the size for allocation of blocks

void* calloc(size_t number, size_t size){
    size_t      *new_block;
    size_t      i,size4;

    new_block = c_malloc(number*size);
    if(new_block){
        size4 = align4(size) ;
        for( i=0;i<size4;i++){
            new_block[i] = 0;
        }
    }
    return new_block;
}
