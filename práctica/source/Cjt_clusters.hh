/** @file Cjt_clusters.hh
    @brief Especificación de la clase Cjt_clusters
*/

#ifndef _CJT_CLUSTERS_HH_
#define _CJT_CLUSTERS_HH_

#include "Cjt_especie.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif

/** @class Cjt_clusters
    @brief Representa a un conjunto de clústers

    Contiene a un conjunto de clústers con diferentes características
*/

class Cjt_clusters {
public:
  //Constructoras

  /** @brief Creadora por defecto.

      Se ejecuta automáticamente al declarar a un conjunto de clústers.
      \pre <em>cierto</em>
      \post El resultado es un conjunto de clústers vacío
  */
  Cjt_clusters();

  //Modificadoras

  /** @brief Inicializa el conjunto de clusters.

      Permite inicializar un conjunto de clusters.
      \pre dado un conjunto de especies
      \post post inicializa el parámetro implícito, es decir, almacena el parámetro de entrada al conjunto implícito y imprime la tabla de distancias del parámetro de entrada
  */
  void inicializa_clusters(map<string, Especie> esp);

  /** @brief Actualiza la tabla de distancias
      \pre dado la tabla de distancias
      \post actualiza la tabla con las distancias que hay entre los clústers
  */
  void actualiza_tabla_distancias(map<string, map<string, double> >& distance);

  /** @brief Fusiona dos clústers
      \pre dado la tabla de distancias enter los clústers
      \post crea uno clúster nuevo a base de la fusión de los dos clústers que están a menor distancia
  */
  Cluster fusion_clusters(const map<string, map<string, double> > &distance);

  //Consultoras

  /** @brief Consulta si existe un clúster del conjunto que tenga el identificador del canal de entrada
      \pre <em>cierto</em>
      \post el resultado indica si en el parámetro implícito existe un clúster que tiene como identificador el parámetro de entrada
  */
  bool existe_cluster(string identificador) const;

  /** @brief Hace una consulta sobre el tamaño del conjunto implícito
      \pre <em>cierto</em>
      \post el resultado indica el número de elementos del conjunto implícito
  */
  int size() const;

  /** @brief Operación que busa un clúster.
      \pre dado el identificador de un clúster
      \post devuele el clúster que tiene como identificador el parámetro de entrada
  */
  Cluster buscar_cluster(string identificador) const;

  /** @brief Operación que consulta un elemento del parámetro implícito.
      \pre solo hay un elemento en el parámetro implícito
      \post retorna el clúster que representa al árbol filogenetico resultante de aplicar el algoritmo WPGMA al parámetro implícito
  */
  Cluster arbol_filogenetico ();

  //Lectura y escritura

  /** @brief Operación de escritura.
      \pre dado el identificador de un clúster
      \post se escribe por el canal estándard de salida el clúster del parámetro implícito que tiene como identificador el parámetro de entrada
  */
  void imprime_cluster(BinTree<string>& c) const;


private:

  /* Un conjunto de clústers se almacenará mediante la estructura map(diccionario), que ordena sus elementos seguún su llave, que en este caso es el identificador de un clúster(string), y en orden alfabético */

  /** @brief Estructura del conjunto de clústers, guardado en un diccionario, es decir, ordenados por orden alfabético */
  map<string, Cluster> clu;
  /** @brief Cluster que junto con min2, son los dos clústers que están en la distancia más pequeña */
  Cluster min1;
  /** @brief Cluster que junto con min1, son los dos clústers que están en la distancia más pequeña */
  Cluster min2;
  /** @brief la distancia que hay entre m1 y m2, pero dividido entre dos */
  double dist;
  /** @brief Operación que calcula los dos clústers que están a distancia más pequeña.
      \pre <em>cierto</em>
      \post modifica los valores de min1 y min2 por los clústers que están a distancia más pequeña y guarda la distancia que hay entre ellos dividido entre dos a la variable dist
  */
  void clusters_a_distancia_mas_corta(const map<string, map<string, double> > &distance);
  /** @brief Diccionario que guarda las distancias que hay entre clústers cuando se fusionan */
  map<string, double> distancias_clusters;
};
#endif
