/** @file cluster.cc
    @brief Código de la clase clúster
*/

#include "Cluster.hh"

Cluster::Cluster()
  /* pre <em>cierto</em> */
  /* post el resultado es un cluster vacío */
{
  cluster = BinTree<string>();
}

Cluster::Cluster(string identificador)
  /* pre hay preparado un string en el canál estándard de entrada */
  /* post se crea un nuevo clúster que tiene identificador como raíz, y sus hijos derecho y izquierdo son vacíos */
{
  cluster = BinTree<string>(identificador);
}

Cluster::Cluster(string identificador, Cluster a, Cluster b)
  /* pre hay preparados dos clústers y un identificador en el canal de entrada */
  /* crea un nuevo clúster  que tiene como raíz el identificador, y como hijo izquierdo y hijo derecho los clústers a y b, respectivamente */
{
  BinTree<string> aux = a.consultar_arbol();
  BinTree<string> aux2 = b.consultar_arbol();
  BinTree<string> aux3(identificador, aux, aux2);
  cluster = aux3;
}

string Cluster::value() const
  /* pre <em>cierto</em> */
  /* post retorna la raíz del parámetro implícito */
{
  return cluster.value();
}

bool Cluster::empty() const
  /* pre <em>cierto</em> */
  /* post el resultado indica si el parámetro implícito es vacío o no */
{
  return cluster.empty();
}

BinTree<string> Cluster::consultar_arbol() const
  /* pre <em>cierto</em> */
  /* post retorna la estructura arbolescente del parámetro implícito */
{
  return cluster;
}
