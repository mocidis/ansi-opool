#include "object-pool.h"

void opool_init(opool_t *p_opool, int capacity, int data_size) {
	int i;
	p_opool->items = calloc(capacity, sizeof(opool_t));
	p_opool->data = calloc(capacity, data_size);
	p_opool->capacity = capacity;
	p_opool->data_size = data_size;
	p_opool->count = 0;
	for( i = 0; i < p_opool->capacity; i++ ) {
		p_opool->items[i].data = (void *)&(p_opool->data[i*data_size]);
	}
}

opool_item_t *opool_get(opool_t *p_opool) {
	opool_item_t *p_item = NULL;
	int i = 0;
	pthread_mutex_lock(&p_opool->mutex);

	if(p_opool->count == p_opool->capacity) {
		printf( "object pool is full");
	}
	else {
		do {
			srand (time(NULL));
			i = rand() % p_opool->capacity + 1;
			p_item = &(p_opool->items[i]);
		} while(p_item->is_used);
	//	printf("Pick object at idx:%d", i);
		p_item->is_used = 1;
		++(p_opool->count);
	}

	pthread_mutex_unlock(&p_opool->mutex);
	return p_item;
}

void opool_free(opool_t *p_opool, opool_item_t *p_item) {
	pthread_mutex_lock(&p_opool->mutex);
	p_item->is_used = 0;
	--(p_opool->count);
	pthread_mutex_unlock(&p_opool->mutex);
}
