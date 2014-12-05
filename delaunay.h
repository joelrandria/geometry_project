#ifndef __DELAUNAY_H__
#define __DELAUNAY_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#ifdef __LINUX__
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#endif

#include "vertex.h"
#include "construction.h"

#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 768

// Accès aux options de la ligne de commandes
extern char *optarg;
extern int opterr;

// Options
extern int _point_count;	// nombre de points défini en paramêtre avec l'option "-n"

extern double _altitude_min;	// altitude minimum des sommets
extern double _altitude_max;	// altitude maximum des sommets

// Variables globales
extern vertex* premier;		// pointeur vers le premier point chainé de la liste de points

// Gestionnaires d'évènements
void on_idle_event();

// Rendu
void draw();

#endif
