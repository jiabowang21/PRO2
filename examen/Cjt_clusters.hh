/** @file Cjt_clusters.hh
    @brief Especificación de la clase Cjt_clusters
*/

#ifndef _CJT_CLUSTERS_HH_
#define _CJT_CLUSTERS_HH_

#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <map>
#endif

/** @class Cjt_clusters
    @brief Representa a un conjunto de clústers.

    Ofrece un conjunto de operaciones para calcular la posición de una especie dentro de la línia evolutiva de un conjunto de especies, es decir, el cálculo del árbol filogenético de un conjunto de diversas especie.
*/

class Cjt_clusters {
public:
  //Constructoras

  /** @brief Creadora por defecto.

      \pre <em>cierto</em>
      \post el resultado es un conjunto de clústers vacío, sin ningun clúster
  */
  Cjt_clusters();

  //Modificadoras

  /** @brief Modifica los valores implícitos del conjunto de clústers.

      \pre <em>cierto</em>
      \post se limpia el parámetro implícito, es decir, se vacia el conjunto de clústers que tenia el parámetro implícito y sus respectivas distancias, el parámetro implícito pasa a ser un conjunto de clústers vacío
  */
  void inicializa();

  /** @brief Añade al parámetro implícito un nuevo clúster, gestiona la entrada de un clúster al conjunto de clústers.

      \pre el parámetro implícito no contiene ningún clúster con identificador = ident
      \post se añade el clúster con identificador = ident al parámetro implícito
  */
  void adderir_cluster(const string &ident);

  /** @brief Añade la distancia que hay entre dos clústers.
      \pre existen los dos clústers con identificador = ident y identificador = ident2 en el parámetro implícito, n = distancia entre estos dos clústers
      \post se añade n al parámetro implícito como distancia entre los clústers referenciados como ident y ident2
  */
  void distancias_clusters(const string &ident, const string &ident2, const double &n);

  /** @brief Ordena las distancias que hay entre los clústers, de forma creciente según su identificador.
      \pre <em>cierto</em>
      \post se agrupan y se ordenan de forma creciente según el identificador de un clúster las distancias que hay entre los clústers
  */
  void ordenar_distancias();

  /** @brief Se ejecuta un paso del algoritmo WPGMA, es decir, los dos clústers a menor distancia pasan a formar uno solo.
      \pre el parámetro implícito contiene al menos dos clústers y los clústers junto con sus distancias están ordenadas crecientemente
      \post se añade un clúster formado por los dos clústers a menor distancia y se eliminan esos dos clústers, y se actualizan las distancias (la distancia de los clústers que no se han modificado al nuevo clúster será la suma de la distancia que tenia con dos clústers eliminados entre dos)
  */
  void ejecuta_paso_wpgma();

  //Consultoras

  /** @brief Consulta si existe un clúster del parámetro implícito con identificador = ident.
      \pre <em>cierto</em>
      \post el resultado indica si existe en el parámetro implícito un clúster con identificador = ident
  */
  bool existe_cluster(const string &ident) const;

  /** @brief Hace una consulta sobre el tamaño del conjunto implícito, es decir, cuántos elementos contiene.
      \pre <em>cierto</em>
      \post el resultado indica el número de elementos del conjunto de clústers del parámetro implícito
  */
  int size() const;

  //Escritura

  /** @brief Operación de escritura de un clúster.
      \pre existe el clúster con identificador = ident dentro del parámetro implícito
      \post se imprime por el canal de salida el clúster con identificador = ident
  */
  void imprime_cluster(const string &ident);

  /** @brief Operación de escritura del árbol filogenético que se forma con el conjunto de clústers del parámetro implícito.
      \pre hay únicamente un clúster en el conjunto implícito
      \post se imprime por el canal de salida el único clúster del conjunto implícito
  */
  void imprime_arbol();

  /** @brief Operación de escritura de las distancias que hay entre los clústers.
      \pre <em>cierto</em>
      \post imprime por el canal de salida la tabla de distancias del parámetro implícito
  */
  void imprime_tabla_distancias() const;

private:

  /* Un conjunto de clústers se almacenará mediante la estructura map(diccionario), que ordena sus elementos seguún su llave, que en este caso es el identificador de un clúster(string), y en orden creciente */

  /** @brief Estructura del conjunto de clústers, guardado en un diccionario y un clúster en forma arbolescente. */
  map<string, BinTree<Cluster> > clu;

  /** @brief Estructura del conjunto de distancias del conjunto de clústers, guardado en un diccionario, es decir, ordenados por orden creciente según su llave. */
  map<string, map<string, double> > distance;

  /** @brief Conjunto de distancias temporal, guardado en un diccionario. */
  map<pair<string, string>, double> dis;

  map<string, double> cardinal;

  /** @brief Cluster que junto con min2, son los dos clústers que están a menor distancia del conjunto de clústers. */
  BinTree<Cluster> min1;

  /** @brief Cluster que junto con min1, son los dos clústers que están a menor distancia del conjunto de clústers. */
  BinTree<Cluster> min2;

  /** @brief la distancia que hay entre los clústers m1 y m2. */
  double dist;

  /** @brief Operación que fusiona dos clústers.
      \pre <em>cierto</em>
      \post crea uno clúster nuevo a base de la fusión de los dos clústers que están a menor distancia (min1, min2)
  */
  void fusion_clusters(BinTree<Cluster>& c);

  /** @brief Operación que calcula los dos clústers que están a distancia más pequeña.
      \pre hay al menos dos clústers en el conjunto de clústers
      \post calcula los dos clústers a menor distancia y los guarda en los clústers min1 y min2 respectivamente, y a dist la distancia que hay entre estos dos clústers
  */
  void clusters_a_distancia_mas_corta();

  /** @brief Operación que imprime la estructura arbolescente del clúster.
      \pre <em>cierto</em>
      \post imprime por el canal de salida el árbol c en un recorrido en preorden y su formato es [raíz [subárbol izquierdo][subárbol derecho]]...
  */
  void imprime(const BinTree<Cluster>& c);
};
#endif
