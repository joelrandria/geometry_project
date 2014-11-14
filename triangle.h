

/*! Structure pour representer un triangle. */
typedef struct _triangle
{
  struct _vertex* s[3];		//sommets du triangle
  struct _triangle* v[3];	//triangles voisins
} triangle;
