/**
 * @file   construction.h
 * @brief  construction d'une triangulation de delaunay en plusieurs étape.
 * @author Argoud Aurélien et Joel Randria
 */

#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__

#include "pqueue.h"
#include "tstack.h"
#include "triangle.h"
#include "delaunay.h"
#include "settings.h"

#include <assert.h>

/** 
 * @fn void initCarre(vertex* premier, pqueue* pq);
 * @brief Crée deux triangles à partir des quatre premiers vertex de la liste naturel en paramêtre.
 * Ces quatre premiers vertex doivent être les quatre sommets du carré et dans l'ordre lexicographique (0,0)(0,1)(1,0)(1,1) avec (x,y).
 * Les vertex suivants seront les candidats d'un des deux triangles.
 * 
 * @param[in] premier vertex du carré chainé aux autres vertex.
 * @param[out] pq priority_queue dont la taille a été initialisé. Les deux triangles créés seront inséré dans cette priority_queue.
 * */
void initCarre(vertex* premier, pqueue* pq);

/** 
 * @fn int insertPoint(pqueue* pq, tstack* pile, settings* s);
 * @brief Passe à l'étape suivante dans l'algorithme de Delaunay en créant une nouvelle triangulation.
 * 
 * @param[out] pq priority_queue de la liste de triangle
 * @param pile pile de triangle dont la taille a été initialisée.
 * @return Booleen: reste il une triangulation possible?
 */
int insertPoint(pqueue* pq, tstack* pile, settings* s);

/** 
 * @fn int repartage(triangle* t, vertex* v);
 * @brief Insère le vertex dans le triangle s'il est a l'intérieur sur les coordonnées XY.
 * 
 * @param[in] t triangle dans la triangulation de delaunay.
 * @param[in] v verter qui peut être ajouté dans la liste des candidats du triangle.
 * @return Booleen: est-ce que le vertex a été ajouté dans liste des candidats du triangle?
 */
int repartage(triangle* t, vertex* v);

/** 
 * @fn void repartageCandidats(triangle** tgls, const int nbTriangles, vertex* candid);
 * @brief Insère toute la liste des candidats dans tous les triangles en paramètre.
 * 
 * @param[in] tgls tableau de triangle sans candidat.
 * @param[in] nbTriangle nombre de triangle dans le tableau.
 * @param[in] candid liste des candidats à partager entre chaques triangles.
 * */
void repartageCandidats(triangle** tgls, const int nbTriangles, vertex* candid);

/** 
 * @fn void creerTroisTriangles(triangle* t, pqueue* pq, tstack* pile);
 * @brief Crée 3 triangles à partir d'un triangle coupé en 3 par son candidat de plus haute priorité.
 * 
 * @param[in] t triangle à couper en 3.
 * @param[in, out] pq priority_queue dont le triangle de priorité la plus forte a été enlevé et les trois triangles créés ont été insérés à leur place.
 * @param[out] pile pile qui stockera les trois triangles créés et qui risqueront d'être corrigés avec les triangles voisins.
 * */
void creerTroisTriangles(triangle* t, pqueue* pq, tstack* pile);

/** 
 * @fn void corrigeTriangles(tstack* pile, vertex* p, pqueue* pq);
 * @brief corrige les triangle de la pile qui sont peut-être trop applati et forme une mauvaise triangulation avec un voisin.
 * 
 * @param[in] pile pile des triangles à corriger (peut-être).
 * @param pq priority_queue dont les triangles pourront être déplacer s'ils sont corrigés.
 * @param[in] p vertex d'un point appartenant à tous les triangles de la pile.
 */
void corrigeTriangles(tstack* pile, vertex* p, pqueue* pq);


#endif
