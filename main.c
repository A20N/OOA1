#include <time.h>
#include <malloc.h>
#include "priorityqueue.h"
#include <stdlib.h>

#define MAX 100000

char *random_string(int size) {
	char *str = (char *) malloc((size + 1) * sizeof(char));
    for (int i = 0; i < size; ++i) {
        str[i] = (rand() % 26) + 'A';
    }
    str[size] = '\0';
    return str;
}

void test_queue() {
    struct priorityqueue_t *p = pqueue_create();
    pqueue_insert(p, "test0", 1);
    pqueue_insert(p, "test1", 2);
    pqueue_insert(p, "test2", 3);
    pqueue_insert(p, "test3", 4);
    pqueue_insert(p, "test4", 5);
    for (int i = 0; i < 5; i++) {
        printf("%s\n", pqueue_extractMin(p));
    }

    printf("Test1 finished\n\n");


    pqueue_insert(p, "test0", 1);
    pqueue_insert(p, "test1", 2);
    pqueue_insert(p, "test2", 3);
    pqueue_insert(p, "test3", 4);
    pqueue_insert(p, "test4", 5);
    pqueue_decreaseKey(p, "test2", 6);
    for (int i = 0; i < 5; i++) {
        printf("%s\n", pqueue_extractMin(p));
    }
    printf("Test2 finished\n");
    pqueue_destroy(p);
    printf("Test3 finished\n");

}

int main(int argc, char **argv) {
    test_queue();
    return 0;
}
