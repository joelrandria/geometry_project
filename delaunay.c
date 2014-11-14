#include "tpga4.h"

int _point_count = 0;

vertex* _points_ex1 = NULL;
/*vertex* _points_ex2 = NULL;
vertex* _points_ex3 = NULL;
vertex* _points_ex4 = NULL;

vertex* _convex_ordonnes_ex1 = NULL;
vertex* _convex_ordonnes_ex2 = NULL;
vertex* _convex_ordonnes_ex3 = NULL;
vertex* _convex_ordonnes_ex4 = NULL;*/

// Exercice sélectionné
char _opt_selex = 0;

double myRandom(double a, double b)
{
	double tmp = random();
	return (a + tmp * ((b - a) / RAND_MAX));
}

void create_random_points()
{
  int i;

  _points_ex1 = malloc(sizeof(*_points_ex1) * _point_count);

  for (i = 0; i < _point_count; ++i)
  {
    vertex_init(&_points_ex1[i],
		myRandom(MARGIN, WINDOW_WIDTH-MARGIN),
		myRandom(MARGIN, WINDOW_HEIGHT-MARGIN));
		myRandom(0,ALTITUDE_MAX);
  }

  /*_points_ex2 = vertex_copy(_points_ex1, _point_count);
  _points_ex3 = vertex_copy(_points_ex1, _point_count);
  _points_ex4 = vertex_copy(_points_ex1, _point_count);*/
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
		case '1': tpga4_ex1(); break;
		case '2': tpga4_ex2(); break;
		case '3': tpga4_ex3(); break;
		case '4': tpga4_ex4(); break;
	        case 'a':

		  tpga4_ex1();
		  tpga4_ex2();
		  tpga4_ex3();
		  tpga4_ex4();

		  break;
	}

	glutMainLoop();

	free(_points_ex1);
	free(_points_ex2);
	free(_points_ex3);
	free(_points_ex4);

	return EXIT_SUCCESS;
}

void on_idle_event()
{
	draw();
}

void draw()
{
  glColor3f(0, 0, 0);
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

/*void draw_jarvis(const vertex* points, const unsigned int point_count, const int_list* hull_points)
{
  int hull_point;

  // Rendu de l'enveloppe convexe
  glBegin(GL_LINE_LOOP);

  while (hull_points)
  {
    hull_point = hull_points->value;
    glVertex2f(points[hull_point].X, points[hull_point].Y);
    hull_points = hull_points->next;
  }

  glEnd();

  // Rendu des points
  draw_points(points, point_count);
}*/

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
}
