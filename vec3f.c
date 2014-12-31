#include "vec3f.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void vec3f_set(vec3f* v, double x, double y, double z)
{
  v->x = x;
  v->y = y;
  v->z = z;
}

void vec3f_add(const vec3f* v1, const vec3f* v2, vec3f* r)
{
  r->x = v1->x + v2->x;
  r->y = v1->y + v2->y;
  r->z = v1->z + v2->z;
}
void vec3f_mul(const vec3f* v, double d, vec3f* r)
{
  r->x = v->x * d;
  r->y = v->y * d;
  r->z = v->z * d;
}
void vec3f_cross(const vec3f* v1, const vec3f* v2, vec3f* r)
{
  r->x = (v1->y * v2->z) - (v1->z * v2->y);
  r->y = (v1->z * v2->x) - (v1->x * v2->z);
  r->z = (v1->x * v2->y) - (v1->y * v2->x);
}

double vec3f_length(const vec3f* v)
{
  return sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}
void vec3f_normalize(const vec3f* v, vec3f* r)
{
  double length;

  length = vec3f_length(v);

  r->x = v->x / length;
  r->y = v->y / length;
  r->z = v->z / length;
}

void vec3f_print(const vec3f* v)
{
  printf("<%f, %f, %f>\r\n", v->x, v->y, v->z);
}
