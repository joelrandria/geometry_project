#include "pqueue.h"

#include <assert.h>

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
  int swap;

  triangle* first;

  assert(q->size > 0);

  first = q->items[1];

  q->items[1] = q->items[q->size];
  q->size--;

  pos = 1;

  while ((pos < q->size)
	 && (q->items[pos]->distance_max < q->items[pos * 2]->distance_max
	     || q->items[pos]->distance_max < q->items[(pos * 2) + 1]->distance_max))
  {
    if (q->items[pos * 2]->distance_max > q->items[(pos * 2) + 1]->distance_max)
      swap = pos * 2;
    else
      swap = (pos * 2) + 1;

    pqueue_swap(q, pos, swap);

    pos = swap;
  }

  return first;
}
