#ifndef __TPGA4_H__
#define __TPGA4_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>
#include <string.h>

#include "vertex.h"

#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 768
#define MARGIN 20
#define ALTITUDE_MAX = 20

// Accès aux options de la ligne de commandes
extern char *optarg;
extern int opterr;

// Variables globales communes initialisées au démarrage de l'application
extern int _point_count;	// nombre de points défini en paramêtre avec l'option "-n"

extern vertex* _points_ex1;	// copies des vertices pour l'exercice 1 (Jarvis)
/*extern vertex* _points_ex2;	// copies des vertices pour l'exercice 2 (Graham)
extern vertex* _points_ex3;	// copies des vertices pour l'exercice 3 (Insertion lexico)
extern vertex* _points_ex4;	// copies des vertices pour l'exercice 4 (Divide & Conquer)

// Variables globales initialisées spécifiquement par les différents exercices

extern vertex* _convex_ordonnes_ex1;	// enveloppe convexe générée par l'exercice 1
extern vertex* _convex_ordonnes_ex2;	// enveloppe convexe générée par l'exercice 2
extern vertex* _convex_ordonnes_ex3;	// enveloppe convexe générée par l'exercice 3
extern vertex* _convex_ordonnes_ex4;	// enveloppe convexe générée par l'exercice 4*/

// Gestionnaires d'évènements
void on_idle_event();

// Fonctions de rendu communes aux exercices
void draw();
void draw_points(const vertex* points, const unsigned int point_count);


// Fonction de rendu commune aux exercices 2, 3 et 4
void draw_exercice(const vertex* points, const unsigned int point_count, const vertex* hull);

#endif
