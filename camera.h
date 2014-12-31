/**
 * @file   camera.h
 * @brief  Caméra FPS.
 */
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vec3f.h"
#include "transform.h"

/*! Définit une caméra FPS. */
typedef struct _camera
{
  /// Position spatiale de la caméra dans le repère monde.
  vec3f pos;

  /// Direction up de la caméra dans le repère monde.
  vec3f up;
  /// Orientation de la caméra dans le repère monde.
  vec3f front;

  /// Transformation permettant de passer du repère caméra au repère monde.
  transform view_to_world;
  /// Transformation permettant de passer du repère monde au repère caméra.
  transform world_to_view;

} camera;

/**
 * Construit une nouvelle instance de caméra.
 *
 * @param pos La position de la caméra.
 * @param up La direction up de la caméra.
 * @param front L'orientation de la caméra.
 *
 * @return Un pointeur vers la structure caméra correspondante.
 */
camera* camera_create(vec3f* pos, vec3f* up, vec3f* front);
/**
 * Affecte à la caméra spécifiée, les attributs spécifiés.
 *
 * @param c La caméra à affecter.
 * @param pos La position de la caméra.
 * @param up La direction up de la caméra.
 * @param front L'orientation de la caméra.
 */
void camera_set(camera* c, vec3f* pos, vec3f* up, vec3f* front);

/**
 * Effectue une rotation de la caméra spécifiée autour de l'axe z du monde.
 *
 * @param c La caméra à réorienter.
 * @param degree_angle L'angle de la rotation.
 */
void camera_yaw(camera* c, float degree_angle);
/**
 * Effectue une rotation de la caméra spécifiée autour de son axe x.
 *
 * @param c La caméra à réorienter.
 * @param degree_angle L'angle de la rotation.
 */
void camera_pitch(camera* c, float degree_angle);
/**
 * Translate la caméra spécifiée.
 *
 * @param c La caméra à translater.
 * @param t La translation à opérer, exprimée dans le repère caméra.
 */
void camera_translate(camera* c, const vec3f* t);

/**
 * Affiche les attributs de la caméra spécifiée.
 *
 * @param c La caméra à afficher.
 */
void camera_print(const camera* c);

#endif
