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

/* TASK */
#define TASK_PROGRAM_VIRTUAL_ADDRESS 0x400000
#define TASK_USER_PROGRAM_STACK_SIZE 1024 * 16
#define TASK_PROGRAM_VIRTUAL_STACK_ADDRESS_START 0x3FF000
#define TASK_PROGRAM_VIRTUAL_STACK_ADDRESS_END 0x3FF000 - TASK_USER_PROGRAM_STACK_SIZE

#define USER_DATA_SEGMENT 0x23 /* DS */
#define USER_CODE_SEGMENT 0x1b /* CS */

#endif
