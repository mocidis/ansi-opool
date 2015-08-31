#ifndef _ANSI_OBJECT_POOL_H_
#define _ANSI_OBJECT_POOL_H_
#include <pthread.h>
#include <pjlib.h>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* calloc, exit, free */

/* OBJECT POOL */
typedef struct {
    int is_used;
    char *data;
} opool_item_t;

typedef struct {
    opool_item_t *items;
    char *data;
    int capacity;
    int data_size;
    int count;
    pthread_mutex_t mutex;
} opool_t;

void opool_init(opool_t *p_opool, int capacity, int data_size);
opool_item_t *opool_get(opool_t *p_opool);
void opool_free(opool_t *p_opool, opool_item_t *p_item);
#endif
