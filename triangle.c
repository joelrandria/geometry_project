#include "triangle.h"

#include <math.h>

void triangle_init(triangle* t, vertex* v0, vertex* v1, vertex* v2,
		   triangle* voisin0, triangle* voisin1, triangle* voisin2)
{
  t[0] = v0;
  t[1] = v1;
  t[2] = v2;

  v[0] = voisin0;
  v[1] = voisin1;
  v[2] = voisin2;
}
void triangle_init2(triangle* t, vertex* v0, vertex* v1, vertex* v2)
{
  t[0] = v0;
  t[1] = v1;
  t[2] = v2;

  v[0] = NULL;
  v[1] = NULL;
  v[2] = NULL;
}

triangle* triangle_create(vertex* v0, vertex* v1, vertex* v2,
			  triangle* voisin0, triangle* voisin1, triangle* voisin2)
{
  triangle* t = malloc(sizeof(*t));

  triangle_init(t, v0, v1, v2, voisin0, voisin1, voisin2);

  return t;
}
triangle* triangle_create2(vertex* v0, vertex* v1, vertex* v2)
{
  return triangle_create(v0, v1, v2, NULL, NULL, NULL);
}

#define ALIGNE 0x11
#define GAUCHE 0x01
#define DROITE 0x10
int cote2d(const vertex* p1, const vertex* p2, const vertex* p)
{
	if(equal2d(p1,p2) || equal2d(p1,p) || equal2d(p2,p))
		return ALIGNE;
	
	double e = (p2->Y-p1->Y)*(p->X-p2->X)-(p->Y-p2->Y)*(p2->X-p1->X);
	//printf("%f\n", e);
	
	if(e < 0) 		return DROITE;
	else if(e > 0)	return GAUCHE;
	else 			return ALIGNE;
}

int dansTriangle2d(const triangle* t, const vertex* p)
{
	int a = cote(t->s[0], t->s[1], p),
		b = cote(t->s[1], t->s[2], p);
	if( (a & b))
	{
		int c = cote(t->s[2], t->s[0], p);
		if((b & c) && (a & c))	//a et b sont orientés du même côté avec "c". Cela marche aussi si les points sont alignés.
		{
			if(a == ALIGNE || b == ALIGNE || c == ALIGNE)
				return 2;
			else
				return 1;
		}
	}
	return 0;
}

double triangle_vertical_distance(triangle* t, vertex* v)
{
  // Normale (non unitaire) au plan contenant t
  double nX;
  double nY;
  double nZ;

  // Altitude de la projection verticale de v sur le plan contenant t
  double vProjZ;

  nX = ((t->s[1]->Y - t->s[0]->Y) * (t->s[2]->Z - t->s[0]->Z))
	- ((t->s[1]->Z - t->s[0]->Z) * (t->s[2]->Y - t->s[0]->Y));
  nY = ((t->s[1]->Z - t->s[0]->Z) * (t->s[2]->X - t->s[0]->X))
	- ((t->s[1]->X - t->s[0]->X) * (t->s[2]->Z - t->s[0]->Z));
  nZ = ((t->s[1]->X - t->s[0]->X) * (t->s[2]->Y - t->s[0]->Y))
	- ((t->s[1]->Y - t->s[0]->Y) * (t->s[2]->X - t->s[0]->X));

  if (!nZ)
  {
    // Erreur d'implémentation: Le maillage n'est pas 2,5 D !
    exit(-1);
  }

  vProjZ = (((t->s[0]->X - v->X) * nX) + ((t->s[0]->Y - v->Y) * nY) + (t->s[0]->Z * nZ)) / nZ;

  return (fabs(v->Z - vProjZ));
}
