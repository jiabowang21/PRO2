/** @file Cjt_clusters.cc
    @brief Código de la clase Cjt_clusters.hh
*/

#include "Cjt_clusters.hh"

Cjt_clusters::Cjt_clusters()
  /* pre <em>cierto</em> */
  /* post El resultado es un conjunto de clústers vacío */
{
  clu.clear();
}

void Cjt_clusters::inicializa()
  /* pre <em>cierto</em> */
  /* post se limpia el parámetro implícito, es decir, se vacia el conjunto de clústers que tenia el parámetro implícito y sus respectivas distancias, el parámetro implícito pasa a ser un conjunto de clústers vacío */
{
  distance.clear();
  clu.clear();
}

void Cjt_clusters::adderir_cluster(const string &ident)
  /* pre dado un conjunto de especies */
  /* post inicializa el parámetro implícito, es decir, almacena el parámetro de entrada al conjunto implícito y imprime la tabla de distancias del conjunto de clústers */
{
  Cluster aux(ident);
  BinTree<Cluster> aux2(aux);
  cardinal.insert(make_pair(ident, 1));
  clu.insert(make_pair(ident, aux2));
}

void Cjt_clusters::distancias_clusters(const string &ident, const string &ident2, const double &n)
  /* pre existen los dos clústers con identificador = ident y identificador = ident2 en el parámetro implícito, n = distancia entre estos dos clústers */
  /* post se añade n al parámetro implícito como distancia entre los clústers referenciados como ident y ident2 */
{
  dis.insert(make_pair(make_pair(ident, ident2), n));
}

void Cjt_clusters::ordenar_distancias()
  /* pre <em>cierto</em> */
  /* post se agrupan y se ordenan de forma creciente según el identificador de un clúster las distancias que hay entre los clústers */
{
  map<string, BinTree<Cluster> >::const_iterator it, ut;
  map<string, double> aux;
  map<pair<string, string>, double>::const_iterator up = dis.begin();
  for (it = clu.begin(); it != clu.end(); ++it) {
    ut = it;
    ++ut;
    while (ut != clu.end()) {
      aux.insert(make_pair(ut->first, up->second));
      ++up;
      ++ut;
    }
    distance.insert(make_pair(it->first, aux));
    aux.clear();
  }
  dis.clear();
}

void Cjt_clusters::ejecuta_paso_wpgma()
  /* pre el parámetro implícito contiene al menos dos clústers y los clústers junto con sus distancias están ordenadas crecientemente */
  /* post se añade un clúster formado por los dos clústers a menor distancia y se elimina esos dos clústers, y se actualizan las distancias (la distancia de los clústers que no se han modificado al nuevo clúster será la suma de la distancia que tenia con dos clústers eliminados entre dos) */
{
  BinTree<Cluster> fus;
  fusion_clusters(fus);
  string fusclu = fus.value().consultar_identificador();
  string muno = min1.value().consultar_identificador();
  string mudo = min2.value().consultar_identificador();
  map<string, double>::iterator aa, bb;
  aa = cardinal.find(fus.right().value().consultar_identificador());
  bb = cardinal.find(fus.left().value().consultar_identificador());
  clu.erase(muno);
  clu.erase(mudo);
  clu.insert(make_pair(fusclu, fus));
  map<string, double> auxiliar;
  map<string, double>::iterator af, of, uf, ef;
  map<string, map<string, double> >::iterator ap, op, it;
  for (it = distance.begin(); it != distance.end(); ++it) {
    if (it->first != muno and it->first != mudo) {
      af = it->second.find(muno);
      of = it->second.find(mudo);
      if (af != it->second.end() and of != it->second.end()) {
        double fff;
        fff = ((bb->second*af->second) + (aa->second*of->second)) / (aa->second+bb->second);
        it->second.insert(make_pair(fusclu, fff));
        it->second.erase(of);
        it->second.erase(af);
      }
      else if (af == it->second.end() and of == it->second.end()) {
        ap = distance.find(muno);
        uf = ap->second.find(it->first);
        op = distance.find(mudo);
        ef = op->second.find(it->first);
        double fff;
        fff = ((bb->second*uf->second) + (aa->second*ef->second)) / (aa->second+bb->second);
        auxiliar.insert(make_pair(it->first, fff));
      }
      else if (af == it->second.end() and of != it->second.end()){
        ap = distance.find(muno);
        ef = ap->second.find(it->first);
        double fff;
        fff = ((bb->second*ef->second) + (aa->second*of->second)) / (aa->second+bb->second);
        auxiliar.insert(make_pair(it->first,fff));
        it->second.erase(mudo);
      }
      else {
        ap = distance.find(mudo);
        ef = ap->second.find(it->first);
        double fff;
        fff = ((bb->second*ef->second) + (aa->second*af->second)) / (aa->second+bb->second);
        auxiliar.insert(make_pair(it->first, fff));
        it->second.erase(muno);
      }
    }
  }
  distance.insert(make_pair(fusclu, auxiliar));
  distance.erase(min1.value().consultar_identificador());
  distance.erase(min2.value().consultar_identificador());
}

