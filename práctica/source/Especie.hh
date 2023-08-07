/** @file Especie.hh
    @brief Especificación de la clase Especie
*/

#ifndef _ESPECIE_HH_
#define _ESPECIE_HH_

#ifndef NO_DIAGRAM
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#endif

/** @class Especie
    @brief Representa a una especie.

    Caracteriza a una especie según su identificador, un string, y su gen, otro string
*/
class Especie {

public:
  //Constructoras

  /** @brief Creadora por defecto.

      Se ejecuta automáticamente al declarar una especie.
      \pre <em>cierto</em>
      \post el resultado es una especie vacío
  */
  Especie();

  /** @brief Creadora copiadora.

      Permite declarar una especie con sus características, identificador y gen respectivamente.
      \pre hay preparados dos string en el canál estándard de entrada
      \post el resultado es una especie con identificador "identificador" y gen "gen"
  */
  Especie(string identificador, string gen);

  //Consultoras

  /** @brief Consulta el identificador de una especie.
      \pre el parámetro implícito tiene identificador
      \post el resultado es el identificador del parámetro implícito
  */
  string consultar_identificador() const;

  /** @brief Consulta el gen de una Especie.
      \pre el parámetro implícito tiene gen
      \post el resultado es el gen del parámetro implícito
  */
  string consultar_gen() const;

  /** @brief Consulta los kmers del gen de la especie.
      \pre dado una gen que pertenece al parámetro implícito y un natural
      \post retorna un vector que contiene los kmers del gen de la especie
  */
  vector<string> consultar_kmers(string gen, int k) const;

  //Lectura y escriptura

  /** @brief Operación de lectura.
      \pre estan preparados en el canal de entrada dos strings
      \post el parámetro implícito pasa a tener los atributos leídos del canal estándard de entrada
  */
  void leer_especie();

  /** @brief Operación de escritura.
      \pre <em>cierto</em>
      \post post se han escrito los atributos del parámetro implícito al canal estándard de salida: el identificador de la especie seguido de un espacio y seguido del gen de la especie
  */
  void imprimir_especie() const;

private:

  /* Una especie se representa mediante su identificador y su gen */

  /** @brief Identificador de la especie */
  string identificador;
  /** @brief Indica si especie tiene identificador(true) o no(false) */
  bool te_identificador;
  /** @brief Gen de la especie */
  string gen;
  /** @brief Indica si la especie tiene gen(true) o no(false) */
  bool te_gen;
};
#endif
