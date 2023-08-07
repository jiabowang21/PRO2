/**
 *  @mainpage Proyecto PRO2
*/

/** @file pro2.cc
    @brief Práctica
*/

#include "Especie.hh"
#include "Cjt_especie.hh"
#include "Cjt_clusters.hh"
#include "Cluster.hh"
using namespace std;

/** @brief Programa principal de la práctica.
*/

int main() {
  int k;
  cin >> k;
  Cjt_especie Cjt;
  Cjt_clusters Cjt_c;
  Cjt.lee_k(k);
  string identificador, gen, opcio;
  map<string, map<string, double> > distance;
  cin >> opcio;
  while (opcio != "fin") {
    if (opcio == "crea_especie") {
      cin >> identificador >> gen;
      cout << "# crea_especie " << identificador << " " << gen << endl;
      Especie es(identificador, gen);
      if (not Cjt.existe_especie(identificador)) {
        Cjt.adderir_especie(es);
      }
      else {
        cout << "ERROR: La especie " << identificador << " ya existe." << endl;
      }
      cout << endl;
    }
    else if (opcio == "obtener_gen") {
      cin >> identificador;
      cout << "# obtener_gen " << identificador << endl;
      if (Cjt.existe_especie(identificador)) {
        Especie es = Cjt.consultar_iden(identificador);
        cout << es.consultar_gen() << endl;
      }
      else {
        cout << "ERROR: La especie " << identificador << " no existe." << endl;
      }
      cout << endl;
    }
    else if (opcio == "distancia") {
      string ident;
      cin >> identificador >> ident;
      cout << "# distancia " << identificador << " " << ident << endl;
      if (not Cjt.existe_especie(identificador) and not Cjt.existe_especie(ident)) {
        cout << "ERROR: La especie " << identificador << " y la especie " << ident << " no existen." << endl;
      }
      else if (not Cjt.existe_especie(identificador)) {
        cout << "ERROR: La especie " << identificador << " no existe." << endl;
      }
      else if (not Cjt.existe_especie(ident)) {
        cout << "ERROR: La especie " << ident << " no existe." << endl;
      }
      else cout << Cjt.distancia(identificador, ident) << endl;
      cout << endl;
    }
    else if (opcio == "elimina_especie") {
      cin >> identificador;
      cout << "# elimina_especie " << identificador << endl;
      if (Cjt.existe_especie(identificador)) {
        Cjt.elimina_especie(identificador);
      }
      else cout << "ERROR: La especie " << identificador << " no existe." << endl;
      cout << endl;
    }
    else if (opcio == "existe_especie") {
      cin >> identificador;
      cout << "# existe_especie " << identificador << endl;
      if (Cjt.existe_especie(identificador)) {
        cout << "SI" << endl;
      }
      else cout << "NO" << endl;
      cout << endl;
    }
    else if (opcio == "lee_cjt_especies") {
      Cjt.lee_cjt_especies();
      Cjt_c.inicializa_clusters(Cjt.consultar_conjunto());
      cout << "# lee_cjt_especies" << endl;
      cout << endl;
    }
    else if (opcio == "imprime_cjt_especies") {
      cout << "# imprime_cjt_especies" << endl;
      Cjt.imprime_cjt_especies();
      cout << endl;
    }
    else if (opcio == "tabla_distancias") {
      cout << "# tabla_distancias" << endl;
      distance = Cjt.tabla_distancias();
      Cjt.imprime_tabla_distancias(distance);
      cout << endl;
    }
    else if (opcio == "inicializa_clusters") {
      cout << "# inicializa_clusters" << endl;
      Cjt_c.inicializa_clusters(Cjt.consultar_conjunto());
      distance = Cjt.tabla_distancias();
      Cjt.imprime_tabla_distancias(distance);
      cout << endl;
    }
    else if (opcio == "ejecuta_paso_wpgma") {
      cout << "# ejecuta_paso_wpgma" << endl;
      if (Cjt_c.size() <= 1) {
        cout << "ERROR: num_clusters <= 1" << endl;
      }
      else {
        Cjt_c.actualiza_tabla_distancias(distance);
        Cjt.imprime_tabla_distancias(distance);
      }
      cout << endl;
    }
    else if (opcio == "imprime_cluster") {
      cin >> identificador;
      cout << "# imprime_cluster " << identificador << endl;
      if (not Cjt_c.existe_cluster(identificador)) {
        cout << "ERROR: El cluster " << identificador << " no existe." << endl;
      }
      else {
        Cluster p = Cjt_c.buscar_cluster(identificador);
        BinTree<string> c = p.consultar_arbol();
        Cjt_c.imprime_cluster(c);
        cout << endl;
      }
      cout << endl;
    }
    else if (opcio == "imprime_arbol_filogenetico") {
      cout << "# imprime_arbol_filogenetico" << endl;
      if (Cjt.empty()) {
        cout << "ERROR: El conjunto de clusters es vacio." << endl;
      }
      else {
        Cjt_c.inicializa_clusters(Cjt.consultar_conjunto());
        while (Cjt_c.size() > 1) {
          Cjt_c.actualiza_tabla_distancias(distance);
        }
        Cluster p = Cjt_c.arbol_filogenetico();
        BinTree<string> c = p.consultar_arbol();
        Cjt_c.imprime_cluster(c);
        cout << endl;
      }
      cout << endl;
    }
    cin >> opcio;
  }
}
