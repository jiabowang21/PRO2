/** @file Cjt_especie.hh
    @brief Especificación de la clase Cjt_especie
*/

#ifndef _CJT_ESPECIE_HH_
#define _CJT_ESPECIE_HH_

#include "Especie.hh"
#include "Cjt_clusters.hh"

#ifndef NO_DIAGRAM
#include <string>
#include <cmath>
#endif

/** @class Cjt_especie
    @brief Representa a un conjunto de especies.

    Ofrece operaciones para introducir una especie al conjunto de especies, de lectura y escritura del conjunto de especies. Y también el cálculo de la distancia que hay entre dos especies.
*/

class Cjt_especie {
public:
  //Constructoras

  /** @brief Creadora por defecto.

      \pre <em>cierto</em>
      \post El resultado es un conjunto vacío, sin ninguna especie
  */
  Cjt_especie();

  //Modificadoras

  /** @brief Añade al parámetro implícito una nueva especie.

      \pre el parámetro implícito no contiene ninguna especie con el identificador de esp
      \post se añade la especie esp al parámetro implícito
  */
  void adderir_especie(const Especie &esp);

  /** @brief Elimina del parámetro implícito una especie existente en ella.

      \pre existe una especie del parámetro implícito con identificador = ident
      \post el parámetro implícito contiene las mismas especies que el original menos la especie con identificador = ident
  */
  void elimina_especie(const string &ident);

  /** @brief Calcula la tabla de distancias que hay entre las especies del parámetro implícito.
      \pre <em>cierto</em>
      \post calcula la tabla de distancias entre las especies que hay formados en el conjunto de especies del parámetro implícito
  */
  void tabla_distancias();

  //Consultoras

  /** @brief Consultora de si el parámetro implícito está vacío.

      \pre <em>cierto</em>
      \post el resultado indica si el parámetro implícito es vacío o no
  */
  bool empty() const;

  /** @brief Consultora de la existencia de una especie dentro del parámetro implícito.
      \pre <em>cierto</em>
      \post el resultado indica si existe una especie en el parámetro implícito con identificador = ident
  */
  bool existe_especie(const string &ident) const;

  /** @brief Consultora de la especie que tiene como identificador = ident dentro del parámetro implícito.
      \pre existe una especie con identificador = ident al parámetro implícito
      \post retorna la especie con identificador = ident
  */
  Especie consultar_especie(const string &ident) const;

  /** @brief Consultora de la distancia que hay entre dos especies que tiene como identificadores ident1 y ident2, respectivamente.
      \pre existen una especie con identificador = ident1 y otra con identificador = ident2 al parámetro implícito
      \post retorna la distancia que hay entre la especie con identificador = ident1 y la especie con identificador = ident2 mediante un entero
  */
  double busca_distancias(const string& ident1, const string& ident2) const;

  /** @brief Inicializa el conjunto de clústers, es decir, le pasa las especies del parámetro implícito junto con sus respectivas distancias.
      \pre <em>cierto</em>
      \post inicializa el conjunto de clústers con el conjunto de especies del parámetro implícito
  */
  void inicializa_conjunto_clusters(Cjt_clusters &Cjt_c) const;

  //Lectura y escriptura

  /** @brief Operación de lectura.
      \pre hay preparado en el canal de entrada un conjunto de especies
      \post el parámetro implícito contiene el conjunto de especies leídos del canal de entrada
  */
  void lee_cjt_especies();

  /** @brief Operación de escritura de la tabla de distancias del conjunto de especies.
      \pre <em>cierto</em>
      \post imprime por el canal de salida la tabla de distancias del parámetro implícito
  */
  void imprime_tabla_distancias() const;

  /** @brief Operación de escritura del conjunto de especies.
      \pre <em>cierto</em>
      \post se han escrito por el canal de salida las especies del parámetro implícito en orden alfabético de los identificadores de las especies
  */
  void imprime_cjt_especies() const;

private:

  /* Un conjunto de especies se almacenará mediante la estructura map(diccionario), que ordena sus elementos según su llave, que en este caso es el identificador de una especie(string), y en orden creciente.
     El conjunto de las distancias que hay entre las especies también se guarda mediante la estructura map */

  /** @brief un número natural que es usado para el cálculo de la distancia entre dos especies. */
  int k;

  /** @brief Estructura del conjunto de especies, guardado en un diccionario, es decir, ordenados por orden creciente según su llave. */
  map<string, pair<Especie, map <string, double> > > es;

  /** @brief Estructura del conjunto de distancias, guardado en un diccionario, es decir, ordenados por orden creciente según su llave. */
  map<string, map<string, double> > dis;

  /** @brief Consulta los k-mers del gen de la especie, que será utilizado para el cálculo de la distancia.
      \pre gen contiene al menos un carácter
      \post kmer contiene los k-mers de gen
  */
  void consultar_kmers(const string &gen, map<string, double>& kmer);

  /** @brief Calcula la distancia que hay entre dos especies.
      \pre existen en el parámetro implícito la especie que tiene como identificador = identificador1 y la especie que tiene como identificador = identificador2
      \post el resultado es un número real que indica la distancia que hay entre estas dos especies
  */
  double distancia(string identificador1, string identificador2);
};
#endif
