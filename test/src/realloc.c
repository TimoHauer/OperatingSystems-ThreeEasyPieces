#include <stdio.h>
#include <stdlib.h>

#include "vector.h"


void init(vector *vec)
{
	vec->vdata = NULL;
	vec->size = 0;
	vec->count = 0;
}
void add(vector *vec, int d)
{
	if (vec->size == 0) {
		vec->size = 10;
		vec->vdata = calloc(vec->size, sizeof(int*) * vec->size);
	}
	if (vec->size == vec->count) {
		vec->size *= 2;
		vec->vdata = realloc(vec->vdata, sizeof(int*) * vec->size);
	}

	vec->vdata[vec->count] = d;
	vec->count++;
}
void vremove(vector *vec, int index)
{
	if (index >= vec->count) {
		return;
	}

	vec->vdata[index] = NULL;

	int i, j;
	int *data = calloc(vec->size, sizeof(int*) * vec->size);
	for(j = 0; j < index; j++)
	{
		data[j] = get(vec, j);
	}
	for(i = index; i < vec->count-1; i++)
	{
		data[i] = get(vec, index+1);
	}

	vec->vdata = realloc(vec->vdata, sizeof(data));
	vec->vdata = data;

	vec->count--;
}
int get(vector *vec, int index)
{
		if (index >= vec->count) {
			return -1;
		}
		return vec->vdata[index];
}
void vfree(vector *vec)
{
	free(vec->vdata);
}
int anzahl(vector *vec)
{
	return vec->count;
}
int main()
{
	vector myvec;
	init(&myvec);
	add(&myvec, 1);
	add(&myvec, 2);
	add(&myvec, 3);

	for(int x = 0; x < anzahl(&myvec); x++)
	{
		printf("vdata is: %d\n",get(&myvec, x));
	}
	printf("Anzahl: %d\n",anzahl(&myvec));
	
	vremove(&myvec, 1);

	for(int x = 0; x < anzahl(&myvec); x++)
	{
		printf("vdata is: %d\n",get(&myvec, x));
	}
	printf("Anzahl: %d\n",anzahl(&myvec));


	int i;
	for(i = 0; i < 200; i++)
	{
		add(&myvec, i+1);
	}
	for(int j = 0; j < anzahl(&myvec); j++)
	{
		printf("vdata is: %d\n",get(&myvec, j));
	}
	printf("Anzahl: %d\n",anzahl(&myvec));

	vfree(&myvec);
}