#include "triangle.h"

/*void triangle_init_candidat(triangle* t)
{
	const int candidat = VLINK_CANDIDAT,	suiv = VLINK_FORWARD;
	t->candidats = t->s[0];
	t->s[0]->link[candidat][suiv] = t->s[1];
	t->s[1]->link[candidat][suiv] = t->s[2];
}*/

void triangle_init(triangle* t,
				   vertex* v0, vertex* v1, vertex* v2,
				   triangle* voisin0, triangle* voisin1, triangle* voisin2)
{
	t->s[0] = v0;
	t->s[1] = v1;
	t->s[2] = v2;

	t->v[0] = voisin0;
	t->v[1] = voisin1;
	t->v[2] = voisin2;

	//triangle_init_candidat(t);
}
void triangle_init2(triangle* t, vertex* v0, vertex* v1, vertex* v2)
{
	t->s[0] = v0;
	t->s[1] = v1;
	t->s[2] = v2;


	t->v[0] = NULL;
	t->v[1] = NULL;
	t->v[2] = NULL;

	//triangle_init_candidat(t);
}

triangle* triangle_create(vertex* v0, vertex* v1, vertex* v2, triangle* voisin0, triangle* voisin1, triangle* voisin2)
{
  triangle* t = malloc(sizeof(*t));

  triangle_init(t, v0, v1, v2, voisin0, voisin1, voisin2);

  return t;
}
triangle* triangle_create2(vertex* v0, vertex* v1, vertex* v2)
{
  return triangle_create(v0, v1, v2, NULL, NULL, NULL);
}

//Joel, si tu préfère ton propre code, prend le.
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

double plane_vertical_distance(triangle* t, vertex* v)
{
	return fabs(1);
}

/**le triangle a déjà au moins ses trois sommets comme candidats*/
triangle* ajouteCandidat(triangle* t, vertex* v)
{
	const int candidat = VLINK_CANDIDAT,	suiv = VLINK_FORWARD;
	if(plane_vertical_distance(t, v) > plane_vertical_distance(t, t->candidats))
	{
		v->link[candidat][suiv] = t->candidats);
		t->candidats = v;
	}
	else
	{
		v->link[candidat][suiv] = t->candidats->link[candidat][suiv];
		t->candidats->link[candidat][suiv] = v;
	}
	return t;
}
