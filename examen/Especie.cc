/** @file Especie.cc
    @brief Código de la clase Especie
*/

#include "Especie.hh"

Especie::Especie()
  /* pre <em>cierto</em> */
  /* post el resultado es una especie vacío, sin identificador ni gen */
{

}

Especie::Especie(const string &identificador, const string &gen)
  /* pre identificador y gen contienen al menos un carácter */
  /* post el resultado es una especie con identificador "identificador" y gen "gen" */
{
  this->identificador = identificador;
  this->gen = gen;
}

string Especie::consultar_identificador() const
  /* pre el parámetro implícito tiene identificador */
  /* post el resultado es el identificador del parámetro implícito */
{
  return identificador;
}

string Especie::consultar_gen() const
  /* pre el parámetro implícito tiene gen */
  /* post el resultado es el gen del parámetro implícito */
{
  return gen;
}

void Especie::leer_especie()
  /* pre estan preparados en el canal de entrada dos strings */
  /* post el parámetro implícito pasa a tener los atributos leídos del canal estándard de entrada */
{
  cin >> identificador >> gen;
}

void Especie::imprimir_especie() const
  /* pre <em>cierto</em> */
  /* post post se han escrito los atributos del parámetro implícito por el canal estándard de salida: el identificador de la especie seguido de un espacio y seguido del gen de la especie */
{
  cout << this->identificador << " " << this->gen << endl;
}
