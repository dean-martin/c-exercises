// Exercise 3-1.
// Our binary search makes two tests inside the loop, when one would suffice
// (at the price of more tests outside). Write a version with only one test
// inside the loop and measure the difference in run-time.
#include <stdio.h>
#include <time.h>

int binsearch(int x, int v[], int n);
int _binsearch(int x, int v[], int n);
void test(int originalsearch);


int v[] = {2, 4, 5, 7, 7, 9};

int main()
{
    test(1); // new
    //test(0); // original
    // some sort of cpu optimizing/caching going on, old and new are the same
    // on separate executions
}

void test(int newsearch)
{
    clock_t begin = clock();

    if (newsearch) {
        printf("%i\n", binsearch(9, v, 6));
        printf("%i\n", binsearch(1, v, 6));
    }
    else {
        printf("%i\n", _binsearch(5, v, 6));
        printf("%i\n", _binsearch(4, v, 6));
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time taken: %fs\n", time_spent);
}


/* binsearch assumed an ordered array */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low+high) / 2;
    while (low <= high && x != v[mid]) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    // checking another example, they don't have a x != v[mid] in their while test
    // and use x == v[mid-1] and return mid-1; here
    if (x == v[mid]) 
        return mid;

    return -1;  /* no match */
}

/* original from book, binsearch assumed an ordered array */
int _binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    /* found match */
            return mid;
    }
    return -1;  /* no match */
}
