#include "object-pool.h"
#include <stdlib.h>
#include <string.h>
#include "pthread.h"
#include <unistd.h>
#include <time.h>

opool_t opool;
const char *s = "Cong hoa xa hoi chu nghia";

void * do_test(void *args) {
	int i;
    struct timespec rqtp;
    rqtp.tv_sec = 0;
    rqtp.tv_nsec = 100 * 1000 * 1000;

	for (i = 0; i < 100; i++) {
		opool_item_t *p_item = opool_get(&opool);
		strncpy(p_item->data, s, strlen(s));
		printf("%d: %s\n", i, p_item->data);
        nanosleep(&rqtp, NULL);
		opool_free(&opool, p_item);
	}
    return NULL;
}

int main() {
	int i;
	pthread_t thread1;

	opool_init(&opool, 10, strlen(s) + 10);

	pthread_create(&thread1, NULL, (void *)do_test, &opool);
	sleep(1);
	do_test(&opool);

	pthread_join(thread1, NULL);

	return 0;
}
