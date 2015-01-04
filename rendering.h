/**
 * @file   rendering.h
 * @brief  Prend en charge les différents modes de rendu du terrain.
 * @author Argoud Aurélien et Joel Randria
 */
#ifndef __RENDERING_H__
#define __RENDERING_H__

/**
 * Fonction executée lors de l'appui d'une touche standard du clavier.
 *
 * @param key Le caractère correspondant à la touche appuyée.
 * @param x Abscisse de la souris dans la fenêtre au moment de l'évènement.
 * @param y Ordonnée de la souris dans la fenêtre au moment de l'évènement.
 */
void process_key_pressed(unsigned char key, int x, int y);
/**
 * Fonction executée lors de l'appui d'une touche spéciale du clavier.
 *
 * @param key Le code GLUT correspondant à la touche spéciale appuyée.
 * @param x Abscisse de la souris dans la fenêtre au moment de l'évènement.
 * @param y Ordonnée de la souris dans la fenêtre au moment de l'évènement.
 */
void process_specialkey_pressed(int key, int x, int y);
/**
 * Fonction exécutée lors d'un déplacement de la souris.
 *
 * @param x Abscisse de la souris dans la fenêtre.
 * @param y Ordonnée de la souris dans la fenêtre.
 */
void process_mouse_moved(int x, int y);

/**
 * Effectue le rendu du terrain.
 */
void render();

#endif
