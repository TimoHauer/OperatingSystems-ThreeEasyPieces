#ifndef VECTOR_H
#define VECTOR_H

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct vector
{
  int *vdata;
  int size;
  int count;
  pthread_mutex_t lock;
} vector;

void init(vector *vec)
{
	vec->vdata = 0;
	vec->size = 0;
	vec->count = 0;
	pthread_mutex_init(&vec->lock, NULL);
}
void add(vector *vec, int d)
{
	pthread_mutex_lock(&vec->lock);
	if (vec->size == 0) {
		vec->size = 1;
		vec->vdata = calloc(vec->size, sizeof(int*) * vec->size);
	}
	if (vec->size == vec->count) {
		vec->size *= 2;
		vec->vdata = realloc(vec->vdata, sizeof(int*) * vec->size);
	}

	vec->vdata[vec->count] = d;
	vec->count++;
	pthread_mutex_unlock(&vec->lock);
}
void vremove(vector *vec, int index)
{
	pthread_mutex_lock(&vec->lock);
	if (index >= vec->count) {
		pthread_mutex_unlock(&vec->lock);
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
	pthread_mutex_unlock(&vec->lock);
}
int get(vector *vec, int index)
{
	pthread_mutex_lock(&vec->lock);
	if (index >= vec->count) {
		pthread_mutex_unlock(&vec->lock);
		return -1;
	}
	return vec->vdata[index];
	pthread_mutex_unlock(&vec->lock);

}
int anzahl(vector *vec)
{
	pthread_mutex_lock(&vec->lock);
	return vec->count;
	pthread_mutex_unlock(&vec->lock);
}

#endif