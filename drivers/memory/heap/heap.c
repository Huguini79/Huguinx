#include "heap.h"

#include "status.h"

#include "libc/stdio.h"
#include "libc/string.h"

#include <stdbool.h>

struct heap_struct kernel_heap;
struct heap_table kernel_heap_table;

/* Check if we have a valid heap table */
static int validate_table(void* ptr, void* end, struct heap_table* table) {
    int res = 0;
    size_t size = (size_t)(end - ptr); /* The actual size of the heap table */
    size_t total_blocks = size / 4096; /* The total blocks in the heap table | 4 KB of block size */

    if (table->total_entries != total_blocks) { /* Check if we have the same number of memory blocks */
        res = -2; /* Error - 2 */
    }

    return res;

}

/* Check if the pointer is aligned to the heap block size */
static bool validate_alignment(void* ptr) {
    return ((unsigned int)ptr % 4096) == 0; /* 4 KB of block size */
}

/* We create the heap */
int heap_create(struct heap_struct* heap, void* ptr, void* end, struct heap_table* table) {
    int res = 0;

    int ptr_validate_alignment = validate_alignment(ptr);
    int end_validate_alignment = validate_alignment(end);

    /* Check if the start and end of the heap table is correct */
    if (!ptr_validate_alignment || !end_validate_alignment) {
        res = -2;
        return res;
    }

    /* /////////////////////////////////////////////////////////////// */
    memset(heap, 0, sizeof(struct heap_struct)); /* We set the heap */
    heap->start_address = ptr; /* The start address of the heap */
    heap->heap_table = table; /* The table */
    /* /////////////////////////////////////////////////////////////// */

    res = validate_table(ptr, end, table); /* Validate the heap table */
    
    if(res < 0) {
        return res;
    }

    /* //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
    size_t size = sizeof(HEAP_BLOCK_TABLE_ENTRY) * table->total_entries; /* Calculate the table size */
    memset(table->entries, 0x00, size); /* Set all the entries to free <- basically, init the tables, this allows us to have all the blocks free at the start of the kernel, and then can do kmalloc() correctly with free blocks, until we don't have more memory blocks free */
    /* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

    return res;

}

/* For example, if we put 4000, this will returns us 4096, or 8000 -> 8192 | Conclusion: This returns us the perfect size in bytes */
static uint32_t heap_align_value_to_upper(uint32_t val) {
    if ((val % 4096) == 0) { /* 4 KB of block size */
        return val;
    }

    val = (val - (val % 4096)); /* 4 KB of block size */
    val += 4096; /* 4 KB of block size */

    return val;

}

/* Get the type of the entry <- FREE OR TAKEN */
static int free_or_taken(HEAP_BLOCK_TABLE_ENTRY entry) {
    int free_or_taken = entry & 0x0f;
    return free_or_taken;
}

/* Get the start block in the heap table */
int heap_get_start_block(struct heap_struct* heap, uint32_t total_blocks) {
    struct heap_table* heap_table = heap->heap_table;
    
    int bc = 0;
    int bs = -1;

    /* Check all the entries of the heap table */
    for (size_t i = 0; i < heap_table->total_entries; i++) {
        if (free_or_taken(heap_table->entries[i]) != 0x00) {
            bc = 0;
            bs = -1;
            continue;
        }
        /* If this is the first block */
        if (bs == -1) {
            bs = i;
        }
        bc++;
        if (bc == total_blocks) {
            break;
        }

    }

    if (bs == -1) {
        return -3; /* NO MEMORY ERROR */
    }

}

/* Get the block address <- we use this in malloc */
void* block_to_address(struct heap_struct* heap, int block) {
    return heap->start_address + (block * 4096); /* 4 KB of block size */
}

/* Mark the blocks taken */
void blocks_taken(struct heap_struct* heap, int start_block, int total_blocks) {
    int end_block = (start_block + total_blocks) - 1;

    HEAP_BLOCK_TABLE_ENTRY entry = 0x01 | 0b010000000; /* 0x01 -> TAKEN | 0b010000000 -> this is the first block */

    if (total_blocks > 1) {
        entry |= 0b10000000;
    }

    for (int i = start_block; i <= end_block; i++) {
        heap->heap_table->entries[i] = entry;
        entry = 0x01; /* Mark the blocks as taken | 0x01 */

        if (i != end_block - 1) {
            entry |= 0b10000000;
        }

    }

}

/* Malloc blocks */
void* heap_malloc_blocks(struct heap_struct* heap, uint32_t total_blocks) {
    void* address = 0;

    int start_block = heap_get_start_block(heap, total_blocks); /* The start block */
    
    if (start_block < 0) {
        return address;
    }

    address = block_to_address(heap, start_block); /* Converts the block to and address */

    blocks_taken(heap, start_block, total_blocks); /* Marks the blocks as taken */

}

/* Marks the blocks free */
void blocks_free(struct heap_struct* heap, int starting_block) {
    struct heap_table* table = heap->heap_table; /* The heap table */
    
    for (int i = starting_block; i < (int)table->total_entries; i++) {
        HEAP_BLOCK_TABLE_ENTRY entry = table->entries[i];
        table->entries[i] = 0x00; /* Mark the blocks as free, 0x00 */

        if (!(entry & 0b10000000)) {
            break;
        }

    }

}

/* Converts an address to a block */
int address_to_block(struct heap_struct* heap, void* address) {
    int address_to_block = ((int)(address - heap->start_address)) / 4096; /* 4 KB of block size */
    return address_to_block;
}

void* heap_malloc(struct heap_struct* heap, size_t size) {
    size_t aligned_size = heap_align_value_to_upper(size); /* This converts an incorrect size to a correct size (if needed) */
    uint32_t total_blocks = aligned_size / 4096; /* 4 KB -> HEAP_BLOCK_SIZE */

    return heap_malloc_blocks(heap, total_blocks);

}

void heap_free(struct heap_struct* heap, void* ptr) {
    int address_to_block_variable = address_to_block(heap, ptr); /* This converts the address to a block */

    blocks_free(heap, address_to_block_variable); /* Mark the blocks as free */

}

void heap_init() {
    int total_table_entries = 104857600 / 4096; /* Calculate total table entries | heap_size / block_size*/
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY*)(0x00007E00); /* Configure the heap table */
    kernel_heap_table.total_entries = total_table_entries; /* Configure total table entries */

    void* end = (void*)(0x01000000 + 104857600); /* The end of the heap table */

    int res = heap_create(&kernel_heap, (void*)0x01000000, end, &kernel_heap_table); /* Create the heap */

    if (res < 0) {
        huguinx_logs("FAILED TO CREATE HEAP");
    }

}

void* kmalloc(size_t size) {
    return heap_malloc(&kernel_heap, size);
}

void kfree(void* ptr) {
    heap_free(&kernel_heap, ptr);
}

void* kzalloc(size_t size)
{
    void* ptr = kmalloc(size);
    if (!ptr)
        return 0;

    memset(ptr, 0x00, size);
    return ptr;
}