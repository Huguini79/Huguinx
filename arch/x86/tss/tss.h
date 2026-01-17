// Author: Huguini79
// TSS (Task State Segment) implementation

#ifndef TSS_H
#define TSS_H

#include <stdint.h>

struct tss {
	uint32_t link; // Used in Nesting stacks
	uint32_t esp0; // Kernel stack pointer
	uint32_t ss0; // Kernel stack segment
	/////////////////////////////////////
	/* These are used for privilege level transitions, but we don't require these in modern operating systems */
	uint32_t esp1;
	uint32_t esp2;
	uint32_t ss2;
	/////////////////////////////////////
	uint32_t sr3;
	/////////////////////////////////////
	/* These store the instruction pointer and flags register for task switching */
	uint32_t eip;
	uint32_t eflags;
	/////////////////////////////////////
	/////////////////////////////////////
	/* These store general-purpose registers */
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	/////////////////////////////////////
	/////////////////////////////////////
	/* These are the segment selectors */
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	/////////////////////////////////////
	uint32_t ldtr;
	uint32_t iopb; // Specifies the I/O permission bitmap

}__attribute__((packed));

void tss_load(int tss_segment);

#endif
