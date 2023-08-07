/** @file cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

Cluster::Cluster()
  /* pre <em>cierto</em> */
  /* post el resultado es un cluster vacío, sin identificador y con dist = 0 */
{
  distancia = 0;
}

Cluster::Cluster(const string &ident)
  /* pre hay preparado un string en el canál estándard de entrada, que tiene almenos un carácter */
  /* post el resultado es un clúster con identificador = ident y distancia = 0 */
{
  this->identificador = ident;
  distancia = 0;
}

Cluster::Cluster(const string &ident, const double &dis)
  /* pre hay preparado un string en el canál estándard de entrada, que tiene almenos un carácter y un entero dis */
  /* post el resultado es un cluster con identificador = ident y distancia = dis */
{
  this->identificador = ident;
  distancia = dis;
}

string Cluster::consultar_identificador() const
  /* pre <em>cierto</em> */
  /* post el resultado es el identificador del parámetro implícito */
{
  return identificador;
}

double Cluster::consultar_dist() const
  /* pre <em>cierto</em> */
  /* post el resultado es la distancia del parámetro implícito */
{
  return distancia;
}
