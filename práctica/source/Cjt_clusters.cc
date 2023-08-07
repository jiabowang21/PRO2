/** @file Cjt_clusters.cc
    @brief Código de la clase conjunto de clústers
*/

#include "Cjt_clusters.hh"

Cjt_clusters::Cjt_clusters()
  /* pre <em>cierto</em> */
  /* post El resultado es un conjunto de clústers vacío */
{
  clu.clear();
}

void Cjt_clusters::inicializa_clusters(map<string, Especie> esp)
  /* pre dado un conjunto de especies */
  /* post inicializa el parámetro implícito, es decir, almacena el parámetro de entrada al conjunto implícito y imprime la tabla de distancias del conjunto de clústers */
{
  clu.clear();
  map<string, Especie>::const_iterator it;
  for (it = esp.begin(); it != esp.end(); ++it) {
    Cluster aux(it->first);
    clu.insert(make_pair(it->first, aux));
  }
}

void Cjt_clusters::actualiza_tabla_distancias(map<string, map<string, double> >& distance)
  /* pre dado la tabla de distancias */
  /* post actualiza la tabla con las distancias que hay entre los clústers */
{
  if (distance.size() > 0) {
    Cluster fus;
    fus = fusion_clusters(distance);
    string fusclu = fus.value();
    map<string, double> aux, aux1, aux2;
    map<string, map<string, double> >::iterator it;
    it = distance.find(min1.value());
    aux = it->second;
    it = distance.find(min2.value());
    aux1 = it->second;
    distance.erase(min1.value());
    distance.erase(min2.value());
    map<string, double>::iterator it1, it2;
    it1 = aux.begin();
    it2 = aux1.begin();
    while (it1 != aux.end() and it2 != aux1.end()) {
      string p = it1->first;
      double count = (it1->second + it2->second)/2;
      aux2.insert(make_pair(p, count));
      ++it1;
      ++it2;
    }
    aux2.insert(make_pair(fusclu, 0));
    distance.insert(make_pair(fusclu, aux2));
    for (it = distance.begin(); it != distance.end(); ++it) {
      map<string, double>::iterator ot;
      bool b = (it->first == fusclu);
      ot = it->second.begin();
      while (ot != it->second.end()) {
        if (ot->first == min1.value()) {
          ot = it->second.erase(ot);
        }
        else if (ot->first == min2.value()) {
          ot = it->second.erase(ot);
        }
        else {
          if (not b) {
            map<string, double>::const_iterator ut;
            ut = aux2.find(it->first);
            double c = ut->second;
            it->second.insert(make_pair(fusclu, c));
          }
          ++ot;
        }
      }
    }
  }
}

Cluster Cjt_clusters::fusion_clusters(const map<string, map<string, double> > &distance)
  /* pre dado la tabla de distancias enter los clústers */
  /* post crea uno clúster nuevo a base de la fusión de los dos clústers que están a menor distancia */
{
  clusters_a_distancia_mas_corta(distance);
  string aux = min1.value();
  string aux2 = min2.value();
  string f;
  Cluster fusion;
  if (aux < aux2) {
    f = aux + aux2;
    Cluster fusion(f, min1, min2);
    clu.erase(aux);
    clu.erase(aux2);
    clu.insert(make_pair(f, fusion));
    distancias_clusters.insert(make_pair(f, dist));
    return fusion;
  }
  else {
    f = aux2 + aux;
    Cluster fusion(f, min2, min1);
    clu.erase(aux);
    clu.erase(aux2);
    clu.insert(make_pair(f, fusion));
    distancias_clusters.insert(make_pair(f, dist));
    return fusion;
  }
}

bool Cjt_clusters::existe_cluster(string identificador) const
  /* pre <em>cierto</em> */
  /* post el resultado indica si en el parámetro implícito existe un clúster que tiene como identificador el parámetro de entrada */
{
  map<string, Cluster>::const_iterator it = clu.find(identificador);
  if (it == clu.end()) return false;
  return true;
}

int Cjt_clusters::size() const
  /* pre <em>cierto</em> */
  /* post el resultado indica el número de elementos del conjunto implícito */
{
  return clu.size();
}

Cluster Cjt_clusters::buscar_cluster(string identificador) const
  /* pre dado el identificador de un clúster */
  /* post devuele el clúster que tiene como identificador el parámetro de entrada */
{
  map<string, Cluster>::const_iterator it = clu.find(identificador);
  return it->second;
}

Cluster Cjt_clusters::arbol_filogenetico ()
  /* pre solo hay un elemento en el parámetro implícito */
  /* post retorna el clúster que representa al árbol filogenetico resultante de aplicar el algoritmo WPGMA al parámetro implícito */
{
  map<string, Cluster>::const_iterator it = clu.begin();
  return it->second;
}

void Cjt_clusters::imprime_cluster(BinTree<string>& c) const
  /* pre dado el identificador de un clúster */
  /* post se escribe por el canal estándard de salida el clúster del parámetro implícito que tiene como identificador el parámetro de entrada */
{
  if (c.left().empty() and c.right().empty()) cout << "[" << c.value() << "]";
  else {
    map<string, double>::const_iterator it;
    it = distancias_clusters.find(c.value());
    cout << "[(" << c.value() << ", " << it->second << ") ";
    BinTree<string> aux1 = c.left();
    BinTree<string> aux2 = c.right();
    imprime_cluster(aux1);
    imprime_cluster(aux2);
    cout << "]";
  }
}

void Cjt_clusters::clusters_a_distancia_mas_corta(const map<string, map<string, double> > &distance)
  /* pre <em>cierto</em> */
  /* post modifica los valores de min1 y min2 por los clústers que están a distancia más pequeña */
{
  map<string, map<string, double> >::const_iterator it;
  map<string, double>::const_iterator ot;
  bool b = true;
  bool p = true;
  for (it = distance.begin(); it != distance.end(); ++it) {
    Cluster aux = buscar_cluster(it->first);
    if (b) {
      min1 = aux;
      b = false;
    }
    for (ot = it->second.begin(); ot != it->second.end(); ++ot) {
      if (it->first != ot->first) {
        Cluster aux2 = buscar_cluster(ot->first);
        if (not b and p) {
          min2 = aux2;
          dist = ot->second;
          p = false;
        }
        else if (not b and not p) {
          if (ot->second < dist) {
            dist = ot->second;
            min1 = aux;
            min2 = aux2;
          }
        }
      }
    }
  }
  dist /= 2;
}
