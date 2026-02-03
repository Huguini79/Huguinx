#ifndef SCHEDULER_H
#define SCHEDULER_H

struct scheduler {
    int task_tail;
    int task_head;

    int prev;
    int next;
};

#endif
