#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "vertex.h"

/*! Structure pour représenter un triangle. */
typedef struct _triangle
{
  struct _vertex* s[3];		// sommets du triangle
  struct _triangle* v[3];	// triangles voisins

  double distance_max;		// distance du candidat du triangle, le plus loin verticalement
  struct _vertex* candidats;	// liste des points dans le triangle (x,y) avec VLINK_CANDIDAT.
} triangle;

/*! Création */
void triangle_init(triangle* t, vertex* v0, vertex* v1, vertex* v2,
		   triangle* voisin0, triangle* voisin1, triangle* voisin2);
void triangle_init2(triangle* t, vertex* v0, vertex* v1, vertex* v2);

triangle* triangle_create(vertex* v0, vertex* v1, vertex* v2,
			  triangle* voisin0, triangle* voisin1, triangle* voisin2);
triangle* triangle_create2(vertex* v0, vertex* v1, vertex* v2);

/*! Géométrie */
int dansTriangle2d(const triangle* t, const vertex* p);
double triangle_vertical_distance(triangle* t, vertex* v);
double ajouteCandidat(triangle* t, vertex* v);

double triangle_vertical_distance(triangle* t, vertex* v);

int triangleInCircle (const triangle *t, const vertex *D);

/*! Tests */
void triangle_tests();

void triangle_print(const triangle* t);
void triangle_print2D(const triangle* t);

//rapprochement point et indice
int triangle_indice_point(const triangle* t, const vertex* p);
int triangle_indice_voisin(const triangle* t, const triangle* voisin);


//modifier indice triangle
void rotationIndiceTriangle(triangle* t, const int rot);
void swapIndiceTriangle(triangle*t, const int i1, const int i2);
#endif
