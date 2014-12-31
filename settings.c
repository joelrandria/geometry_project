#include "settings.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*! Variables externes d'accès aux paramètres de la ligne de commande. */
extern int opterr;
extern char *optarg;

static void usage()
{
  printf("Usage: ./delaunay [-n vertex_count] [-a altitude_max] [-v view_mode] [-f max_face_count] [-s gof]\r\n");

  exit(0);
}

settings* settings_alloc()
{
  return (malloc(sizeof(settings)));
}
static void settings_reset(settings* s)
{
  s->vertex_count = 50;
  s->altitude_max = 1;

  s->view_mode = VIEWMODE_3D;

  s->stop_mode = STOPMODE_NONE;
  s->max_face_count = 0;
  s->gof = -1.0;
  s->afficheBordure = 1;
  s->afficheLine = 0;
}
void settings_from_cmdline(int argc, char** argv, settings* s)
{
  int opt;

  opterr = 0;

  settings_reset(s);

  while ((opt = getopt(argc, argv, "n:a:v:f:s:b")) != EOF)
  {
    switch (opt)
    {
    case 'n':

      if (sscanf(optarg, "%d", &s->vertex_count) != 1 || s->vertex_count < 4)
		usage();
      break;

    case 'a':
      if (sscanf(optarg, "%lf", &s->altitude_max) != 1 || s->altitude_max < 0)
		usage();
      break;

    case 'v':
      if (sscanf(optarg, "%d", (int*)&s->view_mode) != 1 || s->view_mode < 0 || s->view_mode > 2)
		usage();
      break;

    case 'f':
      if (s->stop_mode != STOPMODE_NONE || sscanf(optarg, "%d", &s->max_face_count) != 1 || s->max_face_count < 2)
		usage();
      s->stop_mode = STOPMODE_FACE_COUNT;
      break;

    case 's':
      if (s->stop_mode != STOPMODE_NONE || sscanf(optarg, "%f", &s->gof) != 1 || s->gof < 0 || s->gof > 1)
		usage();
      s->stop_mode = STOPMODE_GOF;
      break;
    case 'b':
		s->afficheBordure = 0;
		break;

    default:
      usage();
    }
  }
}
void settings_print(settings* s)
{
  printf("vertex_count: %d\r\n", s->vertex_count);
  printf("altitude_max: %f\r\n", s->altitude_max);

  printf("view_mode: ");
  switch (s->view_mode)
  {
  case VIEWMODE_3D: printf("3D\r\n"); break;
  case VIEWMODE_2D: printf("2D\r\n"); break;
  case VIEWMODE_CONSOLE: printf("console\r\n"); break;
  default: printf("N/A\r\n");
  }

  printf("stop_mode: ");
  switch (s->stop_mode)
  {
  case STOPMODE_NONE: printf("none\r\n"); break;
  case STOPMODE_FACE_COUNT: printf("max_face_count = %d\r\n", s->max_face_count); break;
  case STOPMODE_GOF: printf("goodness_of_fit = %f\r\n", s->gof); break;
  default: printf("N/A\r\n");
  }
}
