#include "delaunay.h"
#include "pqueue.h"

// Initialisation des variables externes
int _point_count = 0;

double _altitude_min = 0.0f;
double _altitude_max = 0.5f;

//vertex* premier = NULL;
pqueue* _queue = NULL;

double myRandom(double a, double b)
{
	double tmp = random();
	return (a + tmp * ((b - a) / RAND_MAX));
}

vertex* create_random_points()
{
	assert(_point_count >=4);

	const int naturel = VLINK_NATURAL,
	  lexico = VLINK_LEXICO,
	  suiv = VLINK_FORWARD;

	// Vertices du carré ]0,1[² dans l'ordre lexicographique
	vertex* v = vertex_create(0, 0, myRandom(_altitude_min, _altitude_max));
	vertex* premier = v;
	vertex* vPrec = v;

	v = vertex_create(0, 1, myRandom(_altitude_min, _altitude_max));
	vPrec->link[naturel][suiv] = v;
	vPrec->link[lexico][suiv] = v;
	vPrec = v;

	v = vertex_create(1, 0, myRandom(_altitude_min, _altitude_max));
	vPrec->link[naturel][suiv] = v;
	vPrec->link[lexico][suiv] = v;
	vPrec = v;

	v = vertex_create(1, 1, myRandom(_altitude_min, _altitude_max));
	vPrec->link[naturel][suiv] = v;
	vPrec->link[lexico][suiv] = v;
	vertex* dernier = v;

	int i;
	int cmp;
	vertex* v2 = v;
	for (i = 4; i < _point_count; ++i)
	{
		/*v = vertex_create(
				myRandom(MARGIN, WINDOW_WIDTH-MARGIN),
				myRandom(MARGIN, WINDOW_HEIGHT-MARGIN);
				myRandom(0,_altitude_max));*/
		v = vertex_create(0,0, myRandom(_altitude_min, _altitude_max));
		dernier->link[naturel][suiv] = v;
		dernier = v;

		do
		{
			v->X = myRandom(0, 1),
			v->Y = myRandom(0, 1);

			vPrec = premier;
			v2= vPrec->link[lexico][suiv];
			while(v2 != NULL && (cmp = lexico_cmp(v2, v))== -1)
			{
				vPrec = v2;
				v2 = v2->link[lexico][suiv];
			}

			if(cmp != 0)	//si le vertex(x,y) n'est pas déjà dans la chaine	(-1 => v2==NULL)
			{
				vPrec->link[lexico][suiv] = v;
				v->link[lexico][suiv] = v2;
			}
			//else: il faut changer les valeurs du vertex.
		}
		while(cmp == 0);	//tant que le vertex à les mêmes coordonnées (x,y) qu'un autre point
	}

	chainageArriere(premier, naturel);
	chainageArriere(premier, lexico);
	
	return premier;
}



void winInit()
{
	gluOrtho2D(0, 1, 0, 1);
}

void usage()
{
	printf("Usage: ./delaunay -n count\r\n");
}

int main(int argc, char **argv)
{
	int c;

	opterr = 0;
	_point_count = 50;

	while ((c = getopt(argc, argv, "n:")) != EOF)
	{
		switch (c)
		{
			case 'n':

				if ((sscanf(optarg, "%d", &_point_count) != 1) || _point_count <= 0)
					_point_count = 50;
				break;

			default: usage(); break;
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Delaunay");
	glutIdleFunc(on_idle_event);

	glutDisplayFunc(draw);

	winInit();

	vertex* premier = create_random_points();

	_queue = pqueue_create(2*_point_count-6);
	initCarre(premier, _queue);
	insertPoint(_queue);
	insertPoint(_queue);
	//vertex_print_all(premier, VLINK_LEXICO, VLINK_FORWARD);
	/*triangle** tgls = algo();
	//vertex_print_all(tgls[0]->candidats, VLINK_CANDIDAT, VLINK_FORWARD);
	vertex* v = tgls[0]->candidats;
	while (v != NULL)
	{
		printf("hauteur: %lf, x: %lf, y: %lf, z:%lf\r\n", triangle_vertical_distance(tgls[0], v), v->X, v->Y, v->Z);
		v = v->link[VLINK_CANDIDAT][VLINK_FORWARD];
	}
	printf("\n");
	
	//vertex_print_all(tgls[1]->candidats, VLINK_CANDIDAT, VLINK_FORWARD);
	v = tgls[1]->candidats;
	while (v != NULL)
	{
		printf("hauteur: %lf, x: %lf, y: %lf, z:%lf\r\n", triangle_vertical_distance(tgls[1], v), v->X, v->Y, v->Z);
		v = v->link[VLINK_CANDIDAT][VLINK_FORWARD];
	}*/

	glutMainLoop();

	vertex_delete(premier, VLINK_NATURAL);
	pqueue_delete(_queue);

	return EXIT_SUCCESS;
}

void on_idle_event()
{
	draw();
}

void draw()
{
	
	vertex* v;
	triangle* t;
	float val;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//printf("nb = %d\n" , _queue->size);
	glPointSize(3);
	for(int i = 1;	i < _queue->size;	i++)
	{
		glBegin(GL_LINE_LOOP);
		t = _queue->items[i];
		for(int j = 0;	j < 3;	j++)
		{
			v = t->s[j];
			val = (v->Z-_altitude_min)/(_altitude_max-_altitude_min);
			glColor3f(0.625+val*0.375, 0.25+val*0.75, val);
			glVertex3f(v->X, v->Y, v->Z);
		}		
		glEnd();	
	}

	
	/*glBegin(GL_POINTS);

	v = premier;
	float val;
	while (v != NULL)
	{
		val = (v->Z-_altitude_min)/(_altitude_max-_altitude_min);
		glColor3f(0.625+val*0.375, 0.25+val*0.75, val);
		glVertex3f(v->X, v->Y, v->Z);
		v = v->link[VLINK_NATURAL][VLINK_FORWARD];
	}*/

	glFlush();
}
