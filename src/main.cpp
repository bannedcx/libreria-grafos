#include "Grafo.h"
#include <iostream>

using namespace std;

void mostrarMenu() {
    cout << "==LIBRERIA DE GRAFOS==" << endl;
    cout << "1. Mostrar grafo" << endl;
    cout << "2. Mostrar matriz de adyacencia" << endl;
    cout << "3. Agregar arista" << endl;
    cout << "4. Recorrido BFS" << endl;
    cout << "5. Recorrido DFS" << endl;
    cout << "6. Camino mas corto (Dijkstra)" << endl;
    cout << "7. Verificar si es conexo" << endl;
    cout << "8. Informacion del grafo" << endl;
    cout << "0. Salir" << endl;
    cout << "\nOpcion: ";
}
