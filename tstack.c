#include "tstack.h"

#include <stdlib.h>

static tstack* tstack_create(triangle* t)
{
  tstack* s;

  s = malloc(sizeof(*s));
  s->t = t;
  s->next = 0;

  return s;
}

tstack* tstack_push(tstack* s, triangle* t)
{
  tstack* h;

  h = tstack_create(t);
  h->next = s;

  return h;
}
tstack* tstack_pop(tstack* s, triangle** t)
{
  tstack* n;

  *t = s->t;
  n = s->next;

  free(s);

  return n;
}
