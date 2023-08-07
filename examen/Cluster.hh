/** @file cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_


#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#endif

/** @class Cluster
    @brief Representa el conjunto de características y operaciones un clúster.

    Ofrece operaciones consultoras, de lectura y de escritura de un clúster.
*/

class Cluster{
public:
  //Constructoras

  /** @brief Creadora por defecto.

      \pre <em>cierto</em>
      \post el resultado es un clúster vacío, sin identificador y con distancia = 0
  */
  Cluster();

  /** @brief Creadora copiadora.

      \pre hay preparado un string en el canál estándard de entrada, que tiene almenos un carácter
      \post el resultado es un cluster con identificador = ident y distancia = 0
  */
  Cluster(const string &ident);

  /** @brief Creadora copiadora.

      \pre hay preparado un string en el canál estándard de entrada, que tiene almenos un carácter y un entero dis
      \post el resultado es un cluster con identificador = ident y distancia = dis
  */
  Cluster(const string &ident, const double &dis);


  //Consultoras

  /** @brief Consultora del identificador del parámetro implícito.

      \pre <em>cierto</em>
      \post el resultado es el identificador del parámetro implícito
  */
  string consultar_identificador() const;

  /** @brief Consultaora de la distancia del parámetro implícito.

      \pre <em>cierto</em>
      \post el resultado es la distancia del parámetro implícito
  */
  double consultar_dist() const;

private:

  /* Un clúster se caracteriza por un identificador(string) y  una distancia(double). */

  /** @brief Identificador del clúster. */
  string identificador;

  /** @brief Distancia del clúster. */
  double distancia;
};
#endif
