#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
using namespace std;

class Grafo {
private:
    int numVertices;
    vector<vector<int> > listaAdyacencia; 
    vector<vector<int> > pesos;           
    bool esDirigido;
    
public:

    Grafo(int vertices, bool dirigido = false);
    
    void agregarArista(int origen, int destino, int peso = 1);
    void mostrarGrafo();
    
    bool cargarDesdeCSV(const string& archivo);
    
    // Algoritmos de recorrido
    void BFS(int inicio);
    void DFS(int inicio);
    
    // Camino mas corto
    void dijkstra(int origen, int destino);
    
    // Otras funciones
    bool esConexo();
    int numeroAristas();
    void mostrarMatriz();
};

#endif
