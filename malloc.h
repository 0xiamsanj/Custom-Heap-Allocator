#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#define META_BLOCK_SIZE sizeof(struct meta_block)   //Block size for the meta-data block
#define align4(x) (((((x)-1)>>2)<<2)+4)     //Aligning the size for allocation of blocks

void* global_base = NULL;

typedef struct meta_block* t_block;            //Using typedef as t_block for simple accessing of the meta-data structure

//Defining the meta-data block
struct meta_block{
    size_t  size;
    t_block next;
    int     free;
    char    data[1];
};

t_block find_block (t_block *last, size_t size){
    t_block block = global_base;
    while(block && ( block->size >= size && block->free)){
        *last = block;
        block = block->next;
    }
    return block;
}

t_block heap_extension (t_block last, size_t size){
    t_block block;
    block = sbrk(0);
    if (sbrk(META_BLOCK_SIZE+size)==(void*)-1)
        return NULL;
    block->size = size;
    block->free = 0;
    if (last)
        last->next = block;
    return block;
}
/*
   Splitting a large block into requried space
   */
void split_block(t_block block, size_t size){
    t_block new;
    new = (t_block)b->data + size;
    new->size = block->size - size - BLOCK_SIZE;
    new->next = block->next;
    new->free = 1;
    block->size = size;
    block->next = new;
}

void *c_malloc(size_t size){
    t_block     last,block;
    size = align4(size);
    if (global_base){
        last = global_base;
        block = find_block(&last, size);
        if (block) {
            if (block->size - size >= (META_BLOCK_SIZE+4))
                split_block(block,size);
            block->free = 0;
        }
        else {
            block = heap_extension(last,size);
            if (!block)
                return NULL;
        }
    }
    else {
        block = heap_extension(NULL, size);
        if (!block)
            return NULL;
        global_base = block;
    }
    return (block->data);
}
