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
	if (vec->size == 0) {
		vec->size = 1;
		vec->vdata = calloc(vec->size, sizeof(int*) * vec->size);
	}
	if (vec->size == vec->count) {
		vec->size *= 2;
		vec->vdata = realloc(vec->vdata, sizeof(int*) * vec->size);
	}
	pthread_mutex_lock(&vec->lock);
	vec->vdata[vec->count] = d;
	vec->count++;
	pthread_mutex_unlock(&vec->lock);
}
void vremove(vector *vec, int index)
{
	
	if (index >= vec->count) {
		return;
	}
	pthread_mutex_lock(&vec->lock);
	vec->vdata[index] = NULL;
	pthread_mutex_unlock(&vec->lock);

	int i, j;
	pthread_mutex_lock(&vec->lock);
	int *data = calloc(vec->size, sizeof(int*) * vec->size);
	pthread_mutex_unlock(&vec->lock);
	for(j = 0; j < index; j++)
	{
		pthread_mutex_lock(&vec->lock);
		data[j] = get(vec, j);
		pthread_mutex_unlock(&vec->lock);
	}
	for(i = index; i < vec->count-1; i++)
	{
		pthread_mutex_lock(&vec->lock);
		data[i] = get(vec, index+1);
		pthread_mutex_unlock(&vec->lock);
	}

	vec->vdata = realloc(vec->vdata, sizeof(data));

	pthread_mutex_lock(&vec->lock);
	vec->vdata = data;
	vec->count--;
	pthread_mutex_unlock(&vec->lock);
}
int get(vector *vec, int index)
{
	if (index >= vec->count) {
		return -1;
	}
	pthread_mutex_lock(&vec->lock);
	int data = vec->[index];
	pthread_mutex_unlock(&vec->lock);
	return data

}
int anzahl(vector *vec)
{
	pthread_mutex_lock(&vec->lock);
	return vec->count;
	pthread_mutex_unlock(&vec->lock);
}

#endif