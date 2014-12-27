#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__

#include "pqueue.h"
#include "triangle.h"
#include "delaunay.h"
#include "tstack.h"
#include <assert.h>

void initCarre(vertex* premier, pqueue* pq);
int insertPoint(pqueue* pq, const double goodness_of_fit, const int face);

int repartage(triangle* t, vertex* v);
void repartageCandidats(triangle** tgls, const int nbTriangles, vertex* candid);
tstack* creerTroisTriangles(triangle* t, pqueue* pq);
void corrigeTriangles(tstack* pile, vertex* p, pqueue* pq);


#endif
