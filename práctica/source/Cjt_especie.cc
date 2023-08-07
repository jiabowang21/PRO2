/** @file Cjt_especie.cc
    @brief Código de la clase conjunto Especie
*/

#include "Cjt_especie.hh"

Cjt_especie::Cjt_especie()
  /* pre <em>cierto</em> */
  /* post El resultado es un conjunto de especies vacío */
{
  es.clear();
}

void Cjt_especie::adderir_especie(const Especie &esp)
  /* pre <em>cierto</em> */
  /* post se añade al parámetro implícito un nuevo elemento, formado por el pair (identificador de esp, esp) */
{
  es.insert(pair<string, Especie>(esp.consultar_identificador(), esp));
}

void Cjt_especie::elimina_especie(string identificador)
  /* pre Dado el identificador de una especie en el canal de entrada estándard, existe una especie con este identificador en el conjunto implícito */
  /* post Se elimina del parámetro implícito la especie que tiene como identificador el parámetro de entrada */
{
  es.erase(identificador);
}

void Cjt_especie::lee_k(int n)
  /* pre dado un natural */
  /* post asigna el valor de n a k */
{
  k = n;
}

bool Cjt_especie::empty() const
  /* pre <em>cierto</em> */
  /* post el resultado indica si el parámetro implícito es vacío o no */
{
  return (es.size() == 0);
}

bool Cjt_especie::existe_especie(string identificador) const
  /* pre <em>cierto</em> */
  /* post el resultado indica si existe una especie en el parámetro implícito con identificador el parámetro de entrada */
{
  map<string, Especie>::const_iterator it = es.find(identificador);
  if (it == es.end()) return false;
  return true;
}

map<string, Especie> Cjt_especie::consultar_conjunto() const
  /* pre <em>cierto</em> */
  /* post el resulta retorna un conjunto formado por las especies que hay en ese momento en el conjunto de especies */
{
  return es;
}

Especie Cjt_especie::consultar_iden(string identificador) const
  /* pre dentro del parámetro de entrada existe un elemento que se referencia por el parámetro de entrada */
  /* post retorna la especie del parámetro implícito que se identifica por el parámetro de entrada */
{
  return buscar_especie(identificador);
}

double Cjt_especie::distancia(string identificador1, string identificador2)
  /* pre dados dos identificadores */
  /* post el resultado indica la distancia que hay entre las dos especies que se referencian con los parámetros de entrada */
{
  numero_kmer_totales(identificador1, identificador2);
  double d = 1 - (ncoincidente/ntotal);
  d = d*100;
  return d;
}

map<string, map<string, double> > Cjt_especie::tabla_distancias()
  /* pre <em>cierto</em> */
  /* post calcula la tabla de distancias entre las distintas especies */
{
  map<string, map<string, double> > resultado;
  map<string, Especie>::const_iterator it;
  map<string, Especie>::const_iterator j;
  for (it = es.begin(); it != es.end(); ++it) {
    string aux = it->first;
    j = es.begin();
    map<string, double> auxiliar;
    while (j != es.end()) {
      double a = distancia(j->first, aux);
      auxiliar.insert(make_pair(j->first, a));
      ++j;
    }
    resultado.insert(make_pair(aux, auxiliar));
  }
  return resultado;
}

void Cjt_especie::imprime_tabla_distancias(const map<string, map<string, double> > &dis)
  /* pre <em>cierto</em> */
  /* post imprime al canal de salida la tabla de distancias */
{
  if (dis.size() > 0) {
    map<string, map<string, double> >::const_iterator it = dis.begin();
    map<string, double>::const_iterator ot = it->second.begin();
    for (it = dis.begin(); it != dis.end(); ++it) {
      cout << it->first << ":";
      ot = it->second.find(it->first);
      ++ot;
      while (ot != it->second.end()) {
        cout << " " << ot->first << " (" << ot->second << ")";
        ++ot;
      }
      cout << endl;
    }
  }
}

void Cjt_especie::lee_cjt_especies()
  /* pre <em>cierto</em> */
  /* post el parámetro implícito contiene el conjunto de n especies leídos del canal de entrada */
{
  es.clear();
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    Especie aux;
    aux.leer_especie();
    string iden = aux.consultar_identificador();
    es.insert(pair<string, Especie>(iden, aux));
  }
}

void Cjt_especie::imprime_cjt_especies() const
  /* pre <em>cierto</em> */
  /* post se han escrito por el canal de salida las especies del parámetro implícito en orden alfabético de los identificadores de las especies */
{
  map<string, Especie>::const_iterator it;
  it = es.begin();
  while (it != es.end()) {
    Especie aux = it->second;
    aux.imprimir_especie();
    ++it;
  }
}

Especie Cjt_especie::buscar_especie(string identificador) const
  /* pre dado el identificador de una especie */
  /* post devuele la especie que tiene como identificador el parámetro de entrada */
{
  map<string, Especie>::const_iterator it = es.find(identificador);
  return it->second;
}

void Cjt_especie::numero_kmer_totales(string identificador1, string identificador2)
  /* pre dados dos strings que representan los identificadores de dos especies */
  /* post modifica los valores de ntotal y ncoincidente por el cardinal de unión de los genes de las dos especies y el cardinal de intersección de los genes de las dos especies, respectivamente */
{
  Especie especie1 = buscar_especie(identificador1);
  Especie especie2 = buscar_especie(identificador2);
  vector<string> k1 = especie1.consultar_kmers(especie1.consultar_gen(), k);
  vector<string> k2 = especie2.consultar_kmers(especie2.consultar_gen(), k);
  ntotal = 0, ncoincidente = 0;
  for (int i = 0; i < k1.size(); ++i) {
    int n1 = 1, n11 = 0;
    int n2 = 0;
    if (k1[i] != "--") {
      string aux = k1[i];
      int j = 0;
      bool b = false;
      while (j < k2.size()) {
        if (k2[j] == aux) {
          ++n2;
          b = true;
          k2[j] = "--";
        }
        ++j;
      }
      if(b) ++n11;
      for (int l = i + 1; l < k1.size(); ++l) {
        if (k1[l] == aux) {
          ++n1;
          k1[l] = "--";
          if (b) {
            ++n11;
          }
        }
      }
      if (n1 >= n2) ntotal += n1;
      else ntotal += n2;
      if (b) {
        if (n11 <= n2) ncoincidente += n11;
        else ncoincidente += n2;
      }
    }
  }
  for (int s = 0; s < k2.size(); ++s) {
    if (k2[s] != "--") ++ntotal;
  }
}
