/** @file Especie.hh
    @brief Especificación de la clase Especie
*/

#ifndef _ESPECIE_HH_
#define _ESPECIE_HH_

#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

/** @class Especie
    @brief Representa el conjunto de características y operaciones una especie.

    Sus operaciones permite crear, modificar y consultar una especie.
*/
class Especie {

public:
  //Constructoras

  /** @brief Creadora por defecto.

      \pre <em>cierto</em>
      \post el resultado es una especie vacío, sin identificador ni gen
  */
  Especie();

  /** @brief Creadora copiadora.

      \pre identificador y gen contienen al menos un carácter
      \post el resultado es una especie con identificador "identificador" y gen "gen"
  */
  Especie(const string &identificador, const string &gen);

  //Consultoras

  /** @brief Consultora del identificador de una especie.
      \pre el parámetro implícito tiene identificador
      \post el resultado es el identificador del parámetro implícito
  */
  string consultar_identificador() const;

  /** @brief Consultora del gen de una especie.
      \pre el parámetro implícito tiene gen
      \post el resultado es el gen del parámetro implícito
  */
  string consultar_gen() const;

  //Lectura y escriptura

  /** @brief Operación de lectura.
      \pre estan preparados en el canal de entrada dos strings
      \post el parámetro implícito pasa a tener los atributos leídos del canal estándard de entrada
  */
  void leer_especie();

  /** @brief Operación de escritura de la especie.
      \pre <em>cierto</em>
      \post post se han escrito los atributos del parámetro implícito por el canal estándard de salida: el identificador de la especie seguido de un espacio y seguido del gen de la especie
  */
  void imprimir_especie() const;

private:

  /* Una especie se representa mediante un identificador y un gen. */

  /** @brief Identificador de la especie. */
  string identificador;

  /** @brief Gen de la especie. */
  string gen;
};
#endif
