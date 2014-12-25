/**
 * @file   pqueue.h
 * @author jo <jo@jo-linux>
 * @date   Thu Dec 25 19:45:30 2014
 *
 * @brief File de priorité de triangles basée sur leurs distances respectives à leurs sommets respectifs.
 */
#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include "triangle.h"

/**
 * Définit une file de priorité de triangles.
 * La priorité des triangles est fondée sur leur distance maximum respective à leurs sommets respectifs.
 * Cette file de priorité est implémentée selon une arborescence binaire.
 */
typedef struct _pqueue
{
  /// Taille courante de la file de priorité.
  int size;
  /// Capacité maximum de la file de priorité.
  int capacity;
  /// Tableau interne encapsulant l'arborescence binaire de triangles.
  triangle** items;

} pqueue;

/**
 * Construit une nouvelle file de priorité de triangles, de la capacité spécifiée.
 *
 * @param capacity Nombre maximum de triangles pouvant être pris en charge dans la file de priorité.
 *
 * @return La file de priorité.
 */
pqueue* pqueue_create(int capacity);
/**
 * Détruit la file de priorité de triangles spécifiée.
 *
 * @param q La file de priorité à libérer.
 */
void pqueue_delete(pqueue* q);	//free/delete

/**
 * Affiche sur la sortie standard les éléments de la file de priorité spécifiée.
 *
 * @param q La file de priorité à afficher.
 */
void pqueue_print(pqueue* q);

/**
 * Insère le triangle spécifié dans la file de priorité spécifiée.
 *
 * @param q La file de priorité.
 * @param t Le triangle à insérer dans la file.
 */
void pqueue_enqueue(pqueue* q, triangle* t);
/**
 * Défile le triangle de priorité maximum de la file spécifiée.
 *
 * @param q La file de priorité à défiler.
 *
 * @return Le triangle de priorité maximum de la file spécifiée.
 */
triangle* pqueue_dequeue(pqueue* q);

/**
 * Batterie de tests de la structure de file de priorité.
 */
void pqueue_tests();

#endif
