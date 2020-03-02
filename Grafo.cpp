//
// Created by sergio on 21/2/20.
//
/**
 *  @brief Codigo para el funcionamiento de los grafos y Dijkstra
 * @author Sergio
 */
#include "Grafo.h"
#include <iostream>

#define max 5
#define INFINITY 9999
/**
     * @brief iniciar: inicia el grafo
     */
void Grafo::iniciar() {
    h=NULL;
}
/**
 * @brief vacio: evalua si existe el grafo
 * @return true si esta vacio, false si no
 */
bool Grafo::Vacio() {
    if(h==NULL){

        return true;
    }
    return false;
}
/**
 * @brief retorna el vertice de nuestra preferencia
 * @param id id de nuestro vertice
 * @return el vertice que buscamos
 */
int Grafo::Tamano() {
    int cont=0;
    Vertice *aux;
    aux=h;
    while(aux!=NULL){
        cout<<"hola"<<endl;
        cont++;
        aux=aux->sig;
    }
    return cont;

}
/**
 * @brief funcion para agragar aristas
 * @param origen vertice origen
 * @param dest  vertice destino
 * @param peso peso de la arista
 */
Vertice *Grafo::GetVertice(int id) {
    Vertice *aux;
    aux=h;
    while(aux!=NULL){
        if(aux->ID==id){
            return aux;
        }
        aux=aux->sig;
    }
    return NULL;
}
/**
 * @brief Inserta vertices en el grafo
 * @param ID id del vertice
 */
void Grafo::InsertVert(int ID) {

    Vertice *nuevo=new Vertice;
    nuevo->ID= ID;
    nuevo->sig=NULL;
    nuevo->ady=NULL;

    if(Vacio()){
        h=nuevo;
    }else{
        Vertice *aux;
        aux=h;
        while(aux->sig!=NULL){
            aux=aux->sig;
        }
        aux->sig=nuevo;
    }
}
/**
 * @brief funcion para agragar aristas
 * @param origen vertice origen
 * @param dest  vertice destino
 * @param peso peso de la arista
 */

void Grafo::InsertArista(Vertice *origen, Vertice *dest, int peso) {
    Arista *nueva=new Arista;
    nueva->peso=peso;
    nueva->sig=NULL;
    nueva->ady=NULL;
    Arista *aux;
    aux=origen->ady;
    if(aux==NULL){
        origen->ady=nueva;
        nueva->ady=dest;

    }else{
        while(aux->sig!=NULL){
            aux=aux->sig;
        }
        aux->sig=nueva;
        nueva->ady=dest;

    }
}
/**
 * @brief imprime un a representacion del grafo
 */
void Grafo::Lista() {
    Vertice *VertAux;
    Arista *AristAux;
    VertAux=h;
    while(VertAux!=NULL){
        cout<<VertAux->ID<<"->";
        AristAux=VertAux->ady;
        while(AristAux!=NULL){
            cout<<AristAux->ady->ID<<"->";
            AristAux=AristAux->sig;
        }
        VertAux=VertAux->sig;
        cout<<endl;
    }


}
/**
 * @brieffuncion que se encarga del algoritmo de Dijkstra
 * @param pInt  matriz de adyacencia del grafo
 * @param n numero de vertices del grafo
 * @param ori vertice de origen
 * @param dest vertice de destino
 */
void Grafo::dijkstra(int G[5][5], int n, int ori, int dest) {
    int cost[max][max],distance[max],pred[max];
    int visited[max],count,mindistance,nextnode,i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=G[i][j];
    for(i=0;i<n;i++) {
        distance[i]=cost[ori][i];
        pred[i]=ori;
        visited[i]=0;
    }
    distance[ori]=0;
    visited[ori]=1;
    count=1;
    while(count<n-1) {
        mindistance=INFINITY;
        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i]) {
                mindistance=distance[i];
                nextnode=i;
            }
        visited[nextnode]=1;
        for(i=0;i<n;i++)
            if(!visited[i])
                if(mindistance+cost[nextnode][i]<distance[i]) {
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
        count++;
    }
    for(i=0;i<n;i++)
        if(i!=ori) {
            if(i==dest) {
                cout << "\nDistancia del nodo " << ori<<" al nodo "<<i << " es de: " << distance[i];
                cout << "\nCamino= " << i;
                j = i;
                do {
                    j = pred[j];
                    cout << "<-" << j;
                } while (j != ori);
            }
        }

}