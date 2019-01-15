#ifndef LIST_H
#define LIST_H

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct node
{
	int data;
	struct node *next;
	pthread_mutex_t lock;
}node;

typedef struct list
{
	node *head;
	pthread_mutex_t lock;
}list;

void init(list *liste)
{
	pthread_mutex_init(&liste->lock, NULL);
	liste->head = NULL;
}

int add(list *liste, int data)
{
	node *n = malloc(sizeof(node));
	if (n == NULL)
	{
		return -1;
	}
	n->data = data;
	pthread_mutex_init(&n->lock, NULL);
	pthread_mutex_lock(&liste->lock);
	n->next = liste->head;
	liste->head = n;
	pthread_mutex_unlock(&liste->lock);
	return 0;
}
#endif