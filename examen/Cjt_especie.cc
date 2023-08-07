/** @file Cjt_especie.cc
    @brief Código de la clase Cjt_especie.hh
*/

#include "Cjt_especie.hh"
#define _USE_MATH_DEFINES
#include <cmath>

Cjt_especie::Cjt_especie()
  /* pre <em>cierto</em> */
  /* post El resultado es un conjunto de especies vacío */
{
  cin >> k;
  es.clear();
}

void Cjt_especie::adderir_especie(const Especie &esp)
  /* pre el parámetro implícito no contiene ninguna especie con el identificador de esp, ni tampoco un elemento de dis que se identifique con el identificador de esp */
  /* post se añade la especie esp al parámetro implícito y se añade también a dis junto con nuevos valores de distancia */
{
  string identificador = esp.consultar_identificador();
  string gen = esp.consultar_gen();
  map<string, double> k1;
  consultar_kmers(gen, k1);
  es.insert(make_pair(identificador, make_pair(esp, k1)));
  map<string, map<string, double> >::iterator it;
  map<string, double> aux;
  it = dis.begin();
  while (it != dis.end() and it->first < identificador) {
    it->second.insert(make_pair(identificador, distancia(identificador, it->first)));
    ++it;
  }
  while (it != dis.end()) {
    aux.insert(make_pair(it->first, distancia(identificador, it->first)));
    ++it;
  }
  dis.insert(make_pair(identificador, aux));
}

void Cjt_especie::elimina_especie(const string &ident)
  /* pre existe una especie al parámetro implícito con identificador = ident, existe un elemento de dis que se identifica por ident */
  /* post el parámetro implícito contiene las mismas especies que el original menos la especie con identificador = ident, dis contiene los mismos elementos que el original menos el elemento que se identifica por ident */
{
  es.erase(ident);
  map<string, map<string, double> >::iterator it, ot;
  map<string, double>::const_iterator ut;
  it = dis.find(ident);
  for (ot = dis.begin(); ot != it; ++ot) {
    ut = ot->second.find(ident);
    ot->second.erase(ut);
  }
  dis.erase(it);
}

void Cjt_especie::tabla_distancias()
  /* pre <em>cierto</em> */
  /* post calcula la tabla de distancias entre las especies que hay formados en el conjunto de especies del parámetro implícito */
{
  dis.clear();
  map<string, double> auxiliar;
  map<string, pair<Especie, map<string, double> > >::const_iterator it, j;
  for (it = es.begin(); it != es.end(); ++it) {
    j = it;
    ++j;
    while (j != es.end()) {
      auxiliar.insert(make_pair(j->first, distancia(j->first, it->first)));
      ++j;
    }
    dis.insert(make_pair(it->first, auxiliar));
    auxiliar.clear();
  }
}

bool Cjt_especie::empty() const
  /* pre <em>cierto</em> */
  /* post el resultado indica si el parámetro implícito es vacío o no */
{
  return (es.size() == 0);
}

bool Cjt_especie::existe_especie(const string &ident) const
  /* pre <em>cierto</em> */
  /* post el resultado indica si existe una especie en el parámetro implícito con identificador = ident */
{
  map<string, pair<Especie, map<string, double> > >::const_iterator it = es.find(ident);
  if (it == es.end()) return false;
  return true;
}

Especie Cjt_especie::consultar_especie(const string &ident) const
  /* pre existe una especie con identificador = ident al parámetro implícito */
  /* post retorna la especie con identificador = ident */
{
  map<string, pair<Especie, map<string, double> > >::const_iterator it = es.find(ident);
  return it->second.first;
}

double Cjt_especie::busca_distancias(const string& identificador, const string& ident) const
  /* pre existen una especie con identificador = ident1 y otra con identificador = ident2 al parámetro implícito */
  /* post retorna la distancia que hay entre la especie con identificador = ident1 y la especie con identificador = ident2 mediante un entero */
{
  map<string, map<string, double> >::const_iterator it;
  map<string, double>::const_iterator ot;
  if (identificador < ident) {
    it = dis.find(identificador);
    ot = it->second.find(ident);
    return ot->second;
  }
  else {
    it = dis.find(ident);
    ot = it->second.find(identificador);
    return ot->second;
  }
}

