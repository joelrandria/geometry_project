#include "triangle.h"

#include <math.h>
#include <stdio.h>

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

	t->candidats = NULL;
	t->distance_max = 0;

	t->queue_pos = 0;
}
void triangle_init2(triangle* t, vertex* v0, vertex* v1, vertex* v2)
{
	triangle_init(t, v0, v1, v2, NULL, NULL, NULL);
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
	int a = cote2d(t->s[0], t->s[1], p),
		b = cote2d(t->s[1], t->s[2], p);
	if( (a & b))
	{
		int c = cote2d(t->s[2], t->s[0], p);
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

void test2(const int i)
{
	printf("test %d\n", i);
}

double triangle_vertical_distance(triangle* t, vertex* v)
{
  // Normale (non unitaire) au plan contenant t
  double nX;
  double nY;
  double nZ;

  // Altitude de la projection verticale de v sur le plan contenant t
  double vProjZ;

  nX = ((t->s[1]->Y - t->s[0]->Y) * (t->s[2]->Z - t->s[0]->Z)) - ((t->s[1]->Z - t->s[0]->Z) * (t->s[2]->Y - t->s[0]->Y));
  nY = ((t->s[1]->Z - t->s[0]->Z) * (t->s[2]->X - t->s[0]->X)) - ((t->s[1]->X - t->s[0]->X) * (t->s[2]->Z - t->s[0]->Z));
  nZ = ((t->s[1]->X - t->s[0]->X) * (t->s[2]->Y - t->s[0]->Y)) - ((t->s[1]->Y - t->s[0]->Y) * (t->s[2]->X - t->s[0]->X));

  if (!nZ)
  {
    fprintf(stderr, "triangle_vertical_distance(): Erreur: Nz = %f ! Fin du programme\r\n", nZ);
    exit(-1);
  }

  vProjZ = (((t->s[0]->X - v->X) * nX) + ((t->s[0]->Y - v->Y) * nY) + (t->s[0]->Z * nZ)) / nZ;

  return (fabs(v->Z - vProjZ));
}

/**le triangle a déjà au moins ses trois sommets comme candidats*/
double ajouteCandidat(triangle* t, vertex* v)
{
	const int candidat = VLINK_CANDIDAT, suiv = VLINK_FORWARD;
	const double distV = triangle_vertical_distance(t, v);

	if(t->candidats == NULL)
	{
		t->candidats = v;
		t->distance_max = distV;
		return distV;
	}
	const double distC = t->distance_max;	//triangle_vertical_distance(t, t->candidats);
	if(distV > distC)
	{
		v->link[candidat][suiv] = t->candidats;
		t->candidats = v;
		t->distance_max = distV;
		return distV;
	}
	else
	{
		v->link[candidat][suiv] = t->candidats->link[candidat][suiv];
		t->candidats->link[candidat][suiv] = v;
		return distC;
	}
}

void triangle_print(const triangle* t)
{
	if(t == NULL)
		printf("triangle NULL\n");
	else
	{
		printf("0 : ");		vertex_print(t->s[0]);
		printf("1 : ");		vertex_print(t->s[1]);
		printf("2 : ");		vertex_print(t->s[2]);
	}
}
void triangle_print2D(const triangle* t)
{
	if(t == NULL)
		printf("triangle NULL\n");
	else
	{
		printf("0 : ");		vertex_print2D(t->s[0]);
		printf("1 : ");		vertex_print2D(t->s[1]);
		printf("2 : ");		vertex_print2D(t->s[2]);
	}
}

void triangle_tests()
{
  triangle* t;

  printf("-------- Tests unitaires de la structure triangle --------\r\n");

  t = triangle_create(vertex_create(0, 0, 0), vertex_create(-1, 1, 1), vertex_create(1, 1, 1), NULL, NULL, NULL);

  printf("distance = %f\r\n", triangle_vertical_distance(t, vertex_create(0, 0, 2)));

  printf("----------------------------------------------------------\r\n");
}

/**retrouve l'indice d'un point dans le triangle (pour corrigeTriangle)*/
int triangle_indice_point(const triangle* t, const vertex* p)
{
	int indice = 0;
	while(t->s[indice] != p)
	{
		indice++;
		assert(indice < 3);
	}
	return indice;
}

/**retrouve l'indice du triangle voisin dans le triangle 
 * (afin de retrouver le point opposé pour corrigeTriangle)*/
int triangle_indice_voisin(const triangle* t, const triangle* voisin)
{
	int indice = 0;
	while(t->v[indice] != voisin)
	{
		//triangle_print(t->v[indice]);
		indice++;
		if(indice >= 3)
		{
			printf("\n\n/!\\/!\\/!\\/!\\/!\\/!\\/!\\/!\\/!\\/!\\/!\\/!\\/!\\\n");
			printf(" triangle t: \n");
			triangle_print2D(t);
			printf(" triangle voisin: \n");
			triangle_print2D(voisin);
						
			printf("\n  voisins de t\n");
			printf(" 0 : \n");	triangle_print2D(t->v[0]);
			printf(" 1 : \n");	triangle_print2D(t->v[1]);
			printf(" 2 : \n");	triangle_print2D(t->v[2]);
			
			
			printf("\n  voisins de voisin\n");
			printf(" 0 : \n");	triangle_print2D(voisin->v[0]);
			printf(" 1 : \n");	triangle_print2D(voisin->v[1]);
			printf(" 2 : \n");	triangle_print2D(voisin->v[2]);
		}
		assert(indice < 3);
	}
	return indice;
}

/**il faut que A,B et C soit dans l'ordre CCW*/
int InCircle (const vertex *A, const vertex *B, const vertex *C, const vertex *D)
{
	vertex_print(A);	vertex_print(B);	vertex_print(C);	vertex_print(D);
	/*if(orientation(A, B, D) == orientation(A, C, D))
		return 0;	//il n'est pas dedans, résultat non voulu sinon. Il faut que A soit l'opposé de D, et B et D l'intersection des deux triangles.
	*/
	double 	ADx = A->X - D->X, ADy = A->Y - D->Y,
			BDx = B->X - D->X, BDy = B->Y - D->Y,
			CDx = C->X - D->X, CDy = C->Y - D->Y,
          
		det=((A->X + D->X)*ADx + (A->Y + D->Y)*ADy) * (BDx*CDy - BDy*CDx) +
			((B->X + D->X)*BDx + (B->Y + D->Y)*BDy) * (CDx*ADy - CDy*ADx) +
			((C->X + D->X)*CDx + (C->Y + D->Y)*CDy) * (ADx*BDy - ADy*BDx);
  
   
   /* should return (det > 0.0) ? IN : (det == 0.0) ? ON : OUT; really */
   printf("det : %lf\n", det);
   return (det > 0.00);
}

int InCircle2 (const vertex *A, const vertex *B, const vertex *C, const vertex *D)
{
	const double 	a1 = (B->Y == A->Y	?	1000000/((B->X+A->X)/2.0)	:
										-(B->X-A->X)/(B->Y-A->Y)),
					b1 = (B->Y == A->Y	?	-1000000	:
										((B->X-A->X)*(B->X+A->X)/(2.0*(B->Y-A->Y)))+
												((B->Y+A->Y)/2.0)),
					a2 = (B->Y == C->Y	?	1000000/((C->X+B->X)/2.0)	:
										-(C->X-B->X)/(C->Y-B->Y)),
					b2 = (B->Y == C->Y	?	-1000000	:
										((C->X-B->X)*(C->X+B->X)/(2.0*(C->Y-B->Y)))+
												((C->Y+B->Y)/2.0));
	const double 	xc = (b2-b1)/(a1-a2),
					yc = a1*xc+b1;
						
	return (hypot(A->X-xc,A->Y-yc) > hypot(D->X-xc,D->Y-yc) );
}

int triangleInCircle (const triangle *t, const vertex *D)
{
	return InCircle2(t->s[0], t->s[1], t->s[2], D);
}

/**faire tourner les indices des sommets du triangle afin de se retrouver avec une configuration plus confortable et éviter trop de condition
 * le sommet et le voisin à l'indice "rot" va à l'indice 0*/
void rotationIndiceTriangle(triangle* t, const int rot)
{
	if(rot != 0)
	{
		vertex* vtemp = t->s[0];
		triangle* ttemp = t->v[0];
		t->s[0] = t->s[rot];
		t->v[0] = t->v[rot];
		t->s[rot] = t->s[3-rot];
		t->v[rot] = t->v[3-rot];
		t->s[3-rot] = vtemp;
		t->v[3-rot] = ttemp;
	}
}

/**échanger deux indices du triangle*/
void swapIndiceTriangle(triangle*t, const int i1, const int i2)
{
	vertex* vtemp = t->s[i1];
	t->s[i1] = t->s[i2];
	t->s[i2] = vtemp;
	triangle* ttemp = t->v[i1];
	t->v[i1] = t->v[i2];
	t->v[i2] = ttemp;
}
