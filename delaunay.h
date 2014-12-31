/**
 * @file   delaunay.h
 * @brief  
 */
#ifndef __DELAUNAY_H__
#define __DELAUNAY_H__

#include "pqueue.h"
#include "settings.h"

/*! Dimensions de la fenêtre d'application. */
#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 768

/// Paramètres de configuration de l'application.
extern settings* _settings;

/// File de priorité des facettes du terrain.
extern pqueue* _queue;

/**
 * Gestionnaire d'évènement executé lors du passage de l'application à l'état inactif.
 */
void on_idle_event();

#endif
