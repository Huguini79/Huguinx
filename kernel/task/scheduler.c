/* Software Multitasking implementation */

#include "task.h"
#include "drivers/memory/heap/heap.h"

#include "libc/stdlib.h"
#include "libc/stdio.h"

struct scheduler* current_running_task = 0;

struct scheduler* task_tail = 0;
struct scheduler* task_head = 0;

struct scheduler* current_task() {
	if (!current_running_task) {
		huguinx_print("ERROR: No current tasks are running at the moment");
		goto out;
	}


	return current_running_task;



	out:
		return NULL;

}

struct scheduler* get_next_task() {
	if (!current_running_task->next) {
		return task_head;
	}

	return current_running_task->next;

}

static void remove_task_from_list(struct scheduler* task) {
	/* Try of all the ways to remove that task from the task list */
	if (task->prev) {
		task->prev->next = task->next;
	}

	if (task == task_head) {
		task_head = task->next;
	}

	if (task == task_tail) {
		task_tail = task->prev;
	}

	if (task == current_running_task) {
		current_running_task = get_next_task();
	}

}