void Cjt_especie::inicializa_conjunto_clusters(Cjt_clusters &Cjt_c) const
  /* pre <em>cierto</em> */
  /* post inicializa el conjunto de clústers con el conjunto de especies del parámetro implícito */
{
  Cjt_c.inicializa();
  map<string, map<string, double> >::const_iterator it;
  map<string, double>::const_iterator ut;
  for (it = dis.begin(); it != dis.end(); ++it) {
    Cjt_c.adderir_cluster(it->first);
    for (ut = it->second.begin(); ut != it->second.end(); ++ut) {
      Cjt_c.distancias_clusters(it->first, ut->first, ut->second);
    }
  }
  Cjt_c.ordenar_distancias();
}

void Cjt_especie::lee_cjt_especies()
  /* pre hay preparado en el canal de entrada un conjunto de especies */
  /* post el parámetro implícito contiene el conjunto de especies leídos del canal de entrada */
{
  es.clear();
  int n;
  cin >> n;
  map<string, double> aux2;
  for (int i = 0; i < n; ++i) {
    Especie aux;
    aux.leer_especie();
    string gen = aux.consultar_gen();
    consultar_kmers(gen, aux2);
    es.insert(make_pair(aux.consultar_identificador(), make_pair(aux, aux2)));
    aux2.clear();
  }
}

void Cjt_especie::imprime_tabla_distancias() const
  /* pre <em>cierto</em> */
  /* post imprime por el canal de salida la tabla de distancias del parámetro implícito */
{
  if (dis.size() > 0) {
    map<string, map<string, double> >::const_iterator it;
    map<string, double>::const_iterator ot;
    for (it = dis.begin(); it != dis.end(); ++it) {
      cout << it->first << ":";
      ot = it->second.begin();
      while (ot != it->second.end()) {
        cout << " " << ot->first << " (" << ot->second << ")";
        ++ot;
      }
      cout << endl;
    }
  }
}

void Cjt_especie::imprime_cjt_especies() const
  /* pre <em>cierto</em> */
  /* post se han escrito por el canal de salida las especies del parámetro implícito en orden alfabético de los identificadores de las especies */
{
  map<string, pair<Especie, map <string, double> > >::const_iterator it;
  it = es.begin();
  while (it != es.end()) {
    it->second.first.imprimir_especie();
    ++it;
  }
}

void Cjt_especie::consultar_kmers(const string &gen, map<string, double>& kmer)
  /* pre gen contiene al menos un carácter */
  /* post kmer contiene los k-mers de gen */
{
  map<string, double>::const_iterator it;
  string anterior;
  int i = gen.size() - k + 1;
  while (i < gen.size() + 1) {
    char c = gen[i];
    anterior.push_back(c);
    ++i;
  }
  for (int i = (gen.size() - k); i >= 0 ; --i) {
    string posterior;
    anterior.pop_back();
    posterior = anterior;
    char c = gen[i];
    anterior = c + posterior;
    it = kmer.find(anterior);
    if (it != kmer.end()) {
      kmer[anterior] = it->second + 1;
    }
    else {
      kmer.insert(make_pair(anterior, 1));
    }
  }
}

double Cjt_especie::distancia(string identificador1, string identificador2)
  /* pre existen en el parámetro implícito la especie que tiene como identificador = identificador1 y la especie que tiene como identificador = identificador2 */
  /* post el resultado es un número real que indica la distancia que hay entre estas dos especies */
{
  double modulo2 = 0;
  double modulo1 = 0;
  double producto = 0;
  map<string, pair<Especie, map <string, double> > >::iterator at, et;
  at = es.find(identificador1);
  et = es.find(identificador2);
  map<string, double>::const_iterator it, ot;
  it = at->second.second.begin();
  ot = et->second.second.begin();
  while (it != at->second.second.end() and ot != et->second.second.end()) {
    if (it->first == ot->first) {
      producto += (it->second * ot->second);
      modulo1 += (it->second * it->second);
      modulo2 += (ot->second * ot->second);
      ++it;
      ++ot;
    }
    else if (it->first < ot->first) {
      modulo1 += (it->second * it->second);
      ++it;
    }
    else {
      modulo2 += (ot->second * ot->second);
      ++ot;
    }
  }
  while (it != at->second.second.end()) {
    modulo1 += (it->second * it->second);
    ++it;
  }
  while (ot != et->second.second.end()) {
    modulo2 += (ot->second * ot->second);
    ++ot;
  }
  double uno = sqrt(modulo1);
  double dos = sqrt(modulo2);
  double distancc = (producto/(uno*dos));
  double distancee = acos(distancc);
  return (1 - (M_1_PI*distancee)) * 100;
}
