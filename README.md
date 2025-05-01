# OS
## Task 1: Sum a Large Array Using Data Parallelism with Threads

### Objective:
Practice multi-threading using data parallelism in C.

### Description:
In this task, we will create a large array of integers (e.g., 10 million elements) randomly, divide it into N chunks (where N is the number of threads), and assign each thread to compute the sum of its chunk. After all threads complete, the partial results will be aggregated into a final sum.

### Steps:
1. **Array Generation:**
   - A large array of integers will be generated randomly. For simplicity, we assume an array size of `ARRAY_SIZE = 10,000` elements.
   - The array will contain random integers between 1 and 100.

2. **Divide the Array into Chunks:**
   - The array will be divided into `N` chunks, where `N` is the number of threads (`THREADS_NUMBER`).
   - Each thread will handle one chunk and calculate the sum of the elements within that chunk.

3. **Thread Creation:**
   - `pthread_create` will be used to spawn `THREADS_NUMBER` threads.
   - Each thread will be assigned a specific portion of the array to process.

4. **Summing the Chunks:**
   - Each thread computes the sum of its assigned chunk.
   - After all threads complete, the partial sums are combined to get the total sum.

5. **Execution Time:**
   - The execution time of the entire process will be measured using `CLOCK_MONOTONIC` to track the time taken by the multithreaded summing process.

6. **Final Output:**
   - The first 10 elements of the array before and after processing will be printed for verification.
   - The final sum will also be displayed.

----
