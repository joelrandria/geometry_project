#include "construction.h"

triangle* algo()
{
	assert(premier != NULL);
	const int naturel = VLINK_NATURAL,	candidat = VLINK_CANDIDAT,	suiv = VLINK_FORWARD;
	vertex* v = premier;
	vertex* v2 = v->link[naturel][suiv], v3 = v2->link[naturel][suiv];
	
	triangle* tgls = (triangle*) malloc(sizeof(triangle)*2);
	tgls[0] = triangle_create2(v, v2, v3);
	tgls[1] = triangle_create2(v2, v3->link[naturel][suiv], v3);
	tgls[0]->v[0] = tgls[1];
	tgls[1]->v[2] = tgls[0];
	
	v = v3->link[naturel][suiv]->link[naturel][suiv];	//v pointe vers le premier vertex qui n'ai pas un sommet du carré
	while(v != null)
	{
		int sur = dansTriangle2d(tgls[0], v);
		if(sur > 0) //il est dans le triangle, mais il peut aussi être sur la limite entre les deux triangles
		{
			ajouteCandidat(tgls[0], v);
			if(sur == 2 && dansTriangle2d(tgls[1], v))	//sur la limite (mais sur quel des trois segments du triangle). dansTriangle2d retournera soit 0, soit 2
				ajouteCandidat(tgls[1], v);
		}
		else
			ajouteCandidat(tgls[1], v);
			
		v = v->link[naturel][suiv];
	}
	
	return tgls;
}


//void repartageCandidat(triangle* t1, triangle* t2, triangle* t1res, triangle* t2res)
