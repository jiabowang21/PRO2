/** @mainpage

    Ejemplo de práctica resuelta, con documentación completa (incluyendo elementos privados y código).
    El programa principal se encuentra en el módulo program.cc.
    Atendiendo a los tipos de datos sugeridos en el enunciado, necesitaremos 4
    módulos: Especie, Cjt_especie, Cluster, Cjt_clusters.

    Comentarios:
    - La funcionalidad de este programa es la de construir un árbol filogenético para
    un conjunto de N especies, utilizando uno de esos métodos aproximados: el método
    conocido como WPGMA.

    - La distinción entre especie y clúster es debido a que al calcular el ancestro más
    próximo de dos especies, por ejemplo A y B, estamos especulando de la existencia
    de una tercera especie AB y en este caso, usando el término de un clúster de especies
    seria más apropiado, es decir, referirse a AB como un clúster.
*/

/** @file program.cc

    @brief Programa principal

    Este programa tiene como funcionalidad principal resolver las distancias que hay entre
    las diferentes especies de un conjunto y representarlos mediante un árbol filogenético

    Estamos suponiendo que los datos leídos siempre son correctos, ya que
    no incluímos comprobaciones al respecto. Por último, al iniciar el programa, entremos a
    un bucle en que cada iteración realiza una operación, que puede ser la misma o distinta.
    Y finaliza cuando se introduce la opción "fin", que marca la conclusión del programa.
*/

#include "Cjt_especie.hh"
#include "Cjt_clusters.hh"
using namespace std;

int main() {
  Cjt_especie Cjt;
  Cjt_clusters Cjt_c;
  string identificador, gen, opcio;
  cin >> opcio;
  while (opcio != "fin") {
    if (opcio == "crea_especie") {
      cin >> identificador >> gen;
      cout << "# crea_especie " << identificador << " " << gen << endl;
      Especie esp(identificador, gen);
      if (not Cjt.existe_especie(identificador)) {
        Cjt.adderir_especie(esp);
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
        Especie esp = Cjt.consultar_especie(identificador);
        cout << esp.consultar_gen() << endl;
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
      else {
        cout << Cjt.busca_distancias(identificador, ident) << endl;
      }
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
      Cjt.tabla_distancias();
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
      Cjt.imprime_tabla_distancias();
      cout << endl;
    }
    else if (opcio == "inicializa_clusters") {
      cout << "# inicializa_clusters" << endl;
      Cjt.inicializa_conjunto_clusters(Cjt_c);
      Cjt_c.imprime_tabla_distancias();
      cout << endl;
    }
    else if (opcio == "ejecuta_paso_clust") {
      cout << "# ejecuta_paso_clust" << endl;
      if (Cjt_c.size() <= 1) {
        cout << "ERROR: num_clusters <= 1" << endl;
      }
      else {
        Cjt_c.ejecuta_paso_wpgma();
        Cjt_c.imprime_tabla_distancias();
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
        Cjt_c.imprime_cluster(identificador);
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
        Cjt.inicializa_conjunto_clusters(Cjt_c);
        while (Cjt_c.size() > 1) {
          Cjt_c.ejecuta_paso_wpgma();
        }
        Cjt_c.imprime_arbol();
        cout << endl;
      }
      cout << endl;
    }
    cin >> opcio;
  }
}
