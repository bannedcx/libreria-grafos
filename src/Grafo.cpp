#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

//constructor
Grafo::Grafo(int vertices, bool dirigido) {
    numVertices = vertices;
    esDirigido = dirigido;
    
    //array dinamico
    this->vertices = new NodoVertice[numVertices];
    for (int i = 0; i < numVertices; i++) {
        this->vertices[i].id = i;
        this->vertices[i].listaAristas = NULL;
    }
    
    //matriz dinamica
    matrizPesos = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        matrizPesos[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            matrizPesos[i][j] = 0;
        }
    }
}

Grafo::~Grafo() {
    liberarListasAristas();
    
    for (int i = 0; i < numVertices; i++) {
        delete[] matrizPesos[i];
    }
    delete[] matrizPesos;
    
    delete[] vertices;
}

void Grafo::liberarListasAristas() {
    for (int i = 0; i < numVertices; i++) {
        NodoArista* actual = vertices[i].listaAristas;
        while (actual != NULL) {
            NodoArista* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        vertices[i].listaAristas = NULL;
    }
}

void Grafo::agregarAristaALista(int origen, int destino, int peso) {
    NodoArista* nuevaArista = new NodoArista(destino, peso);
    
    //agregar al inicio de la lista
    nuevaArista->siguiente = vertices[origen].listaAristas;
    vertices[origen].listaAristas = nuevaArista;
}

bool Grafo::existeArista(int origen, int destino) {
    NodoArista* actual = vertices[origen].listaAristas;
    while (actual != NULL) {
        if (actual->destino == destino) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void Grafo::agregarArista(int origen, int destino, int peso) {
    if (origen < 0 || destino < 0 || origen >= numVertices || destino >= numVertices) {
        cout << "Error: Vertices invalidos" << endl;
        return;
    }
    
    if (existeArista(origen, destino)) {
        cout << "La arista ya existe" << endl;
        return;
    }
    
    agregarAristaALista(origen, destino, peso);
    matrizPesos[origen][destino] = peso;
    
    if (!esDirigido) {
        agregarAristaALista(destino, origen, peso);
        matrizPesos[destino][origen] = peso;
    }
    
    cout << "Arista agregada: " << origen << " -> " << destino 
         << " (peso: " << peso << ")" << endl;
}

// ==================== MOSTRAR GRAFO ====================
void Grafo::mostrarGrafo() {
    cout << "\n==GRAFO (Lista de Adyacencia)==" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << "Vertice " << i << ": ";
        
        NodoArista* actual = vertices[i].listaAristas;
        while (actual != NULL) {
            cout << actual->destino << "(" << actual->peso << ")";
            if (actual->siguiente != NULL) {
                cout << " -> ";
            }
            actual = actual->siguiente;
        }
        
        if (vertices[i].listaAristas == NULL) {
            cout << "(sin conexiones)";
        }
        
        cout << endl;
    }
}

// ==================== CARGAR DESDE CSV ====================
bool Grafo::cargarDesdeCSV(const string& archivo) {
    ifstream file(archivo.c_str());
    if (!file.is_open()) {
        cout << "No se pudo abrir " << archivo << endl;
        return false;
    }
    
    string linea;
    getline(file, linea); // Saltar encabezado
    
    int aristasLeidas = 0;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string campos[3];
        int index = 0;
        string campo;
        
        while (getline(ss, campo, ',') && index < 3) {
            campos[index] = campo;
            index++;
        }
        
        if (index >= 3) {
            int origen = atoi(campos[0].c_str());
            int destino = atoi(campos[1].c_str());
            int peso = atoi(campos[2].c_str());
            
            agregarArista(origen, destino, peso);
            aristasLeidas++;
        }
    }
    
    file.close();
    cout << "\nGrafo cargado: " << aristasLeidas << " aristas" << endl;
    return true;
}

// ==================== BFS ====================
void Grafo::BFS(int inicio) {
    if (inicio < 0 || inicio >= numVertices) {
        cout << "Vertice inicio invalido" << endl;
        return;
    }

    // Array dinámico de visitados
    bool* visitado = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
    }
    
    // Cola implementada con lista enlazada
    NodoPila* frente = NULL;
    NodoPila* final = NULL;
    
    cout << "\n==RECORRIDO BFS==" << endl;
    cout << "Inicio: vertice " << inicio << endl;
    cout << "Orden: ";
    
    // Encolar inicio
    NodoPila* nuevoNodo = new NodoPila(inicio);
    if (frente == NULL) {
        frente = final = nuevoNodo;
    } else {
        final->siguiente = nuevoNodo;
        final = nuevoNodo;
    }
    visitado[inicio] = true;
    
    while (frente != NULL) {
        // Desencolar
        int v = frente->dato;
        NodoPila* temp = frente;
        frente = frente->siguiente;
        if (frente == NULL) final = NULL;
        delete temp;
        
        cout << v << " ";
        
        // Recorrer vecinos
        NodoArista* arista = vertices[v].listaAristas;
        while (arista != NULL) {
            int vecino = arista->destino;
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                
                // Encolar vecino
                NodoPila* nuevo = new NodoPila(vecino);
                if (frente == NULL) {
                    frente = final = nuevo;
                } else {
                    final->siguiente = nuevo;
                    final = nuevo;
                }
            }
            arista = arista->siguiente;
        }
    }
    
    cout << endl;
    delete[] visitado;
}

