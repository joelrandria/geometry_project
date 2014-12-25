/**
 * @file   settings.h
 * @author jo <jo@jo-linux>
 * @date   Thu Dec 25 19:41:36 2014
 *
 * @brief  Définition des types et des données relatifs aux paramètres d'exécution de l'application.
 */
#ifndef __SETTINGS_H__
#define __SETTINGS_H__

/*! Les modes de visualisation du maillage pris en charge */
typedef enum
{
  VIEWMODE_3D = 0,		/**< 3D avec navigation clavier/souris */
  VIEWMODE_2D = 1,		/**< 2D fil de fer, vue de dessus */
  VIEWMODE_CONSOLE = 2		/**< Mode console */
} viewmode;

/*! Les critères d'arrêt d'affinage du maillage pris en charge */
typedef enum
{
  STOPMODE_NONE = 0,		/**< Insertion de tous les sommets dans le maillage */
  STOPMODE_FACE_COUNT = 1,	/**< Nombre de faces maximum du maillage */
  STOPMODE_GOF = 2		/**< Goodness Of Fit */
} stopmode;

/*! Encapsule les paramètres de configuration de l'application */
typedef struct _settings
{
  /*! Nombre de sommets total */
  int vertex_count;

  /*! Mode de visualisation */
  viewmode view_mode;

  /*! Mode d'arrêt de l'affinage du maillage */
  int stop_mode;
  /*! Nombre de faces maximum du maillage (paramètre du mode d'arrêt STOPMODE_FACE_COUNT) */
  int max_face_count;
  /*! Goodness Of Fit (paramètre du mode d'arrêt STOPMODE_GOF) */
  float gof;

} settings;

/**
 * Initialise les paramètres de l'application à partir des arguments spécifiés en ligne de commande.
 *
 * @param argc Le nombre d'arguments de la ligne de commande.
 * @param argv Les arguments de la ligne de commande.
 * @param s Les paramètres d'application à initialiser.
 */
void settings_from_cmdline(int argc, char** argv, settings* s);
/**
 * Affiche sur la sortie standard l'ensemble de paramètres d'application spécifié.
 *
 * @param s Les paramètres d'application à afficher sur la sortie standard.
 */
void settings_print(settings* s);

#endif
