#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

/* Serial Quicksort
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

void seq_quick_sort (int p,int r,int *data){
    if (p < r) {
        int q = partition (p, r, data);
        seq_quick_sort (p, q - 1, data);
        seq_quick_sort (q + 1, r, data);
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
    int i, n;
    int *data;
    double start, end;

    if (argc != 2) {
        printf ("a.out num_elems\n");
        return 1;
    }

    n = atoi(argv[1]);
    
    // Generate the array
    data = (int *)malloc (sizeof (int) * n);
    for ( i=0; i<n; i++ ) {
        data[i] = rand();
    }

    start = omp_get_wtime();
    seq_quick_sort (0, n - 1, &data[0]);
    end = omp_get_wtime();
    printf("%.4f\n", end - start);

    validate_sort (n, &data[0]);

    free (data);

	return 0;
}
