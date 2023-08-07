/** @file Cjt_especie.hh
    @brief Especificación de la clase Cjt_especie
*/

#ifndef _CJT_ESPECIE_HH_
#define _CJT_ESPECIE_HH_

#include "Especie.hh"

#ifndef NO_DIAGRAM
#include <map>
#endif

/** @class Cjt_especie
    @brief Representa a un conjunto de especies

    Contiene a un conjunto de especies con diferentes características almacenadas alfabéticamente por su identificador
*/

class Cjt_especie {
public:
  //Constructoras

  /** @brief Creadora por defecto.

      Se ejecuta automáticamente al declarar a un conjunto de Especies.
      \pre <em>cierto</em>
      \post El resultado es un conjunto de especies vacío
  */
  Cjt_especie();

  //Modificadoras

  /** @brief Añade al conjunto de Especies una nueva especie.

      \pre <em>cierto</em>
      \post se añade al parámetro implícito un nuevo elemento, formado por el pair (identificador de esp, esp)
  */
  void adderir_especie(const Especie &esp);

  /** @brief Elimina del conjunto de especies una especie.

      Permite eliminar una Especie del conjunto de especies.
      \pre Dado el identificador de una especie en el canal de entrada estándard, existe una especie con este identificador en el conjunto implícito
      \post Se elimina del parámetro implícito la especie que tiene como identificador el parámetro de entrada
  */
  void elimina_especie(string identificador);

  /** @brief Modifica el valor de la k
      \pre dado un natural
      \post sustituye el valor antiguo de k por n
  */
  void lee_k(int n);

  //Consultoras

  /** @brief Operación consultora.

      \pre <em>cierto</em>
      \post el resultado indica si el parámetro implícito es vacío o no
  */
  bool empty() const;

  /** @brief Hace una consulta sobre la existencia de una especie dentro del parámetro implícito
      \pre <em>cierto</em>
      \post el resultado indica si existe una especie en el parámetro implícito con identificador el parámetro de entrada
  */
  bool existe_especie(string identificador) const;

  /** @brief Consulta el parámetro implícito
      \pre <em>cierto</em>
      \post el resulta retorna un conjunto formado por las especies que hay en ese momento en el conjunto de especies
  */
  map<string, Especie> consultar_conjunto() const;

  /** @brief Obtener la especie que tiene como identificador el parámetro de entrada
      \pre dentro del parámetro de entrada existe un elemento que se referencia por el parámetro de entrada
      \post retorna la especie del parámetro implícito que se identifica por el parámetro de entrada
  */
  Especie consultar_iden(string identificador) const;

  /** @brief Calcula la distancia que hay entre dos especies
      \pre dados dos identificadores
      \post el resultado indica la distancia que hay entre las dos especies que se referencian con los parámetros de entrada
  */
  double distancia(string identificador1, string identificador2);

  /** @brief Calcula la tabla de distancias que hay entre las especies del parámetro implícito
      \pre <em>cierto</em>
      \post calcula la tabla de distancias entre las distintas especies
  */
  map<string, map<string, double> > tabla_distancias();

  //Lectura y escriptura

  /** @brief Operación de escritura.
      \pre <em>cierto</em>
      \post imprime al canal de salida la tabla de distancias
  */
  void imprime_tabla_distancias(const map<string, map<string, double> > &dis);

  /** @brief Operación de lectura.
      \pre <em>cierto</em>
      \post el parámetro implícito contiene el conjunto de n especies leídos del canal de entrada
  */
  void lee_cjt_especies();

  /** @brief Operación de escritura.
      \pre <em>cierto</em>
      \post se han escrito por el canal de salida las especies del parámetro implícito en orden alfabético de los identificadores de las especies
  */
  void imprime_cjt_especies() const;

private:

  /* Un conjunto de especies se almacenará mediante la estructura map(diccionario), que ordena sus elementos seguún su llave, que en este caso es el identificador de una especie(string), y en orden alfabético */

  /** @brief un número natural que es usado para el cálculo de la distancia entre dos especies */
  int k;
  /** @brief Estructura del conjunto de especies, guardado en un diccionario, es decir, ordenados por orden alfabético */
  map<string, Especie> es;
  /** @brief Operación que busa una especie.
      \pre dado el identificador de una especie
      \post devuele la especie que tiene como identificador el parámetro de entrada
  */
  Especie buscar_especie(string identificador) const;
  /** @brief un número entero que representa el cardinal de la unión de dos vectores de kmeros de 2 especies diferentes (usado para el cálculo de la distancia de estas dos especies) */
  double ntotal;
  /** @brief un número entero que representa el cardinal de la intersección de dos vectores de kmeros de 2 especies diferentes (usado para el cálculo de la distancia de estas dos especies) */
  double ncoincidente;
  /** @brief Operación que calcula los valores del ntotal y del ncoincidente.
      \pre dados dos strings que representan los identificadores de dos especies
      \post modifica los valores de ntotal y ncoincidente por el cardinal de unión de los genes de las dos especies y el cardinal de intersección de los genes de las dos especies, respectivamente
  */
  void numero_kmer_totales(string identificador1, string identificador2);
};
#endif
