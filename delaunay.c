#include "delaunay.h"
#include "rendering.h"
#include "construction.h"

#ifdef __LINUX__
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#endif

#include <time.h>
#include <unistd.h>
#include <stdio.h>

/* int _point_count = 0; */
/* int _test = 0; */
/* int _candid = 0; */
/* int _ins = -1; */
/* int _face = -1; */
/* double _goodness_of_fit = 0.0; */
int _line = 0;
/* int _sans_echec = 1; */
/* int _bordure = 1; */

/// Altitude minimale aléatoire des sommets générés.
/* double _altitude_min = 0.0; */
/// Altitude maximale aléatoire des sommets générés.
/* double _altitude_max = 1.0; */

/*! Initialisation des variables externes. */
pqueue* _queue = NULL;
tstack* _stack = NULL;
settings* _settings = NULL;

double myRandom(double a, double b)
{
  double tmp = random();
  return (a + tmp * ((b - a) / RAND_MAX));
}

vertex* create_random_points(settings* s)
{
  const int naturel = VLINK_NATURAL, lexico = VLINK_LEXICO, suiv = VLINK_FORWARD;

  // Vertices du carré ]0,1[² dans l'ordre lexicographique
  vertex* v = vertex_create(0, 0, myRandom(0, s->altitude_max));
  vertex* premier = v;
  vertex* vPrec = v;

  v = vertex_create(0, 1, myRandom(0, s->altitude_max));
  vPrec->link[naturel][suiv] = v;
  vPrec->link[lexico][suiv] = v;
  vPrec = v;

  v = vertex_create(1, 0, myRandom(0, s->altitude_max));
  vPrec->link[naturel][suiv] = v;
  vPrec->link[lexico][suiv] = v;
  vPrec = v;

  v = vertex_create(1, 1, myRandom(0, s->altitude_max));
  vPrec->link[naturel][suiv] = v;
  vPrec->link[lexico][suiv] = v;
  vertex* dernier = v;

  int i;
  for (i = 4; i < _settings->vertex_count; ++i)
  {
      v = vertex_create(myRandom(0, 1), myRandom(0, 1), myRandom(0, s->altitude_max));

    dernier->link[naturel][suiv] = v;
    dernier = v;
  }

  printf("fin de création des points.\n");

  return premier;
}

#define MIN(a, b)	(a < b	?	a	:	b)

int main(int argc, char **argv)
{
	clock_t start = clock();
  
  _settings = settings_alloc();
  settings_from_cmdline(argc, argv, _settings);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitWindowPosition(5,5);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Delaunay");

  glutIdleFunc(on_idle_event);
  glutDisplayFunc(render/* draw */);
  glutKeyboardFunc(process_key_pressed);
  glutSpecialFunc(process_specialkey_pressed);
  glutMotionFunc(process_mouse_moved);

  vertex* premier = create_random_points(_settings);

	//crée une priority_queue et une pile de grande taille pour acceuillir tous les triangles.
	const int taille2 = (2 * _settings->vertex_count - 6);
	const int taille = (_settings->stop_mode == STOPMODE_FACE_COUNT ? 
							MIN(taille2, _settings->max_face_count+3)	:	
							taille2);
	_queue = pqueue_create(taille);
	_stack = tstack_create(taille);
	
  initCarre(premier, _queue);

  while(insertPoint(_queue, _stack, _settings));

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glClearColor(0, 0, 0, 0);
	if(_settings->view_mode == VIEWMODE_3D)
		glEnable(GL_DEPTH_TEST);

	
  printf("fin de génération de la triangulation!\n\tTemps : %lf s\n\tTaille max atteinte dans la pile : %d\n", (clock()-start)/((double)CLOCKS_PER_SEC), _stack->nbMaxAtteint );
  glutMainLoop();

  vertex_delete(premier, VLINK_NATURAL);
  pqueue_delete(_queue);
  tstack_delete(_stack);

  return EXIT_SUCCESS;
}

void on_idle_event()
{
  clock_t start = clock();
  render();
  clock_t end = clock();

  //printf("temps : %lf\n", (end-start)/((double)CLOCKS_PER_SEC));
  if((end-start)/((double)CLOCKS_PER_SEC) < 0.020)	//60 FPS
     usleep(20000.0 - 1000000.0 * (end - start) / ((double)CLOCKS_PER_SEC));
}

void drawVertex(const vertex* v)
{
  glVertex3f(v->X, v->Y, v->Z);
}

void drawTriangle(const triangle* t)
{
  if(t != NULL)
  {
    drawVertex(t->s[0]);
    drawVertex(t->s[1]);
    drawVertex(t->s[2]);
  }
}
void drawTriangleAide(const triangle* t)
{
  glBegin(GL_TRIANGLES);
  glColor3f(1,0,0);
  drawTriangle(t->v[0]);
  glColor3f(0,1,0);
  drawTriangle(t->v[1]);
  glColor3f(0,0,1);
  drawTriangle(t->v[2]);

  glColor3f(1,0,0);
  drawVertex(t->s[0]);
  glColor3f(0,1,0);
  drawVertex(t->s[1]);
  glColor3f(0,0,1);
  drawVertex(t->s[2]);
  glEnd();
}
void drawCandidat(const triangle* t)
{
  glBegin(GL_TRIANGLES);
  glColor3f(0.5,0.5,0.5);
  drawTriangle(t);
  glEnd();

  glPointSize(7);
  glBegin(GL_POINTS);
  glColor3f(1,1,0);
  vertex* v = t->candidats;
  while(v != NULL)
  {
    drawVertex(v);
    v = v->link[VLINK_CANDIDAT][VLINK_FORWARD];
  }
  glEnd();
}

void draw()
{
  vertex* v;
  triangle* t;
  float val;

  //glColor3f(0.0, 0.0, 0.0);
  //glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 1, 0, 1);

  /* if(_test > 0) */
  /*   drawTriangleAide(_queue->items[_test]); */
  /* if(_candid > 0) */
  /*   drawCandidat(_queue->items[_candid]); */
  //printf("nb = %d\n" , _queue->size);
  glPointSize(1);

  //glColor3f(1.0, 1.0, 1.0);
  if(!_line)
    glBegin(GL_TRIANGLES);

  for(int i = 1; i <= _queue->size; i++)
  {
    t = _queue->items[i];
    /* if(!_bordure) */
    /*   if(	t->s[0]->X == 0.0 || t->s[1]->X == 0.0 || t->s[2]->X == 0.0 || */
    /* 		t->s[0]->X == 1.0 || t->s[1]->X == 1.0 || t->s[2]->X == 1.0) */
    /* 	continue; */
    if(_line)
      glBegin(GL_LINE_LOOP);
    for(int j = 0;	j < 3;	j++)
    {
      v = t->s[j];
      val = v->Z / _settings->altitude_max;
      glColor3f(0.625 + val * 0.375, 0.25 + val * 0.75, val);
      drawVertex(v);
    }
    if(_line)
      glEnd();
  }
  if(!_line)
    glEnd();

  glFlush();
}
