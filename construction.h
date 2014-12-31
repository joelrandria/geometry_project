#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__

#include "pqueue.h"
#include "tstack.h"
#include "triangle.h"
#include "delaunay.h"
#include "settings.h"

#include <assert.h>

void initCarre(vertex* premier, pqueue* pq);
int insertPoint(pqueue* pq, settings* s);

int repartage(triangle* t, vertex* v);
void repartageCandidats(triangle** tgls, const int nbTriangles, vertex* candid);
tstack* creerTroisTriangles(triangle* t, pqueue* pq);
void corrigeTriangles(tstack* pile, vertex* p, pqueue* pq);


#endif
