/** @file Especie.cc
    @brief Código de la clase Especie
*/

#include "Especie.hh"

Especie::Especie()
  /* pre <em>cierto</em> */
  /* post el resultado es una especie vacío */
{
  te_identificador = false;
  te_gen = false;
}

Especie::Especie(string identificador, string gen)
  /* pre hay preparados dos string en el canál estándard de entrada */
  /* post el resultado es una especie con identificador "identificador" y gen "gen" */
{
  te_identificador = true;
  te_gen = true;
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

vector<string> Especie::consultar_kmers(string gen, int k) const
  /* pre dado una gen que pertenece al parámetro implícito y un natural */
  /* post retorna un vector que contiene los kmers del gen de la especie */
{
  int size = gen.size() - k + 1;
  vector<string> kmer(size);
  for (int i = 0; i < size; ++i) {
    string aux;
    int p = i;
    while (p < k) {
      char car = gen[p];
      aux.push_back(car);
      ++p;
    }
    kmer[i] = aux;
    ++k;
  }
  sort(kmer.begin(), kmer.end());
  return kmer;
}

void Especie::leer_especie()
  /* pre estan preparados en el canal de entrada dos strings */
  /* post el parámetro implícito pasa a tener los atributos leídos del canal estándard de entrada */
{
  if (cin >> identificador >> gen) {
    te_gen = true;
    te_identificador = true;
  }
}

void Especie::imprimir_especie() const
  /* pre <em>cierto</em> */
  /* post se han escrito los atributos del parámetro implícito al canal estándard de salida: el identificador de la especie seguido de un espacio y seguido del gen de la especie */
{
  if (te_identificador and te_gen) cout << this->identificador << " " << this->gen << endl;
}
