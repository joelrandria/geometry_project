#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include "triangle.h"

/*! File de priorité de triangles */
typedef struct _pqueue
{
  int size;
  int capacity;
  triangle** items;
} pqueue;

/*! Allocation / Destruction */
pqueue* pqueue_create(int capacity);
void pqueue_delete(pqueue* q);

/*! Affichage */
void pqueue_print(pqueue* q);

/*! Modifications */
void pqueue_enqueue(pqueue* q, triangle* t);
triangle* pqueue_dequeue(pqueue* q);

/*! Tests */
void pqueue_tests();

#endif
