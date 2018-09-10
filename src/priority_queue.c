//
// Created by dmitry on 10.09.18.
//

#include "priority_queue.h"
#include <stdlib.h>

int prQueueCreate(size_t n_capacity, PrQueue ** pp_queue) {
    *pp_queue = malloc(sizeof(PrQueue));
    if (*pp_queue == NULL) {
        return STATUS_ERR_NOMEM;
    }
    (*pp_queue)->n_capacity = n_capacity;
    (*pp_queue)->n_size = 0;
    (*pp_queue)->p_item = malloc(n_capacity * sizeof(struct Item));
    if ((*pp_queue)->p_item == NULL) {
        free(*pp_queue);
        return STATUS_ERR_NOMEM;
    }
    return STATUS_OK;
}

int prQueuePush(PrQueue * p_queue, int n_priority, void * p_item) {
    if (p_item == NULL || p_queue == NULL) {
        return STATUS_ERR_INVALID;
    }
    if (p_queue->n_size > p_queue->n_capacity - 1) {
        return STATUS_ERR_NOMEM;
    }
    p_queue->p_item[p_queue->n_size].p_data = p_item;
    p_queue->p_item[p_queue->n_size].n_priority = n_priority;
    size_t i = p_queue->n_size;
    while ((i > 0) &&
            p_queue->p_item[i].n_priority <
            p_queue->p_item[(i - 1) / 2].n_priority) {
        // swap
        struct Item tmp = p_queue->p_item[i];
        p_queue->p_item[i] = p_queue->p_item[(i - 1) / 2];
        p_queue->p_item[(i - 1) / 2] = tmp;
        i = (i - 1) / 2;
    }
    p_queue->n_size++;
    return STATUS_OK;
}

int prQueuePop(PrQueue * p_queue, int * pn_priority, void ** pp_item) {
    if (p_queue == NULL) {
        return STATUS_ERR_INVALID;
    }
    if (p_queue->n_size == 0) {
        return STATUS_ERR_NODATA;
    }

    // result
    *pp_item = p_queue->p_item[0].p_data;
    *pn_priority = p_queue->p_item[0].n_priority;

    // reorganization
    p_queue->n_size--;
    p_queue->p_item[0] = p_queue->p_item[p_queue->n_size];
    // remove old tail
    p_queue->p_item[p_queue->n_size].n_priority = 0;
    p_queue->p_item[p_queue->n_size].p_data = NULL;

    int i = 0;
    while (2 * i + 1 < p_queue->n_size) {
        int n_left  = 2 * i + 1;
        int n_right = 2 * i + 2;
        int j = n_left;
        if ((n_right < p_queue->n_size) && (p_queue->p_item[n_right].n_priority < p_queue->p_item[n_left].n_priority)) {
            j = n_right;
        }
        if (p_queue->p_item[i].n_priority <= p_queue->p_item[j].n_priority) {
            break;
        }
        struct Item tmp = p_queue->p_item[i];
        p_queue->p_item[i] = p_queue->p_item[j];
        p_queue->p_item[j] = tmp;
        i = j;
    }
    return STATUS_OK;
}

int prQueuePeek(PrQueue * p_queue, int * pn_priority, void ** pp_item) {
    if (p_queue == NULL) {
        return STATUS_ERR_INVALID;
    }
    if (p_queue->n_size == 0) {
        return STATUS_ERR_NODATA;
    }

    // result
    *pp_item = p_queue->p_item[0].p_data;
    *pn_priority = p_queue->p_item[0].n_priority;
    return STATUS_OK;
}

int prQueueGetCount(PrQueue * p_queue, size_t * pn_count) {
    if (p_queue == NULL) {
        return STATUS_ERR_INVALID;
    }
    *pn_count = p_queue->n_size;
    return STATUS_OK;
}

void prQueueRelease(PrQueue * p_queue) {
    if (p_queue != NULL) {
        if (p_queue->p_item != NULL) {
            free(p_queue->p_item);
        }
        free(p_queue);
    }
}