#include "tpga4.h"

int _point_count = 0;


// Exercice sélectionné
char _opt_selex = 0;

double myRandom(double a, double b)
{
	double tmp = random();
	return (a + tmp * ((b - a) / RAND_MAX));
}

void create_random_points()
{
	assert(_point_count >=4);
	
	const int naturel = VLINK_NATURAL,	lexico = VLINK_LEXICO,	suiv = VLINK_FORWARD,	prec = VLINK_BACKWARD; 
	//le prof a dit de ne pas utiliser un tableau de point mais une liste chainée
	vertex* v = vertex_create(MARGIN, MARGIN, myRandom(0,ALTITUDE_MAX));	//c'est aussi le premier dans l'ordre lexicographique
	premier = v;
	vertex* vPrec = v;
	
	v = vertex_create(MARGIN, WINDOW_HEIGHT-MARGIN, myRandom(0,ALTITUDE_MAX));
	vPrec->link[naturel][suiv] = v;
	vPrec->link[lexico][suiv] = v;
	vPrec = v;
	
	v = vertex_create(WINDOW_WIDTH-MARGIN, MARGIN, myRandom(0,ALTITUDE_MAX));
	vPrec->link[naturel][suiv] = v;
	vPrec->link[lexico][suiv] = v;
	vPrec = v;
	
	v = vertex_create(WINDOW_WIDTH-MARGIN, WINDOW_HEIGHT-MARGIN, myRandom(0,ALTITUDE_MAX));
	vPrec->link[naturel][suiv] = v;
	vPrec->link[lexico][suiv] = v;
	
	
	
	int i; j;
	int cmp;
	vertex* v2 = v;
	for (i = 4; i < _point_count; ++i)
	{
		/*v = vertex_create(
				myRandom(MARGIN, WINDOW_WIDTH-MARGIN),
				myRandom(MARGIN, WINDOW_HEIGHT-MARGIN);
				myRandom(0,ALTITUDE_MAX));*/
		v = vertex_create(0,0,myRandom(0,ALTITUDE_MAX));
		v->link[natural][suiv] = v2;
		
		do
		{
			v->X = myRandom(MARGIN, WINDOW_WIDTH-MARGIN),
			v->Y = myRandom(MARGIN, WINDOW_HEIGHT-MARGIN);
			
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
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

void usage()
{
	printf("Usage: ./tpga4 -n count -m{1|2|3|4}\r\n");
}

int main(int argc, char **argv)
{
	int c;

	opterr = 0;
	_point_count = 50;
	_opt_selex = 'a';
	
	while ((c = getopt(argc, argv, "n:m:")) != EOF)
	{
		switch (c)
		{
			case 'n':
				if ((sscanf(optarg, "%d", &_point_count) != 1) || _point_count <= 0)
					_point_count = 50;
				break;

			case 'm':

			  sscanf(optarg, "%c", &_opt_selex);
			  break;

			default: usage(); break;
		}
	}

	if (!_opt_selex)
	{
		usage();
		return EXIT_SUCCESS;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("TP Géométrie Algorithmique #4");
	glutIdleFunc(on_idle_event);
	glutDisplayFunc(draw);

	winInit();

	create_random_points();

	switch (_opt_selex)
	{
		default: draw();
	}

	glutMainLoop();
	
	//free(_points_ex1);


	return EXIT_SUCCESS;
}

void on_idle_event()
{
	draw();
}

void draw()
{
}
/*  glColor3f(0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  switch(_opt_selex)
  {
  case '1':

    glColor3f(1, 0, 0);
    draw_exercice(_points_ex1, _point_count, _convex_ordonnes_ex1);
    break;

  case '2':

    glColor3f(0, 1, 0);
    draw_exercice(_points_ex2, _point_count, _convex_ordonnes_ex2);
    break;

  case '3':

    glColor3f(0, 0, 1);
    draw_exercice(_points_ex3, _point_count, _convex_ordonnes_ex3);
    break;
    
  case '4':

    glColor3f(1, 1, 0);
    draw_exercice(_points_ex4, _point_count, _convex_ordonnes_ex4);
    break;

  case 'a':

    glViewport(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    glColor3f(1, 0, 0);
    draw_exercice(_points_ex1, _point_count, _convex_ordonnes_ex1);

    glViewport(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    glColor3f(0, 1, 0);
    draw_exercice(_points_ex2, _point_count, _convex_ordonnes_ex2);

    glViewport(0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    glColor3f(0, 0, 1);
    draw_exercice(_points_ex3, _point_count, _convex_ordonnes_ex3);
    
    glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    glColor3f(1, 1, 0);
    draw_exercice(_points_ex4, _point_count, _convex_ordonnes_ex4);

    break;
  }

  glFlush();
}
void draw_points(const vertex* points, const unsigned int point_count)
{
  unsigned int i;

  glBegin(GL_POINTS);

  glColor3f(1, 1, 1);
  glPointSize(2);

  for (i = 0; i < _point_count; ++i)
    glVertex2f(points[i].X, points[i].Y);

  glEnd();
}


#define drawVertex(v) glVertex2f( v->X, v->Y)

void draw_exercice(const vertex* points, const unsigned int point_count, const vertex* hull)
{
	const vertex *v = hull;
	if(v != NULL)
	{
		const vertex *debList = v;

		// Rendu de l'enveloppe convexe
		glBegin(GL_LINE_LOOP);

		do
		{
			drawVertex(v);

			v = v->link[VLINK_CONVEX][VLINK_FORWARD];
		}
		while (v != debList);

		glEnd();
	}
	else
		fprintf(stderr, "problème: anneau convex NULL\n");

	// Rendu des points
	draw_points(points, point_count);
}*/
