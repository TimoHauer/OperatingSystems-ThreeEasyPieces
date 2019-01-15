#include<stdio.h>
#include<stdlib.h>
int main()
{
  int *data = malloc(100*sizeof(int));
  data[5] = 5;
  free(&data[5]);
  printf("%d\n", data[5]);
  return 0;
}
