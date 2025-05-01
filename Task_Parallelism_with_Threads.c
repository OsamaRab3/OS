#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000

typedef struct {
    int *array;
} ThreadData;

int* generate_array() {
    int* array = malloc(sizeof(int) * ARRAY_SIZE);
    if (array == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100 + 1;
    }

    return array;
}

void *addArray(void *args){
    ThreadData *data = (ThreadData*)args;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data->array[i] += 5;
    }
    pthread_exit(NULL);
}

void *subArray(void *args){
    ThreadData *data = (ThreadData*)args;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data->array[i] -= 3;
    }
    pthread_exit(NULL);
}

void *mulArray(void *args){
    ThreadData *data = (ThreadData*)args;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data->array[i] *= 3;
    }
    pthread_exit(NULL);
}

int main() {
    int *array = generate_array();
    printf("First 10 elements before operations:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    ThreadData data = { .array = array };
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, addArray, &data);
    pthread_join(t1, NULL);

    pthread_create(&t2, NULL, subArray, &data);
    pthread_join(t2, NULL);



    pthread_create(&t3, NULL, mulArray, &data);
    pthread_join(t3, NULL);

    printf("First 10 elements after operations:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    free(array);
    return 0;
}