// ==================== DFS ====================
void Grafo::DFS(int inicio) {
    if (inicio < 0 || inicio >= numVertices) {
        cout << "Error: Vertice inicio invalido" << endl;
        return;
    }

    // Array dinámico de visitados
    bool* visitado = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
    }
    
    // Pila implementada con lista enlazada
    NodoPila* pila = NULL;
    
    cout << "\n==RECORRIDO DFS==" << endl;
    cout << "Inicio: vertice " << inicio << endl;
    cout << "Orden: ";
    
    // Apilar inicio
    NodoPila* nuevoNodo = new NodoPila(inicio);
    nuevoNodo->siguiente = pila;
    pila = nuevoNodo;
    
    while (pila != NULL) {
        // Desapilar
        int v = pila->dato;
        NodoPila* temp = pila;
        pila = pila->siguiente;
        delete temp;
        
        if (!visitado[v]) {
            visitado[v] = true;
            cout << v << " ";
            
            //Apilar vecinos (en orden inverso para mantener orden logico)
            //Primero contamos cuántos vecinos hay
            int numVecinos = 0;
            NodoArista* contador = vertices[v].listaAristas;
            while (contador != NULL) {
                numVecinos++;
                contador = contador->siguiente;
            }
            
            //array temporal de vecinos
            int* vecinos = new int[numVecinos];
            NodoArista* arista = vertices[v].listaAristas;
            int index = 0;
            while (arista != NULL) {
                vecinos[index++] = arista->destino;
                arista = arista->siguiente;
            }
            
            //Apilar en orden inverso
            for (int i = numVecinos - 1; i >= 0; i--) {
                if (!visitado[vecinos[i]]) {
                    NodoPila* nuevo = new NodoPila(vecinos[i]);
                    nuevo->siguiente = pila;
                    pila = nuevo;
                }
            }
            
            delete[] vecinos;
        }
    }
    
    cout << endl;
    delete[] visitado;
}