bool Cjt_clusters::existe_cluster(const string &ident) const
  /* pre <em>cierto</em> */
  /* post el resultado indica si existe en el parámetro implícito un clúster con identificador = ident */
{
  map<string, BinTree<Cluster> >::const_iterator it = clu.find(ident);
  if (it == clu.end()) return false;
  return true;
}

int Cjt_clusters::size() const
  /* pre <em>cierto</em> */
  /* post el resultado indica el número de elementos del conjunto de clústers del parámetro implícito */
{
  return clu.size();
}

void Cjt_clusters::imprime_cluster(const string &ident)
  /* pre existe el clúster con identificador = ident dentro del parámetro implícito */
  /* post se imprime por el canal de salida el clúster con identificador = ident junto con sus respectivas distancias */
{
  map<string, BinTree<Cluster> >::const_iterator it = clu.find(ident);
  imprime(it->second);
}

void Cjt_clusters::imprime_arbol()
  /* pre hay únicamente un clúster en el conjunto implícito */
  /* post se imprime por el canal de salida el único clúster del conjunto implícito */
{
  map<string, BinTree<Cluster> >::const_iterator it = clu.begin();
  imprime(it->second);
}

void Cjt_clusters::imprime_tabla_distancias() const
  /* pre <em>cierto</em> */
  /* post imprime por el canal de salida la tabla de distancias del parámetro implícito */
{
  if (distance.size() > 0) {
    map<string, map<string, double> >::const_iterator it;
    map<string, double>::const_iterator ot;
    for (it = distance.begin(); it != distance.end(); ++it) {
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

void Cjt_clusters::fusion_clusters(BinTree<Cluster>& c)
  /* pre <em>cierto</em> */
  /* post crea uno clúster nuevo a base de la fusión de los dos clústers que están a menor distancia (min1, min2) */
{
  clusters_a_distancia_mas_corta();
  string aux = min1.value().consultar_identificador();
  string aux2 = min2.value().consultar_identificador();
  string f;
  map<string, double>::iterator it, ut;
  if (aux < aux2) {
    f = aux + aux2;
    Cluster ff(f, (dist/2));
    BinTree<Cluster> fusion(ff, min1, min2);
    c = fusion;
    it = cardinal.find(aux2);
    ut = cardinal.find(aux);
    cardinal.insert(make_pair(f, it->second + ut->second));
  }
  else {
    f = aux2 + aux;
    Cluster ff(f, (dist/2));
    BinTree<Cluster> fusion(ff, min2, min1);
    c = fusion;
    it = cardinal.find(aux2);
    ut = cardinal.find(aux);
    cardinal.insert(make_pair(f, it->second + ut->second));
  }
}

void Cjt_clusters::clusters_a_distancia_mas_corta()
  /* pre hay al menos dos clústers en el conjunto de clústers */
  /* post calcula los dos clústers a menor distancia y los guarda en los clústers min1 y min2 respectivamente, y a dist la distancia que hay entre estos dos clústers */
{
  map<string, map<string, double> >::const_iterator it;
  map<string, BinTree<Cluster> >::iterator ut, op;
  map<string, double>::const_iterator ot;
  bool b = true;
  bool p = true;
  for (it = distance.begin(); it != distance.end(); ++it) {
    ut = clu.find(it->first);
    BinTree<Cluster> aux = ut->second;
    if (b) {
      min1 = aux;
      b = false;
    }
    for (ot = it->second.begin(); ot != it->second.end(); ++ot) {
      op = clu.find(ot->first);
      BinTree<Cluster> aux2 = op->second;
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

void Cjt_clusters::imprime(const BinTree<Cluster>& c)
  /* pre dado el identificador de un clúster */
  /* post se escribe por el canal estándard de salida el clúster del parámetro implícito que tiene como identificador el parámetro de entrada */
{
  if (c.left().empty() and c.right().empty()) cout << "[" << c.value().consultar_identificador() << "]";
  else {
    cout << "[(" << c.value().consultar_identificador() << ", " << c.value().consultar_dist() << ") ";
    BinTree<Cluster> aux1 = c.left();
    BinTree<Cluster> aux2 = c.right();
    imprime(aux1);
    imprime(aux2);
    cout << "]";
  }
}
