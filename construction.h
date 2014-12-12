#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__

#include "pqueue.h"
#include "triangle.h"
#include "delaunay.h"
#include <assert.h>

void initCarre(vertex* premier, pqueue* pq);
int insertPoint(pqueue* pq);
void creerTroisTriangles(triangle* t, pqueue* pq);


#endif
