#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

/* OpenMP Parallel Quicksort - Sections with depth checking
 *		Checking for depth allows for nested parallelism.
 *  @author: ANDREW VAILLANCOURT
 *  2019
 */

int partition (int p,   int r,   int *data){
    int x = data[p];
    int k = p;
    int l = r + 1;
    int t;

    while (1) {
        do
            k++;
        while ((data[k] <= x) && (k < r));

        do
            l--;
        while (data[l] > x);

        while (k < l) {
            t = data[k];
            data[k] = data[l];
            data[l] = t;

            do
                k++;
            while (data[k] <= x);

            do
                l--;
            while (data[l] > x);
        }

        t = data[p];
        data[p] = data[l];
        data[l] = t;
        return l;
    }
}

void seq_quick_sort (int p,int r,int *data){
    if (p < r) {
        int q = partition (p, r, data);
        seq_quick_sort (p, q - 1, data);
        seq_quick_sort (q + 1, r, data);
    }
}

void quick_sort (int p, int r, int *data, int low_limit, int threads) {
    if (p < r) {
        if ((r - p) < low_limit || threads == 1) {
            seq_quick_sort(p, r, data);
        } else {
            int q = partition(p, r, data);
            #pragma omp parallel firstprivate(data, p, q, r)
            {
				#pragma omp single nowait
				{
                	#pragma omp task
                    quick_sort(p, q - 1, data, low_limit, threads/2);
                 	#pragma omp task
                    quick_sort(q + 1, r, data, low_limit, threads - threads/2);
				}
            }
        }
    }
}


void validate_sort (int n, int *data){
    int i;
    for (i = 0; i < n - 1; i++) {
        if (data[i] > data[i+1]) {
            printf ("ERROR: Validate failed\n");
        }
    }
}


void insertion_sort(int a[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        int j, v = a[i];
        for (j = i - 1; j >= 0; j--) {
            if (a[j] <= v)
                break;
            a[j + 1] = a[j];
        }
        a[j + 1] = v;
    }
}

int main (int argc, char *argv[]){

    int i, n, low_limit;
    int *data;
    double start, end;
    if (argc != 4) {
        printf ("./sections num_elems threshold num_threads\n");
        return 1;
    }
    n = atoi(argv[1]);
    low_limit = atoi(argv[2]);
    int threads = atoi(argv[3]);    			// Requested number of threads
    int processors = omp_get_num_procs();		// Available processors

    omp_set_nested(1);
    if (omp_get_nested() != 1) {
        puts("Warning: Nested parallelism desired but unavailable");
    }

    if (threads > processors) {
        printf("Warning: %d threads requested, will run_omp on %d processors available\n",threads, processors);
    }

//    int max_threads = omp_get_max_threads();	// Max available threads
//    if (threads > max_threads)    				// Requested threads are more than max available
//    {
//        printf("Error: Cannot use %d threads, only %d threads available\n",
//               threads, max_threads);
//        return 1;
//    }

    // Generate the array
    data = (int *)malloc (sizeof (int) * n);
    for ( i=0; i<n; i++ ) {
        data[i] = rand();
    }

    start = omp_get_wtime();
    quick_sort (0, n - 1, &data[0], low_limit, threads);
    end = omp_get_wtime();
    printf("%.4f\n", end - start);

    validate_sort (n, &data[0]);
    free (data);

    return 0;
}
