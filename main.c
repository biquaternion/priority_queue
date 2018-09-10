#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "priority_queue.h"


int main() {
    // test data
    int n_index = 0;
    int n_items[20] = {24, 90, 54, 5, 8,
                       71, 61, 23, 32, 55,
                       28, 58, 78, 37, 9,
                       51, 30, 98, 20, 18};

    PrQueue * pq;
    int status;
    status = prQueueCreate(10, &pq);

    size_t pn_count;
    status = prQueueGetCount(pq, &pn_count);
    assert(pn_count == 0);

    for (n_index = 0; n_index != 10; ++n_index) {
        int priority = n_items[n_index];
        status = prQueuePush(pq, priority, &n_items[n_index]);
        assert(status == STATUS_OK);
    }
    status = prQueueGetCount(pq, &pn_count);
    assert(pn_count == 10);

    status = prQueuePush(pq, 33, &n_items[n_index+1]);
    assert(status == STATUS_ERR_NOMEM);

    status = prQueueGetCount(pq, &pn_count);
    assert(pn_count == 10);

    int *garbage[5];
    int *heads[5];
    for (int i = 0; i != 5; ++i) {
        int priority;
        status = prQueuePeek(pq, &priority, &heads[i]);
        status = prQueuePop(pq, &priority, &garbage[i]);
        assert(heads[i] == garbage[i]);
    }

    status = prQueueGetCount(pq, &pn_count);
    assert(pn_count == 5);

    for (; n_index != 20; ++n_index) {
        int priority = n_items[n_index];
        status = prQueuePush(pq, priority, &n_items[n_index]);
        status = prQueuePop(pq, &priority, &n_items[n_index]);
    }

    status = prQueueGetCount(pq, &pn_count);
    assert(pn_count == 5);

    for (int i = 0; i != 5; ++i) {
        int priority;
        int item;
        status = prQueuePop(pq, &priority, &item);
    }

    status = prQueueGetCount(pq, &pn_count);
    assert(pn_count == 0);

    int priority;
    int item;
    status = prQueuePop(pq, &priority, &item);
    assert(status == STATUS_ERR_NODATA);

    prQueueRelease(pq);

    return 0;
}