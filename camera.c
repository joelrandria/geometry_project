#include "camera.h"

#include <stdio.h>
#include <stdlib.h>

static const vec3f _world_up = {0, 0, 1};

static void camera_right(camera* c, vec3f* r)
{
  vec3f_cross(&c->front, &c->up, r);
}
static void camera_updatetransforms(camera* c)
{
  vec3f camera_x;
  vec3f camera_z;

  camera_right(c, &camera_x);
  vec3f_mul(&c->front, -1, &camera_z);

  transform_setmatrix(&c->view_to_world,
		      camera_x.x, c->up.x, camera_z.x, c->pos.x,
		      camera_x.y, c->up.y, camera_z.y, c->pos.y,
		      camera_x.z, c->up.z, camera_z.z, c->pos.z,
		      0, 0, 0, 1);

  transform_inverse(&c->view_to_world, &c->world_to_view);
}

camera* camera_create(vec3f* pos, vec3f* up, vec3f* front)
{
  camera* c;

  c = malloc(sizeof(*c));

  camera_set(c, pos, up, front);

  return c;
}
void camera_set(camera* c, vec3f* pos, vec3f* up, vec3f* front)
{
  c->pos = *pos;
  c->up = *up;
  c->front = *front;

  camera_updatetransforms(c);
}

void camera_yaw(camera* c, float degree_angle)
{
  vec3f new_up;
  vec3f new_front;

  transform world_up_rotation;

  transform_getrotation(degree_angle, &_world_up, &world_up_rotation);

  transform_mul(&world_up_rotation, &c->up, &new_up);
  transform_mul(&world_up_rotation, &c->front, &new_front);

  vec3f_normalize(&new_up, &c->up);
  vec3f_normalize(&new_front, &c->front);

  camera_updatetransforms(c);
}
void camera_pitch(camera* c, float degree_angle)
{
  vec3f camera_x;
  vec3f new_up;
  vec3f new_front;

  transform camera_x_rotation;

  camera_right(c, &camera_x);

  transform_getrotation(degree_angle, &camera_x, &camera_x_rotation);

  transform_mul(&camera_x_rotation, &c->up, &new_up);
  transform_mul(&camera_x_rotation, &c->front, &new_front);

  vec3f_normalize(&new_up, &c->up);
  vec3f_normalize(&new_front, &c->front);

  camera_updatetransforms(c);
}
void camera_translate(camera* c, const vec3f* t)
{
  vec3f world_translation;

  transform_mul(&c->view_to_world, t, &world_translation);

  vec3f_add(&c->pos, &world_translation, &c->pos);

  camera_updatetransforms(c);
}

void camera_print(const camera* c)
{
  printf("----------- Camera -----------\r\n");

  printf("Pos: ");
  vec3f_print(&c->pos);

  printf("Up: ");
  vec3f_print(&c->up);

  printf("Front: ");
  vec3f_print(&c->front);

  printf("\r\nViewToWorld:\r\n");
  transform_print(&c->view_to_world);

  printf("\r\nWorldToView:\r\n");
  transform_print(&c->world_to_view);

  printf("------------------------------\r\n");
}
