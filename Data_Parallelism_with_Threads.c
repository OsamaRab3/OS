#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000
#define THREADS_NUMBER 7

typedef struct {
    int *array;
    int start;
    int end;
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


void *incrementArray(void *args) {
    ThreadData* data = (ThreadData*)args;
    for (int i = data->start; i < data->end; i++) {
        // data[i] += 2;
        data->array[i]+=2;
    }

    pthread_exit(NULL);
}


int main(){
    int * array = generate_array();
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // here i will work as a Data parallelism so need to divid array to parts 
        //    then applay the same function on all parts then conquer all parts in one array 

    // i will create a threads 
    pthread_t threads[THREADS_NUMBER];
    ThreadData thread_data[THREADS_NUMBER];
    int chunk = ARRAY_SIZE / THREADS_NUMBER ; 

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i=0;i<THREADS_NUMBER;i++){
        thread_data[i].array = array;
        thread_data[i].start = i * chunk; 
        thread_data[i].end = (i == THREADS_NUMBER - 1) ? ARRAY_SIZE : (i + 1) * chunk;


        pthread_create(&threads[i], NULL, incrementArray, &thread_data[i]);
    }

    for (int i = 0; i < THREADS_NUMBER; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time_ms = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
                             (end_time.tv_nsec - start_time.tv_nsec) / 1e6;
                             
    printf("Execution Time: %.3f ms\n", elapsed_time_ms);

    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);


    return 0;

       


    
}