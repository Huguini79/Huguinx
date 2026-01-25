#ifndef TASK_H
#define TASK_H

#include <stdint.h>
#include <stddef.h>

struct task_struct {
	unsigned long state; /* The state of the task */
	int prio; /* Priority of the task */
	int pid; /* Pid of the task (Proccess Identifier) */
};

void init_multitasking();

#endif
