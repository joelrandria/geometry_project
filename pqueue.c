#include "pqueue.h"

#include <assert.h>
#include <stdio.h>

pqueue* pqueue_create(int capacity)
{
  pqueue* q;

  assert(capacity >= 0);

  q = malloc(sizeof(*q));
  q->size = 0;
  q->capacity = capacity;
  q->items = malloc((sizeof(*q->items) * capacity) + 1);

  return q;
}
void pqueue_delete(pqueue* q)
{
  if (q->capacity > 0)
    free(q->items);
  free(q);
}

void pqueue_print(pqueue* q)
{
  int i;

  printf("---------------------------\r\n");
  for (i = 1; i <= q->size; ++i)
    printf("[%d]: %f\r\n", i, q->items[i]->distance_max);
  printf("---------------------------\r\n");
}

static void pqueue_swap(pqueue* q, int pos1, int pos2)
{
  triangle* temp;

  assert(pos1 >= 1 && pos1 <= q->size);
  assert(pos2 >= 1 && pos2 <= q->size);

  temp = q->items[pos1];
  q->items[pos1] = q->items[pos2];
  q->items[pos2] = temp;
}
void pqueue_enqueue(pqueue* q, triangle* t)
{
  int pos;

  assert(q->size < q->capacity);

  q->size++;
  q->items[q->size] = t;

  pos = q->size;

  while ((pos > 1) && (q->items[pos]->distance_max > q->items[pos / 2]->distance_max))
  {
    pqueue_swap(q, pos, pos / 2);
    pos /= 2;
  }
}
triangle* pqueue_dequeue(pqueue* q)
{
  int pos;
  int left;
  int right;
  int swap;

  triangle* first;

  assert(q->size > 0);

  first = q->items[1];

  q->items[1] = q->items[q->size];
  q->size--;

  pos = 1;

  for (;;)
  {
    if (pos >= q->size)
      break;

    swap = -1;
    left = pos * 2;
    right = (pos * 2) + 1;

    if (q->items[left]->distance_max > q->items[pos]->distance_max)
      swap = left;
    if (right <= q->size && q->items[right]->distance_max > q->items[left]->distance_max)
      swap = right;

    if (swap > 0)
      pqueue_swap(q, pos, swap);
    else
      break;

    pos = swap;
  }

  return first;
}

void pqueue_tests()
{
  triangle* t;
  pqueue* q = pqueue_create(6);

  t = triangle_create(0, 0, 0, 0, 0, 0);
  t->distance_max = 3;
  printf("pqueue_enqueue()\r\n");
  pqueue_enqueue(q, t);

  t = triangle_create(0, 0, 0, 0, 0, 0);
  t->distance_max = 2;
  printf("pqueue_enqueue()\r\n");
  pqueue_enqueue(q, t);

  t = triangle_create(0, 0, 0, 0, 0, 0);
  t->distance_max = 1;
  printf("pqueue_enqueue()\r\n");
  pqueue_enqueue(q, t);

  t = triangle_create(0, 0, 0, 0, 0, 0);
  t->distance_max = 5;
  printf("pqueue_enqueue()\r\n");
  pqueue_enqueue(q, t);

  t = triangle_create(0, 0, 0, 0, 0, 0);
  t->distance_max = 6;
  printf("pqueue_enqueue()\r\n");
  pqueue_enqueue(q, t);

  t = triangle_create(0, 0, 0, 0, 0, 0);
  t->distance_max = 4;
  printf("pqueue_enqueue()\r\n");
  pqueue_enqueue(q, t);

  pqueue_print(q);

  while (q->size > 0)
  {
    printf("pqueue_dequeue()\r\n");
    pqueue_dequeue(q);

    pqueue_print(q);
  }

  pqueue_delete(q);
}