// ==================== DIJKSTRA ====================
void Grafo::dijkstra(int origen, int destino) {
    if (origen < 0 || destino < 0 || origen >= numVertices || destino >= numVertices) {
        cout << "Vertices invalidos" << endl;
        return;
    }

    // Arrays dinamicos
    int* distancia = new int[numVertices];
    int* padre = new int[numVertices];
    bool* visitado = new bool[numVertices];
    
    // Inicializar
    for (int i = 0; i < numVertices; i++) {
        distancia[i] = INT_MAX;
        padre[i] = -1;
        visitado[i] = false;
    }
    
    distancia[origen] = 0;
    
    cout << "\n==ALGORITMO DIJKSTRA==" << endl;
    cout << "Origen: " << origen << " | Destino: " << destino << endl;
    
    for (int cont = 0; cont < numVertices; cont++) {
        // Encontrar vertice con menor distancia
        int minDist = INT_MAX;
        int u = -1;
        
        for (int v = 0; v < numVertices; v++) {
            if (!visitado[v] && distancia[v] < minDist) {
                minDist = distancia[v];
                u = v;
            }
        }
        
        if (u == -1) break;
        
        visitado[u] = true;
        
        // Actualizar distancias de vecinos
        NodoArista* arista = vertices[u].listaAristas;
        while (arista != NULL) {
            int v = arista->destino;
            int peso = arista->peso;
            
            if (!visitado[v] && distancia[u] != INT_MAX) {
                if (distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                    padre[v] = u;
                }
            }
            arista = arista->siguiente;
        }
    }
    
    // Mostrar resultado
    if (distancia[destino] == INT_MAX) {
        cout << "No hay camino entre " << origen << " y " << destino << endl;
    } else {
        cout << "Distancia minima: " << distancia[destino] << endl;
        cout << "Camino: ";
        
        // Contar longitud del camino
        int longitud = 0;
        int actual = destino;
        while (actual != -1) {
            longitud++;
            actual = padre[actual];
        }
        
        // Crear array para el camino
        int* camino = new int[longitud];
        actual = destino;
        int index = longitud - 1;
        while (actual != -1) {
            camino[index--] = actual;
            actual = padre[actual];
        }
        
        // Mostrar camino
        for (int i = 0; i < longitud; i++) {
            cout << camino[i];
            if (i < longitud - 1) cout << " -> ";
        }
        cout << endl;
        
        delete[] camino;
    }
    
    // Liberar memoria
    delete[] distancia;
    delete[] padre;
    delete[] visitado;
}

// ==================== ES CONEXO ====================
bool Grafo::esConexo() {
    if (numVertices == 0) return true;
    
    bool* visitado = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
    }
    
    // Cola para BFS
    NodoPila* frente = NULL;
    NodoPila* final = NULL;
    
    // Encolar primer vértice
    NodoPila* inicio = new NodoPila(0);
    frente = final = inicio;
    visitado[0] = true;
    int contador = 1;
    
    while (frente != NULL) {
        // Desencolar
        int v = frente->dato;
        NodoPila* temp = frente;
        frente = frente->siguiente;
        if (frente == NULL) final = NULL;
        delete temp;
        
        // Recorrer vecinos
        NodoArista* arista = vertices[v].listaAristas;
        while (arista != NULL) {
            int vecino = arista->destino;
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                contador++;
                
                // Encolar
                NodoPila* nuevo = new NodoPila(vecino);
                if (frente == NULL) {
                    frente = final = nuevo;
                } else {
                    final->siguiente = nuevo;
                    final = nuevo;
                }
            }
            arista = arista->siguiente;
        }
    }
    
    delete[] visitado;
    return contador == numVertices;
}

// ==================== NUMERO DE ARISTAS ====================
int Grafo::numeroAristas() {
    int total = 0;
    
    for (int i = 0; i < numVertices; i++) {
        NodoArista* arista = vertices[i].listaAristas;
        while (arista != NULL) {
            total++;
            arista = arista->siguiente;
        }
    }
    
    if (!esDirigido) {
        total /= 2;
    }
    
    return total;
}

void Grafo::mostrarMatriz() {
    cout << "\n==MATRIZ DE ADYACENCIA==" << endl;
    cout << "   ";
    for (int i = 0; i < numVertices; i++) {
        cout << " " << i << " ";
    }
    cout << endl;
    
    for (int i = 0; i < numVertices; i++) {
        cout << i << " |";
        for (int j = 0; j < numVertices; j++) {
            cout << " " << matrizPesos[i][j] << " ";
        }
        cout << endl;
    }
}
