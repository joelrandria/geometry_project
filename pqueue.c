#include "pqueue.h"

pqueue* pqueue_create(int capacity)
{
  pqueue* q;

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

void pqueue_enqueue(triangle* t)
{
  
}
triangle* pqueue_dequeue()
{
  
}
