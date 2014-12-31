/**
 * @file   transform.h
 * @brief  Transformation homogène 3D.
 */
#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "vec3f.h"

/*! Structure encapsulant une matrice homogène 4x4. */
typedef struct _transform
{
  /// Matrice homogène 4x4 encapsulant une rotation et une translation dans l'espace.
  double v[4][4];
} transform;

/**
 * Affecte l'identité à la transformation spécifiée.
 *
 * @param t La transformation à affecter.
 */
void transform_identity(transform* t);
/**
 * Copie une transformation dans une autre transformation.
 *
 * @param t La transformation à copier.
 * @param r La transformation recevant la copie.
 */
void transform_copy(const transform* t, transform* r);
/**
 * Affecte les valeurs de matrice spécifiées à la transformation spécifiée.
 *
 * @param t La transformation à affecter.
 * @param v00 La valeur à affecter aux coordonnées [0][0] de la matrice de la transformation.
 * @param v01 La valeur à affecter aux coordonnées [0][1] de la matrice de la transformation.
 * @param v02 La valeur à affecter aux coordonnées [0][2] de la matrice de la transformation.
 * @param v03 La valeur à affecter aux coordonnées [0][3] de la matrice de la transformation.
 * @param v10 La valeur à affecter aux coordonnées [1][0] de la matrice de la transformation.
 * @param v11 La valeur à affecter aux coordonnées [1][1] de la matrice de la transformation.
 * @param v12 La valeur à affecter aux coordonnées [1][2] de la matrice de la transformation.
 * @param v13 La valeur à affecter aux coordonnées [1][3] de la matrice de la transformation.
 * @param v20 La valeur à affecter aux coordonnées [2][0] de la matrice de la transformation.
 * @param v21 La valeur à affecter aux coordonnées [2][1] de la matrice de la transformation.
 * @param v22 La valeur à affecter aux coordonnées [2][2] de la matrice de la transformation.
 * @param v23 La valeur à affecter aux coordonnées [2][3] de la matrice de la transformation.
 * @param v30 La valeur à affecter aux coordonnées [3][0] de la matrice de la transformation.
 * @param v31 La valeur à affecter aux coordonnées [3][1] de la matrice de la transformation.
 * @param v32 La valeur à affecter aux coordonnées [3][2] de la matrice de la transformation.
 * @param v33 La valeur à affecter aux coordonnées [3][3] de la matrice de la transformation.
 */
void transform_setmatrix(transform* t,
			 float v00, float v01, float v02, float v03,
			 float v10, float v11, float v12, float v13,
			 float v20, float v21, float v22, float v23,
			 float v30, float v31, float v32, float v33);
/**
 * Produit matrice-vecteur.
 *
 * @param t La matrice en entrée.
 * @param v Le vecteur en entrée.
 * @param r Le vecteur recevant le produit tv.
 */
void transform_mul(const transform* t, const vec3f* v, vec3f* r);

/**
 * Obtient une transformation représentant une rotation d'angle arbitraire autour d'un axe arbitraire.
 *
 * @param degree_angle L'angle de rotation en degrés.
 * @param axis L'axe de rotation.
 * @param r La transformation recevant le résultat de la fonction.
 */
void transform_getrotation(float degree_angle, const vec3f* axis, transform* r);

/**
 * Inverse une transformation.
 *
 * @param t La transformation à inverser.
 * @param r La transformation recevant la transformation inverse.
 */
void transform_inverse(const transform* t, transform* r);

/**
 * Affiche les attributs d'une transformation.
 *
 * @param t La transformation à afficher.
 */
void transform_print(const transform* t);

#endif
