#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stddef.h>

typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;

struct heap_table {
    HEAP_BLOCK_TABLE_ENTRY* entries; /* The entries of the heap table */
    size_t total_entries; /* Total heap entries in the heap table */
};

struct heap_struct {
    struct heap_table* heap_table; /* The heap table */
    void* start_address; /* Start address of the heap data pool */
};

void* kmalloc(size_t size);
void* kzalloc(size_t size);
void kfree(void* ptr);

void heap_init();

#endif