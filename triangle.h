/**
 * @file   triangle.h
 * @brief  Structure simplex triangle.
 */
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "vertex.h"

/**
 * Définit un triangle du maillage. Encapsule les informations locales d'un simplex triangle et encapsule l'ensemble de sommets n'appartenant pas au maillage, se projetant verticalement sur celui-ci.
 */
typedef struct _triangle
{
  /// Les sommets du triangle.
  struct _vertex* s[3];
  /// Les triangles adjacents à celui-ci.
  struct _triangle* v[3];

  /// Distance verticale séparant ce triangle et son sommet candidat le plus éloigné verticalement.
  double distance_max;
  /// Liste des sommets n'appartenant pas au maillage mais se projetant verticalement sur ce triangle.\n Si non nul, le premier sommet ce cette liste est le plus distant verticalement de ce triangle.
  struct _vertex* candidats;

  /// Position du triangle dans la file de priorité.
  int queue_pos;

} triangle;

/*! Construction / Modification */
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
