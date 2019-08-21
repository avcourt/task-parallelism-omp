#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

/* OpenMP Parallel Quicksort Using Tasking
 *
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

void seq_quick_sort (int p, int r, int *data){
    if (p < r) {
        int q = partition (p, r, data);
        seq_quick_sort (p, q - 1, data);
        seq_quick_sort (q + 1, r, data);
    }
}

void quick_sort (int p, int r, int *data, int low_limit) {
    if (p < r) {
        if ((r - p) < low_limit) {
            seq_quick_sort(p, r, data);
        }
        else {
            int q = partition (p, r, data);
            #pragma omp task firstprivate(data, low_limit, r, q)
                quick_sort (p, q - 1, data, low_limit);
            #pragma omp task firstprivate(data, low_limit, r, q)
                quick_sort (q + 1, r, data, low_limit);
        }
    }
}

void par_quick_sort (int n, int *data, int low_limit) {
    #pragma omp parallel
    {
        #pragma omp single nowait
            quick_sort (0, n, data, low_limit);
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

int main (int argc, char *argv[]){
    int i, n, low_limit, *data;
    double start, end;

    if (argc != 4) {
        printf ("./tasks num_elems threshold num_threads\n");
        return 1;
    }
    n = atoi(argv[1]);
    low_limit = atoi(argv[2]);
    int threads = atoi(argv[3]);    			// Requested number of threads
    int processors = omp_get_num_procs();    	// Available processors


    if (threads > processors) {
        printf("Warning: %d threads requested, will run_omp on %d processors available\n",threads, processors);
    }

	
	omp_set_num_threads(threads);
 
    // Generate the array.
    data = (int *)malloc (sizeof (int) * n);
    for ( i=0; i<n; i++ ) {
        data[i] = rand();
    }

    start = omp_get_wtime();
    par_quick_sort (n - 1, &data[0], low_limit);
    end = omp_get_wtime();
    printf("%.4f\n", end - start);

    validate_sort (n, &data[0]);

    free (data);

    return 0;
}
