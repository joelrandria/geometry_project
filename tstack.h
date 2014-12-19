#ifndef __TSTACK_H__
#define __TSTACK_H__

#include "triangle.h"

/*! Pile de triangles */
typedef struct _tstack
{
  triangle* t;
  struct _tstack* next;
} tstack;

tstack* tstack_push(tstack* s, triangle* t);
tstack* tstack_pop(tstack* s, triangle** t);

#endif
