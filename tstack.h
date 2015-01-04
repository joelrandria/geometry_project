/**
 * @file   tstack.h
 * @brief  pile de triangle.
 * @author Argoud Aurélien et Joel Randria
 */

#ifndef __TSTACK_H__
#define __TSTACK_H__

#include "triangle.h"

/*! Pile de triangles */
typedef struct _tstack
{
	int nb;
	triangle** tab;
	int nbMaxAtteint;	///élément max atteint par la pile (pour les tests de performance)
} tstack;

/**
 * Crée une pile en initialisant un tableau de pointeur de triangle.
 * @param tailleTab taille du tableau de la pile (attention à vérifier avant d'ajouter ou de faire un tableau assez grand.
 */
tstack* tstack_create(const int tailleTab);

/**
 * libère la zone mémoire de la pile.
 * @param s pile à libérer.
 */
void tstack_delete(tstack* s);

/**
 * ajoute un pointeur de triangle dans la pile.
 * @param s pointeur vers la pile
 * @param t pointeur vers le triangle à ajouter
 */
void tstack_push(tstack* s, triangle* t);

/**
 * retourne un pointeur vers le premier triangle de la pile et l'enlève de la pile.
 * @param s pointeur vers la pile
 * @return pointeur vers le triangle enlevé de la pile.
 */
triangle* tstack_pop(tstack* s);


/*typedef struct _tstack
{
  triangle* t;
  struct _tstack* next;
} tstack;

tstack* tstack_push(tstack* s, triangle* t);
tstack* tstack_pop(tstack* s, triangle** t);*/

#endif
