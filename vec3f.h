/**
 * @file   vec3f.h
 * @brief  Définit une structure de vecteur à 3 dimensions et un ensemble d'opérations relatif à celle-ci.
 */

#ifndef __VEC3F_H__
#define __VEC3F_H__

/*! Définit une structure de vecteur à 3 dimensions. */
typedef struct _vec3f
{
  /// Composante x du vecteur.
  double x;
  /// Composante y du vecteur.
  double y;
  /// Composante z du vecteur.
  double z;
} vec3f;

/**
 * Affecte les coordonnées spécifiées au vecteur spécifié.
 *
 * @param v Le vecteur à modifier.
 * @param x La composante x à affecter au vecteur.
 * @param y La composante y à affecter au vecteur.
 * @param z La composante z à affecter au vecteur.
 */
void vec3f_set(vec3f* v, double x, double y, double z);

/**
 * Additionne les 2 vecteurs spécifiés.
 *
 * @param v1 Le premier vecteur.
 * @param v2 Le second vecteur.
 * @param r Le vecteur recevant la somme des deux vecteurs précédents.
 */
void vec3f_add(const vec3f* v1, const vec3f* v2, vec3f* r);
/**
 * Multiplie les composantes du vecteur spécifié par la valeur spécifiée.
 *
 * @param v Le vecteur.
 * @param d Le coefficient multiplicateur.
 * @param r Le vecteur recevant le résultat de la multiplication.
 */
void vec3f_mul(const vec3f* v, double d, vec3f* r);
/**
 * Effectue le produit vectoriel v1 x v2.
 *
 * @param v1 Le premier vecteur.
 * @param v2 Le second vecteur.
 * @param r Le vecteur recevant le résultat du produit v1 x v2.
 */
void vec3f_cross(const vec3f* v1, const vec3f* v2, vec3f* r);

/**
 * Obtient la norme du vecteur spécifié.
 *
 * @param v Le vecteur.
 *
 * @return La norme du vecteur spécifié.
 */
double vec3f_length(const vec3f* v);
/**
 * Calcule le vecteur normalisé du vecteur spécifié.
 *
 * @param v Le vecteur d'entrée.
 * @param r Le vecteur recevant le résultat de la normalisation.
 */
void vec3f_normalize(const vec3f* v, vec3f* r);

/**
 * Affiche les attributs du vecteur spécifié.
 *
 * @param v Le vecteur à afficher.
 */
void vec3f_print(const vec3f* v);

#endif
