#include "tstack.h"

#include <stdlib.h>

tstack* tstack_create(const int tailleTab)
{
  tstack* s;
  s = malloc(sizeof(*s));
  s->tab = (triangle**) malloc(sizeof(triangle*)*tailleTab);
  s->nb = 0;
  s->nbMaxAtteint = 0;

  return s;
}
void tstack_delete(tstack* s)
{
	free(s->tab);
	free(s);
	s = NULL;
}


void tstack_push(tstack* s, triangle* t)
{
	s->tab[s->nb] = t;
	s->nb++;
	if(s->nb > s->nbMaxAtteint)
		s->nbMaxAtteint = s->nb;
}
triangle* tstack_pop(tstack* s)
{
	s->nb--;
	return s->tab[s->nb];
}
