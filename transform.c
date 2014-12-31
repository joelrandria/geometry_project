#include "transform.h"

#include <math.h>
#include <stdio.h>

void transform_identity(transform* t)
{
  int r;
  int c;

  for (r = 0; r < 4; ++r)
  {
    for (c = 0; c < 4; ++c)
    {
      if (r == c)
	t->v[r][c] = 1;
      else
	t->v[r][c] = 0;
    }
  }
}
void transform_copy(const transform* t, transform* r)
{
  int i;
  int j;

  for (i = 0; i < 4; ++i)
    for (j = 0; j < 4; ++j)
      r->v[i][j] = t->v[i][j];
}
void transform_setmatrix(transform* t,
			 float v00, float v01, float v02, float v03,
			 float v10, float v11, float v12, float v13,
			 float v20, float v21, float v22, float v23,
			 float v30, float v31, float v32, float v33)
{
  t->v[0][0] = v00;
  t->v[0][1] = v01;
  t->v[0][2] = v02;
  t->v[0][3] = v03;

  t->v[1][0] = v10;
  t->v[1][1] = v11;
  t->v[1][2] = v12;
  t->v[1][3] = v13;

  t->v[2][0] = v20;
  t->v[2][1] = v21;
  t->v[2][2] = v22;
  t->v[2][3] = v23;

  t->v[3][0] = v30;
  t->v[3][1] = v31;
  t->v[3][2] = v32;
  t->v[3][3] = v33;
}

void transform_mul(const transform* t, const vec3f* v, vec3f* r)
{
  r->x = (t->v[0][0] * v->x) + (t->v[0][1] * v->y) + (t->v[0][2] * v->z);
  r->y = (t->v[1][0] * v->x) + (t->v[1][1] * v->y) + (t->v[1][2] * v->z);
  r->z = (t->v[2][0] * v->x) + (t->v[2][1] * v->y) + (t->v[2][2] * v->z);
}

#define RADIANS(angle) ((M_PI * angle) / 180.0f)

void transform_getrotation(float degree_angle, const vec3f* axis, transform* r)
{
  vec3f a;
  float s;
  float c;

  vec3f_normalize(axis, &a);

  s = sinf(RADIANS(degree_angle));
  c = cosf(RADIANS(degree_angle));

  r->v[0][0] = a.x * a.x + ( 1.f - a.x * a.x ) * c;
  r->v[0][1] = a.x * a.y * ( 1.f - c ) - a.z * s;
  r->v[0][2] = a.x * a.z * ( 1.f - c ) + a.y * s;
  r->v[0][3] = 0;

  r->v[1][0] = a.x * a.y * ( 1.f - c ) + a.z * s;
  r->v[1][1] = a.y * a.y + ( 1.f - a.y * a.y ) * c;
  r->v[1][2] = a.y * a.z * ( 1.f - c ) - a.x * s;
  r->v[1][3] = 0;

  r->v[2][0] = a.x * a.z * ( 1.f - c ) - a.y * s;
  r->v[2][1] = a.y * a.z * ( 1.f - c ) + a.x * s;
  r->v[2][2] = a.z * a.z + ( 1.f - a.z * a.z ) * c;
  r->v[2][3] = 0;

  r->v[3][0] = 0;
  r->v[3][1] = 0;
  r->v[3][2] = 0;
  r->v[3][3] = 1;
}

static void transforme_swap(transform* r, int r1, int c1, int r2, int c2)
{
  double temp;

  temp = r->v[r1][c1];
  r->v[r1][c1] = r->v[r2][c2];
  r->v[r2][c2] = temp;
}
void transform_inverse(const transform* t, transform* r)
{
  transform_copy(t, r);

  transforme_swap(r, 0, 1, 1, 0);
  transforme_swap(r, 0, 2, 2, 0);
  transforme_swap(r, 1, 2, 2, 1);

  r->v[0][3] = -(r->v[0][0] * t->v[0][3]) - (r->v[0][1] * t->v[1][3]) - (r->v[0][2] * t->v[2][3]);
  r->v[1][3] = -(r->v[1][0] * t->v[0][3]) - (r->v[1][1] * t->v[1][3]) - (r->v[1][2] * t->v[2][3]);
  r->v[2][3] = -(r->v[2][0] * t->v[0][3]) - (r->v[2][1] * t->v[1][3]) - (r->v[2][2] * t->v[2][3]);
}

void transform_print(const transform* t)
{
  printf("%f %f %f %f\r\n%f %f %f %f\r\n%f %f %f %f\r\n%f %f %f %f\r\n",
	 t->v[0][0], t->v[0][1], t->v[0][2], t->v[0][3],
	 t->v[1][0], t->v[1][1], t->v[1][2], t->v[1][3],
	 t->v[2][0], t->v[2][1], t->v[2][2], t->v[2][3],
	 t->v[3][0], t->v[3][1], t->v[3][2], t->v[3][3]);
}
