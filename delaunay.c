#include "delaunay.h"

// Initialisation des variables externes
int _point_count = 0;

double _altitude_min = 0.0f;
double _altitude_max = 0.5f;

vertex* premier = NULL;

double myRandom(double a, double b)
{
	double tmp = random();
	return (a + tmp * ((b - a) / RAND_MAX));
}

void create_random_points()
{
	assert(_point_count >=4);

	const int naturel = VLINK_NATURAL,
	  lexico = VLINK_LEXICO,
	  suiv = VLINK_FORWARD;

	// Vertices du carré ]0,1[² dans l'ordre lexicographique
	vertex* v = vertex_create(0, 0, myRandom(_altitude_min, _altitude_max));
	premier = v;
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

	create_random_points();

	vertex_print_all(premier, VLINK_NATURAL, VLINK_FORWARD);

	glutMainLoop();

	vertex_delete(premier, VLINK_NATURAL);

	return EXIT_SUCCESS;
}

void on_idle_event()
{
	draw();
}

void draw()
{
  vertex* v;

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_POINTS);
  glColor3f(1, 1, 1);

  v = premier;
  while (v != NULL)
  {
    glVertex3f(v->X, v->Y, v->Z);
    v = v->link[VLINK_NATURAL][VLINK_FORWARD];
  }

  glEnd();
  glFlush();
}
