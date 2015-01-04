/**
 * @file   triangle.h
 * @brief  Structure simplex triangle.
 * @author Argoud Aurélien et Joel Randria
 */
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "vertex.h"

///def
#define HAUTEUR_DEFAUT 0.0

/**
 * @struct triangle
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
/** 
 * @fn void triangle_init(triangle* t, vertex* v0, vertex* v1, vertex* v2,
		   triangle* voisin0, triangle* voisin1, triangle* voisin2);
 * @brief initialisation d'un triangle.
 * 
 * @param[out] t triangle à initialiser.
 * @param[in] v0 premier sommet du triangle.
 * @param[in] v1 second sommet du triangle.
 * @param[in] v2 troisième sommet du triangle.
 * @param[in] voisin0 triangle à l'opposé du premier sommet.
 * @param[in] voisin1 triangle à l'opposé du second sommet.
 * @param[in] voisin2 triangle à l'opposé du troisième sommet.
 * */
void triangle_init(triangle* t, vertex* v0, vertex* v1, vertex* v2,
		   triangle* voisin0, triangle* voisin1, triangle* voisin2);
/** 
 * @fn void triangle_init2(triangle* t, vertex* v0, vertex* v1, vertex* v2);
 * @brief initialisation d'un triangle.
 * 
 * @param[out] t triangle à initialiser.
 * @param[in] v0 premier sommet du triangle.
 * @param[in] v1 second sommet du triangle.
 * @param[in] v2 troisième sommet du triangle.
 * */
void triangle_init2(triangle* t, vertex* v0, vertex* v1, vertex* v2);

/** 
 * @fn triangle* triangle_create(vertex* v0, vertex* v1, vertex* v2,
			  triangle* voisin0, triangle* voisin1, triangle* voisin2);
 * @brief création et initialisation d'un triangle.
 * 
 * @param[in] v0 premier sommet du triangle.
 * @param[in] v1 second sommet du triangle.
 * @param[in] v2 troisième sommet du triangle.
 * @param[in] voisin0 triangle à l'opposé du premier sommet.
 * @param[in] voisin1 triangle à l'opposé du second sommet.
 * @param[in] voisin2 triangle à l'opposé du troisième sommet.
 * @return triangle créé.
 * */
triangle* triangle_create(vertex* v0, vertex* v1, vertex* v2,
			  triangle* voisin0, triangle* voisin1, triangle* voisin2);
/** 
 * @fn triangle* triangle_create2(vertex* v0, vertex* v1, vertex* v2);
 * @brief création et initialisation d'un triangle.
 * 
 * @param[in] v0 premier sommet du triangle.
 * @param[in] v1 second sommet du triangle.
 * @param[in] v2 troisième sommet du triangle.
 * @return triangle créé.
 * */
triangle* triangle_create2(vertex* v0, vertex* v1, vertex* v2);

/*! Géométrie */

#define ALIGNE 0x11	/// @def ALIGNE
#define GAUCHE 0x01	/// @def GAUCHE
#define DROITE 0x10	/// @def DROITE
/**
 * @fn int cote2d(const vertex* p1, const vertex* p2, const vertex* p);
 * @brief détermine si un troisième vertex est à droite ou à gauche du 
 * vecteur formé par deux autres vertex.
 * 
 * @param[in] p1 point de départ du vecteur.
 * @param[in] p2 point de fin du verteur.
 * @param[in] p point à déterminer s'il est à droite, à gauche ou sur le vecteur.
 * @return retourne si le dernier point est à droite, à gauche ou sur le vecteur.
 * */
int cote2d(const vertex* p1, const vertex* p2, const vertex* p);
/**
 * @fn int dansTriangle2d(const triangle* t, const vertex* p);
 * @brief indique si un point est dans un triangle sur les coordonnées XY
 * 
 * @param[in] t triangle.
 * @param[in] p point qui est peut-être dans le triangle.
 * @return Booleen: le point est-il dans le triangle?
 * */
int dansTriangle2d(const triangle* t, const vertex* p);
/**
 * @fn double triangle_vertical_distance(triangle* t, vertex* v);
 * 
 * @param[in] t triangle.
 * @param[in] v vertex.
 * @return distance verticale sur l'axe Z entre le triangle et le vertex.
 * */
double triangle_vertical_distance(triangle* t, vertex* v);
/**
 * @fn double ajouteCandidat(triangle* t, vertex* v);
 * @brief ajoute un candidat à la bonne position dans un triangle.
 * 
 * @param[in, out] t triangle dont on va ajouter un candidat à sa place.
 * @param[in] v candidat à ajouter.
 * @return distance jusqu'au candidat de priorité la plus forte (distance la plus loin du triangle).
 * */
double ajouteCandidat(triangle* t, vertex* v);

/**
 * @fn int triangleInCircle (const triangle *t, const vertex *D);
 * 
 * @param[in] t triangle dont les sommets sont dans l'ordre anti-horaire. 
 * @param[in] D vertex
 * @return Booleen: le point D est-il dans le cercle circonscrit du triangle?
 * @warning si les sommets sont dans le sens horaire, le résultat est inversé.
 * 			Si le point D est pile sur le cercle circonscrit, alors il est considéré comme à l'extérieur.
 * */
int triangleInCircle (const triangle *t, const vertex *D);

/*! Tests */
void triangle_tests();


void triangle_print(const triangle* t);
void triangle_print2D(const triangle* t);

//rapprochement point et indice
/**
 * @fn int triangle_indice_point(const triangle* t, const vertex* p);
 * @brief indique l'indice du point dans le triangle.
 * 		Cela correspond aussi à l'indice du triangle voisin à l'opposé de ce sommet.
 * 
 * @param[in] t triangle.
 * @param[in] p un point appartenant au triangle. 
 * @return retourne l'indice 0/1/2 du point dans le triangle.
 * @warning si le point n'est pas un sommet du triangle, le programme crash.
 * */
int triangle_indice_point(const triangle* t, const vertex* p);
/**
 * @fn int triangle_indice_voisin(const triangle* t, const triangle* voisin);
 * @brief indique l'indice du triangle voisin d'un triangle.
 * 		Cela correspond aussi à l'indice du sommet à l'opposé du voisin.
 * 
 * @param[in] t triangle.
 * @param[in] voisin un triangle étant un voisin du triangle t.
 * @return retourne l'indice 0/1/2 du voisin de ce triangle.
 * @warning si le triangle voisin n'est pas un voisin du premier triangle, ça crash.
 * */
int triangle_indice_voisin(const triangle* t, const triangle* voisin);

//modifier indice triangle
/**
 * @fn void rotationIndiceTriangle(triangle* t, const int rot);
 * @brief fait tourner les indices du triangle (sommets et voisins) pour ce retrouver dans une configuration plus simple.
 * 
 * @param[in, out] t triangle à tourner.
 * @param[in] rot nombre de rotation des indices vers l'indice suivant. (l'indice 2 passe à l'indice 0).
 * */
void rotationIndiceTriangle(triangle* t, const int rot);

/**
 * @fn void swapIndiceTriangle(triangle*t, const int i1, const int i2);
 * @brief échange deux indices du triangle (sommets et voisins).
 * 
 * @param[in, out] t triangle.
 * @param[in] i1 indice du triangle à échanger.
 * @param[in] i2 indice du triangle à échanger avec le premier.
 * */
void swapIndiceTriangle(triangle*t, const int i1, const int i2);
#endif
