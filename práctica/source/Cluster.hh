/** @file cluster.hh
    @brief Especificación de la clase cluster
*/

#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

#include "Cjt_especie.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif

/** @class Cluster
    @brief Representa a un clúster, que tiene estructura arbolescente.
*/

class Cluster{
public:
  //Constructoras

  /** @brief Creadora por defecto.

      Se ejecuta automáticamente al declarar un cluster.
      \pre <em>cierto</em>
      \post el resultado es un cluster vacío
  */
  Cluster();

  /** @brief Creadora copiadora.

      Permite declarar un clúster con un identificador.
      \pre hay preparado un string en el canál estándard de entrada
      \post se crea un nuevo clúster que tiene identificador como raíz, y sus hijos derecho y izquierdo son vacíos
  */
  Cluster(string identificador);

  /** @brief Creadora copiadora.

      Permite declarar un clúster con ciertas características
      \pre hay preparados dos clústers y un identificador en el canal de entrada
      \post crea un nuevo clúster  que tiene como raíz el identificador, y como hijo izquierdo y hijo derecho los clústers a y b, respectivamente
  */
  Cluster(string identificador, Cluster a, Cluster b);

  //Consultoras

  /** @brief Consulta el elemento raíz.

      \pre <em>cierto</em>
      \post retorna la raíz del parámetro implícito
  */
  string value() const;

  /** @brief Operación consultora.

      \pre <em>cierto</em>
      \post el resultado indica si el parámetro implícito es vacío o no
  */
  bool empty() const;

  /** @brief Operación consultora.
      \pre <em>cierto</em>
      \post retorna la estructura arbolescente del parámetro implícito
  */
  BinTree<string> consultar_arbol() const;

private:

  /* Un clúster se caracteriza por un identificador(string) y se representa mediante un árbol*/

  /** @brief Un cluster se almacena en una estructura arbolescente*/
  BinTree<string> cluster;
};
#endif
