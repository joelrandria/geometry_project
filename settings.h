/**
 * @file   settings.h
 * @brief  Types et structures de données relatifs aux paramètres d'exécution de l'application.
 */
#ifndef __SETTINGS_H__
#define __SETTINGS_H__

/*! Définit les différents modes de visualisation pris en charge par l'application. */
typedef enum
{
  /// Visualisation 3D avec navigation clavier et souris.
  VIEWMODE_3D = 0,
  /// Visualisation 2D fil de fer en vue de dessus. Aucune navigation possible.
  VIEWMODE_2D = 1,
  /// Mode console: Aucune visualisation graphique, aucune navigation possible.
  VIEWMODE_CONSOLE = 2

} viewmode;

/*! Définit les différents critères d'arrêt d'affinage du maillage pris en charge par l'application. */
typedef enum
{
  /// Arrêt de l'affinage du maillage une fois tous les sommets existants, insérés dans le maillage.
  STOPMODE_NONE = 0,
  /// Arrêt de l'affinage du maillage si un nombre arbitraire maximum de faces est atteint.
  STOPMODE_FACE_COUNT = 1,
  /// Arrêt de l'affinage du maillage si le maillage satisfait la valeur de 'Goodness Of Fit' spécifiée.
  STOPMODE_GOF = 2

} stopmode;

/*! Encapsule l'ensemble des paramètres d'exécution de l'application. */
typedef struct _settings
{
  /// Nombre total de sommets générés.
  int vertex_count;

  /// Altitude maximum du terrain.
  double altitude_max;

  /// Mode de visualisation courant.
  viewmode view_mode;

  /// Mode d'arrêt de l'affinage du maillage.
  int stop_mode;
  /// Nombre de faces maximum du maillage (paramètre du mode d'arrêt STOPMODE_FACE_COUNT).
  int max_face_count;
  /// Goodness Of Fit (paramètre du mode d'arrêt STOPMODE_GOF).
  float gof;
  /// Booleen: affiche les triangles sur les bords (avec au moins 1 sommet sur le carré de base) si défini à vrai. 
  int afficheBordure;
  /// Booleen: en mode VIEWMODE_3D, met en evidence les bords des triangles par des lignes grises.
  int afficheLine;

} settings;

/**
 * Alloue une instance de structure settings.
 *
 * @return Pointeur vers une instance non-initialisée de structure settings.
 */
settings* settings_alloc();
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
