//
// Created by sergio on 21/2/20.
//
/**
 * @file Grafo.h
 * @version 1.0
 * @date 21/2/20
 * @author Serrgio
 * @brief Funciones para el grafo
 *
 */

#ifndef GRAFO_GRAFO_H
#define GRAFO_GRAFO_H
#include<iostream>
using namespace std;

class Arista;
/**
 * @brief Clase que configura los vertices del grafo
 * @author Sergio
 */
class Vertice{
    Vertice *sig;
    Arista *ady;
    int ID;
    friend class Grafo;
};
/**
 * @brief Clase que configura las aristas del grafo
 * @author Sergio
 */
class Arista{
    Arista *sig;
    Vertice *ady;
    int peso;
    friend class Grafo;


};
/**
 * @brief Clase principal de los grafos, contiene todos los metodos necesarios para su correcto funcionamiento
 * @author Sergio
 */
class Grafo {
    Vertice *h;
public:
    /**
     * @brief iniciar: inicia el grafo
     */
    void iniciar();
    /**
     * @brief vacio: evalua si existe el grafo
     * @return true si esta vacio, false si no
     */
    bool Vacio();
    /**
     * @brief indica el tamano del grafo
     * @return tamano del grafo
     */
    int Tamano();
    /**
     * @brief retorna el vertice de nuestra preferencia
     * @param id id de nuestro vertice
     * @return el vertice que buscamos
     */
    Vertice *GetVertice(int id);
    /**
     * @brief funcion para agragar aristas
     * @param origen vertice origen
     * @param dest  vertice destino
     * @param peso peso de la arista
     */
    static void InsertArista(Vertice *origen, Vertice *dest, int peso);
    /**
     * @brief Inserta vertices en el grafo
     * @param ID id del vertice
     */
    void InsertVert(int ID);
    /**
     * @brief imprime un a representacion del grafo
     */
    void Lista();
    /**
     * @brieffuncion que se encarga del algoritmo de Dijkstra
     * @param pInt  matriz de adyacencia del grafo
     * @param i numero de vertices del grafo
     * @param id vertice de origen
     * @param dest vertice de destino
     */
    string dijkstra(int pInt[5][5], int i, int id,int dest);
};
#endif //GRAFO_GRAFO_H