//
// Created by dmitry on 10.09.18.
//

#include <glob.h>

#ifndef PRIORITY_QUEUE_PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_PRIORITY_QUEUE_H

#define STATUS_OK            (0)
#define STATUS_ERR_INVALID  (-1)
#define STATUS_ERR_NOMEM    (-2)
#define STATUS_ERR_NODATA   (-3)
#define STATUS_ERR_SINGULAR (-0x10)

struct Item {
    int n_priority;
    void *p_data;
};

struct _PrQueue {
    int n_capacity;
    size_t n_size;
    struct Item *p_item;
};


typedef struct _PrQueue PrQueue;

int prQueueCreate(size_t n_capacity, PrQueue **pp_queue);

/* Brief: Create priority queue with the specified capacity.
Input:
n_capacity
- The queue capacity.
pp_queue
- Pointer to the variable to fill with new queue pointer.
Output:
*pp_queue
- Will contain a pointer to a newly created queue.
Return:
STATUS_OK
- Operation completed succesfully
STATUS_ERR_INVALID - Invalid argumeents passed.
 STATUS_ERR_NOMEM
- Not enough memory to allocate the queue.
 */

int prQueuePush(PrQueue *p_queue, int n_priority, void *p_item);

int prQueuePop(PrQueue *p_queue, int *pn_priority, void **pp_item);

int prQueuePeek(PrQueue *p_queue, int *pn_priority, void **pp_item);

int prQueueGetCount(PrQueue *p_queue, size_t *pn_count);

void prQueueRelease(PrQueue *p_queue);


#endif //PRIORITY_QUEUE_PRIORITY_QUEUE_H
