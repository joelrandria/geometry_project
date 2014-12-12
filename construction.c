#include "construction.h"

void test(const int i)
{
	printf("test %d\n", i);
}


/**
 * retourne s'il n'y a plus de point à ajouter*/
int insertPoint(pqueue* pq)
{
	triangle* t = pqueue_dequeue(pq);
	creerTroisTriangles(t, pq);
	return (pq->items[1]->candidats != NULL);
}

void initCarre(vertex* premier, pqueue* pq)
{
	assert(premier != NULL);
	const int naturel = VLINK_NATURAL,	suiv = VLINK_FORWARD;
	vertex* v = premier;
	vertex* v2 = v->link[naturel][suiv], *v3 = v2->link[naturel][suiv];
	
	triangle** tgls = (triangle**) malloc(sizeof(triangle*)*2);
	tgls[0] = triangle_create2(v, v2, v3);
	tgls[1] = triangle_create2(v2, v3->link[naturel][suiv], v3);
	tgls[0]->v[0] = tgls[1];
	tgls[1]->v[2] = tgls[0];
	
	v = v3->link[naturel][suiv]->link[naturel][suiv];	//v pointe vers le premier vertex qui n'ai pas un sommet du carré
	while(v != NULL)
	{
		int sur = dansTriangle2d(tgls[0], v);
		if(sur == 2)
		{
			exit(-1);
		}
		//if(sur > 0) //il est dans le triangle, mais il peut aussi être sur la limite entre les deux triangles
		else if(sur == 1)
		{
			ajouteCandidat(tgls[0], v);
		}
		else 	//sur == 0
		{
			//seulement pour les deux premiers triangles
			if(dansTriangle2d(tgls[1], v) == 2)	//sur carré?
				exit(-1);
			ajouteCandidat(tgls[1], v);
		}
		
		v = v->link[naturel][suiv];
	}
	
	pqueue_enqueue(pq, tgls[0]);
	pqueue_enqueue(pq, tgls[1]);
	free(tgls);
}

int repartage(triangle* t, vertex* v)
{
	int sur = dansTriangle2d(t, v);
	if(sur == 2)	//sur une arête
		exit(-1);
	//if(sur > 0) //il est dans le triangle, mais il peut aussi être sur la limite entre les deux triangles
	else if(sur == 1)
	{
		ajouteCandidat(t, v);
		return 1;
	}
	else 	//sur == 0
		return 0;
}

void repartageCandidats(triangle** tgls, triangle* tdeb)
{
	const int candidat = VLINK_CANDIDAT,	suiv = VLINK_FORWARD;
	vertex* v = tdeb->candidats, *suivant;
	while(v != NULL)
	{
		//bien mettre le suivant de chaque candidat à NULL;
		suivant = v->link[candidat][suiv];
		v->link[candidat][suiv] = NULL;
		
		//mettre le candidat dans l'un des triangles.
		if(!repartage(tgls[0] , v))
			if(!repartage(tgls[1] , v))
				repartage(tgls[2] , v);
		v = suivant;
	}
}

/**créer trois triangles en découpant un triangle par son premier candidat*/
void creerTroisTriangles(triangle* t, pqueue* pq)
{
	triangle** tgls = (triangle**) malloc(sizeof(triangle*)*3);
	vertex* v = t->candidats;
	tgls[0] = triangle_create(t->s[0], t->s[1], v, NULL, NULL, t->v[2]);
	tgls[1] = triangle_create(v, t->s[1], t->s[2], t->v[0], NULL, tgls[0]);
	tgls[0]->v[0] = tgls[1];
	
	tgls[2] = triangle_create(t->s[0], v, t->s[2], tgls[1], t->v[1], tgls[0]);
	tgls[0]->v[1] = tgls[2];
	tgls[1]->v[1] = tgls[2];
	
	t->candidats = t->candidats->link[VLINK_CANDIDAT][VLINK_FORWARD];
	repartageCandidats(tgls, t);
	
	pqueue_enqueue(pq, tgls[0]);
	pqueue_enqueue(pq, tgls[1]);
	pqueue_enqueue(pq, tgls[2]);
	free(tgls);
}
