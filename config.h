#ifndef CONFIG_H
#define CONFIG_H

/* GDT */

/* Total GDT Segments */
#define HUGUINX_TOTAL_GDT_SEGMENTS 6 // <- NULL Segment, Kernel code segment, Kernel data segment, User, User, TSS Segment

/* IDT */

/* Selectors */
#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

/* Total IDT Interrupts */
#define HUGUINX_TOTAL_INTERRUPTS 512

/* DISK */
#define HUGUINX_SECTOR_SIZE 512 /* We define the size of the sectors <- 512 Bytes*/

#endif
