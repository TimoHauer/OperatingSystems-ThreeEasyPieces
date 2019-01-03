#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector
{
  int *vdata;
  int size;
  int count;
} vector;

void init(vector *vec);
void add(vector *vec, int d);
void vremove(vector *vec, int index);
int get(vector *vec, int index);
void vfree(vector *vec);
int anzahl(vector *vec);

#endif