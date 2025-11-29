
-----REALIZADO POR-----
Santiago Carrasquero 31.653.014
Eric Vargas 31.907.574

Librería de Grafos en la materia Estructura Dinamica de Datos

Este proyecto es una librería de grafos implementada en C++ que permite trabajar con grafos de manera fácil y rápida. 
La librería incluye las funciones más importantes para trabajar con grafos como recorridos BFS Y DFS, encontrar el camino más corto usando Dijkstra, y verificar si el grafo es conexo.
El objetivo de este proyecto es tener una herramienta simple para crear grafos, cargarlos desde archivos y aplicar algoritmos clásicos sin necesidad de escribir todo el código desde cero cada vez.

FUNCIONES DEL PROGRAMA

algunas opciones destacadas podrian ser 

Mostrar grafo: Te muestra todas las conexiones del grafo en formato de lista
es util para ver como esta estructurado

Agregar Arista: permite agregar una nueva conexion al grafo y te pide el vertice de origen, destino y peso

Dijkstra: usa este algoritmo para encontrar el camino mas corto entre dos vertices, pide origen y destino
y luego muestra la distancia minima y el camino completo


COMPILACION Y EJECUCION DEL PROGRAMA

una vez clonado el repositorio, debemos acceder a la carpeta del proyecto de la siguiente forma
en vs code abrimos el terminal con CTRL+Ñ, luego de eso ponemos cd libreria-grafos y entrariamos en la carpeta
una vez dentro debemos compilar el codigo primeramente, con el siguiente comando g++ -Wall src/main.cpp src/Grafo.cpp -o bin/grafos
si la compilacion es exitosa entonces se creara un archivo .exe que es con el cual ejecutaremos el programa

despues de esto para poder ejecutar, simplemente colocamos cd bin para poder entrar a la carpeta BIN donde esta el archivo ejecutable con los datos
una vez dentro de la carpeta solamente debemos colocar ./grafos.exe
y con eso el codigo ya se ejecutaria y podriamos probar el programa
