OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe:program.o Cjt_especie.o Especie.o Cjt_clusters.o Cluster.o
	g++ -o program.exe program.o Cjt_especie.o Especie.o Cjt_clusters.o Cluster.o
	rm *.o

program.o:program.cc Especie.hh Cjt_especie.hh Cjt_clusters.hh Cluster.hh BinTree.hh
	g++ -c program.cc $(OPCIONS)

Especie.o:Especie.cc Especie.hh
	g++ -c Especie.cc $(OPCIONS)

Cjt_especie.o:Cjt_especie.cc Cjt_especie.hh Especie.hh
	g++ -c Cjt_especie.cc $(OPCIONS)

Cluster.o:Cluster.cc Cluster.hh Cjt_especie.hh BinTree.hh
	g++ -c Cluster.cc $(OPCIONS)

Cjt_clusters.o:Cjt_clusters.cc Cjt_clusters.hh Cluster.hh Cjt_especie.hh BinTree.hh
	g++ -c Cjt_clusters.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe
tar:    
	tar -cvf practica.tar program.cc Especie.cc Cjt_especie.cc Cluster.hh Cluster.cc Especie.hh Cjt_especie.hh Cjt_clusters.cc Cjt_clusters.hh Makefile 
