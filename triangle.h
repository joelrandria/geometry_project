#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "vertex.h"

/*! Structure pour representer un triangle. */
typedef struct _triangle
{
  struct _vertex* s[3];		//sommets du triangle
  struct _triangle* v[3];	//triangles voisins
  struct _vertex* candidats;	//liste des points dans le triangle (x,y) avec VLINK_CANDIDAT.
} triangle;

void triangle_init(triangle* t, vertex* v0, vertex* v1, vertex* v2, triangle* voisin0, triangle* voisin1, triangle* voisin2);
void triangle_init2(triangle* t, vertex* v0, vertex* v1, vertex* v2);

triangle* triangle_create(vertex* v0, vertex* v1, vertex* v2, triangle* voisin0, triangle* voisin1, triangle* voisin2);
triangle* triangle_create2(vertex* v0, vertex* v1, vertex* v2);

double plane_vertical_distance(triangle* t, vertex* v);

#endif
