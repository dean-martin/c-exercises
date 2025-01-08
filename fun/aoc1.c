#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int (*CMP) (const void *, const void *);
void _qsort(void *v[], int left, int right, CMP cmp);
void swap(void *v[], int, int);

int cmpint(const int *a, const int *b)
{
	if (*a > *b)
		return 1;
	else if (*a < *b)
		return -1;
	return 0;
}

int main()
{
	int *left = (int *) calloc(100, sizeof(int));
	int *right = (int *) calloc(100, sizeof(int));
	int i = 0;
	while (fscanf(stdin, "%d%d", left++, right++) != EOF)
		i++;
	left -= i+1, right -= i+1;
	qsort(left, i, sizeof(int), (int (*)(const void *, const void *))cmpint);
	qsort(right, i, sizeof(int), (int (*)(const void *, const void *))cmpint);
	double sum = 0;
	while (*left && *right) {
		printf("%d %d\n", *left, *right);
		sum += abs(*left++ - *right++);
	}
	printf("sum: %g\n", sum);
}

void _qsort(void *v[], int left, int right, CMP cmp)
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)      /* do nothing if array contains */
		return;             /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*cmp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	_qsort(v, left, last-1, cmp);
	_qsort(v, last+1, right, cmp);
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
