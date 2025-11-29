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

int main() {
    cout << "==LIBRERIA DE GRAFOS EN C++==" << endl;
    
    // Cargar grafo desde CSV
    cout << "Cargando grafo desde archivo..." << endl;
    Grafo grafo(10, false); // 10 vertices, no dirigido
    
    if (!grafo.cargarDesdeCSV("grafo.csv")) {
        cout << "No se pudo cargar el archivo CSV" << endl;
        cout << "Creando grafo vacio..." << endl;
    }
    
    cout << "\nPresione Enter para continuar...";
    cin.get();
    
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                grafo.mostrarGrafo();
                break;
            }
            
            case 2: {
                grafo.mostrarMatriz();
                break;
            }
            
            case 3: {
                int origen, destino, peso;
                cout << "\nVertice origen: ";
                cin >> origen;
                cout << "Vertice destino: ";
                cin >> destino;
                cout << "Peso: ";
                cin >> peso;
                grafo.agregarArista(origen, destino, peso);
                break;
            }
            
            case 4: {
                int inicio;
                cout << "\nVertice de inicio: ";
                cin >> inicio;
                grafo.BFS(inicio);
                break;
            }
            
            case 5: {
                int inicio;
                cout << "\nVertice de inicio: ";
                cin >> inicio;
                grafo.DFS(inicio);
                break;
            }
            
            case 6: {
                int origen, destino;
                cout << "\nVertice origen: ";
                cin >> origen;
                cout << "Vertice destino: ";
                cin >> destino;
                grafo.dijkstra(origen, destino);
                break;
            }
            
            case 7: {
                if (grafo.esConexo()) {
                    cout << "\nEl grafo SI es conexo" << endl;
                } else {
                    cout << "\nEl grafo NO es conexo" << endl;
                }
                break;
            }
            
            case 8: {
                cout << "\n==INFORMACION==" << endl;
                cout << "Numero de aristas: " << grafo.numeroAristas() << endl;
                cout << "Conexo: " << (grafo.esConexo() ? "Si" : "No") << endl;
                break;
            }
            
            case 0: {
                cout << "\nGracias por usar la libreria" << endl;
                break;
            }
            
            default: {
                cout << "\nOpcion invalida" << endl;
            }
        }
        
        if (opcion != 0) {
            cout << "\nPresiona enter para seguir.";
            cin.ignore();
            cin.get();
        }
        
    } while(opcion != 0);
    
return 0;
}
