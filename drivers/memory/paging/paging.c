#include "paging.h"

#include "drivers/memory/heap/heap.h"

void paging_load_directory(uint32_t* page_directory); /* The NASM function that loads a page directory */

static uint32_t* current_page_directory = 0;

struct paging* map_new_4gb(uint8_t flags) {
    /* We configure the paging */
    /* ................................................................................................................. */
    uint32_t* page_directory = kzalloc(sizeof(uint32_t) * TOTAL_TABLE_ENTRIES); /* We create the page directory | 1024 total table entries*/

    int offset = 0;

    for (int i = 0; i < TOTAL_TABLE_ENTRIES; i++) { /* 1024 total table entries */
        uint32_t* table_entry = kzalloc(sizeof(uint32_t) * TOTAL_TABLE_ENTRIES); /* Create an entry */

        for (int b = 0; b < TOTAL_TABLE_ENTRIES; b++) { /* 1024 total table entries */
            table_entry[b] = (offset + (b * PAGE_SIZE)) | flags; /* Encodes a table entry | 4096 -> PAGE_SIZE | table_entry[b] = (offset + (b * 4096)) | flags; */
        }

        offset += TOTAL_TABLE_ENTRIES * PAGE_SIZE; /* Calculate the offset | 1024 * 4096 */

        /* Each directory entry has pointer to a single page table */
        page_directory[i] = (uint32_t)table_entry | flags | IS_WRITEABLE_FLAG;

    }

    struct paging* chunk_4gb = kzalloc(sizeof(struct paging)); /* We create a 4gb chunk */

    chunk_4gb->directory_entry = page_directory; /* Set the page directory in the 4gb chunk */

    return chunk_4gb; /* We return the 4gb chunk */

}

void switch_page_directory(uint32_t* page_directory) {
    paging_load_directory(page_directory); /* The CR3 registers contains our page directory */
    current_page_directory = page_directory; /* We set the actual page directory */
}

uint32_t* chunk_4gb_get_directory(struct paging* chunk) {
    return chunk->directory_entry; /* We return the page directory of the actual chunk */
}


void paging_free_4gb(struct paging* chunk) {
	for (int i = 0; i < TOTAL_TABLE_ENTRIES; i++) {
		uint32_t entry = chunk->directory_entry[i];
		uint32_t* table = (uint32_t*)(entry & 0xfffff000);
		kfree(table); // We free each page table
	}

	kfree(chunk->directory_entry); // Free the page directory
	kfree(chunk); // We finally free the 4 gb chunk

}
