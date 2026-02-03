#ifndef TASK_H
#define TASK_H

#include "process.h"
#include "scheduler.h"

#include "drivers/memory/paging/paging.h"

#include <stdint.h>
#include <stddef.h>

/* WARNING: we are working in a 32 bit operating system, and we follow an especific model of registers and concepts, that AMD and Intel defined in their manuals for 32 bit processors and systems. If you want to create multitasking for 64 bit enviroments, you have to put differents registers (for example: eax <- 32 bit | rax <- 64 bit), and you have to see others kernel code to learn multitasking in 64 bit, or follow the concepts of 64 bit of AMD (recommended) or Intel (I don't recommend reading Intel manuals) */

/* Also, task_struct doesn't have the things for software multitasking, the implementaction and structure of software multitasking is in our scheduler, and the implementation of loading a process is in our process implementation, this task_struct only defines the internal struct of a task (like the registers, the page directory, and obviously, a pointer to the process, because a task contains a process, a task id, it's registers, page directory etc...) */

struct task_struct {

	int pid;

	struct paging* page_directory; /* The page directory of the task */

	/* Registers */

	/* General purpose registers ( 32 bit registers ) */
	/* ////////////////////////////////////////////// */
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	/* ////////////////////////////////////////////// */

	/* Control and context registers ( 32 bit registers ) */
	/* ////////////////////////////////////////////// */
	uint32_t eip;
	uint32_t cs; /* Code Segment */
	uint32_t eflags; /* EFLAGS ( 32 bit ) | please, don't confuse eflags with flags, flags are the 16 bit version and the 32 bit version is the eflags */
	uint32_t esp; /* The stack */
	uint32_t ss; /* Stack Segment */
	/* ////////////////////////////////////////////// */

	struct process* process; /* A pointer to our process struct (Here is the code of the process) The task contains the process, and the task gives to the process a page directory, registers, pid etc... */

};

void init_multitasking();

void execute_task(struct process* processs); /* Don't confuse, we pass to the function a process, but this process converts to a task that contains it's task id, it's page directory, it's registers etc... */
/* A process it's only code that the cpu can execute, and a task it's a structure to give page directory, registers, pid to a process, finally, we see the result as a task, but it's the result of the process with the structure of the task (pid, page directory, registers .........) */
/* In libc/stdio.h we renombrate this function as exec(), but internally it's execute_task */

#endif
