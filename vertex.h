#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <math.h>
#include <stdlib.h>

/*! Dimensions de l'espace */
#define DIM 3
#define X coords[0]
#define Y coords[1]
#define Z coords[2]

// Orientations
#define ORIENTATION_CW		-1		//clockwise: orientation horaire:	< 180 dans le sens des aiguille d'une montre
#define ORIENTATION_INLINE	0		//aligné
#define ORIENTATION_CCW		1		//counter clockwise: orientation polaire:	> 180 dans le sens des aiguille d'une montre

// Liens inter vertices
#define VLINK_TYPE_COUNT	5
#define VLINK_NATURAL		0
#define VLINK_POLAR		1
#define VLINK_LEXICO		2
#define VLINK_CONVEX		3
#define VLINK_CANDIDAT		4

#define VLINK_DIRECTION_COUNT	2
#define VLINK_BACKWARD		0
#define VLINK_FORWARD		1

/*! Structure pour representer un point. */
typedef struct _vertex
{
  double coords[DIM];
  struct _vertex* link[VLINK_TYPE_COUNT][VLINK_DIRECTION_COUNT];
} vertex;

// Allocation / Initialisation / Copie
void vertex_init(vertex* v, double x, double y, double z);
vertex* vertex_create(double x, double y, double z);
void vertex_modif(vertex* v, double x, double y, double z);
vertex* vertex_copy(vertex* tab, int count);
void vertex_delete(vertex* v, int vlink);

// Affichage
void vertex_print_all(vertex* v, int vlink, int vdirection);

// Relations
vertex* vertex_at(vertex* v, int position, int vlink, int direction);
vertex* vertex_insert(vertex* ref, vertex* nouv, int link, int direction);

// Distances
int equal2d(const vertex* a, const vertex* b);
int equal3d(const vertex* a, const vertex* b);
double vertex_distance(const vertex* v1, const vertex* v2);
double vertex_distance3d(const vertex* v1, const vertex* v2);
double square_distance_eucl(const vertex* a, const vertex* b);

// Relation d'ordre lexicographique
int lexico_cmp(const vertex* a, const vertex* b);
int lexico_min(const vertex* points, const unsigned int point_count);

// Relation d'ordre polaire
int orientation(const vertex* a, const vertex* b, const vertex* c);
int local_polar_min(const vertex* points, const unsigned int point_count, int point);

double calculPolaire(const vertex* origin, const vertex* dest);
double orientPolaire(const vertex* gauche, const vertex* centre, const vertex* droite);

vertex* chainageArriere(vertex* debList, const int type);

#endif
