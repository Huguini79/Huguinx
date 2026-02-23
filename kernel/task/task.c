#include "task.h"
#include "scheduler.h"
#include "drivers/memory/heap/heap.h"

#include "libc/string.h"

#include "status.h"

int task_init(struct task* task);

struct scheduler* task_tail = 0;
struct scheduler* task_head = 0;

struct task* new_task() {
	int res = 0;
	
	struct task* task = kzalloc(sizeof(task)); /* Copy the internal structure of the task (including it's registers) to the memory */
	
	/* No memory error */
	if (!task) {
		res = -ENOMEM;
		return task;
	}
	
	/* Init the task */
	res = task_init(task);
	
	if (res != HUGUINX_ALL_OK) {
		return task;
	}
	
	if (task_head == 0) {
		task_head = task;
		task_tail = task;
		goto out;
	}
	
	/* POR CONTINUAR */
}
