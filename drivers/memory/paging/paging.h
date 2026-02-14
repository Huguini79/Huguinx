#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stddef.h>

/* Paging Flags */
#define CACHE_DISABLED_FLAG 0b00010000
#define WRITE_THROUGH_FLAG 0b00001000
#define ACCESS_FROM_ALL_FLAG 0b00000100
#define IS_WRITEABLE_FLAG 0b00000010
#define IS_PRESENT_FLAG 0b00000001

#define TOTAL_TABLE_ENTRIES 1024
#define PAGE_SIZE 4096

struct paging {
    uint32_t* directory_entry; /* Pointer that points to a Page directory */
};

struct paging* map_new_4gb(uint8_t flags); /* Map 4GB to a virtual address space (we use this in multitasking, and in the initialization of the kernel <- so we map 4 gb to the kernel) */
void switch_page_directory(uint32_t* page_directory); /* We use this to switch from different page directories, for example, page directories of proccesses or from the kernel */
void enable_paging(); /* The NASM function that enables paging */
void paging_free_4gb(struct paging* chunk);
uint32_t* chunk_4gb_get_directory(struct paging* chunk); /* We get the page directory of a virtual address space that it's mapped <- (chunk) */

#endif
