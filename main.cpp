#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "Grafo.h"


using namespace std;
#pragma comment(lib,"ws2_32.lib")
int graph[5][5] = {{0,  5,  10, 0,  10},
                   {5,  0,  0,  20, 8},
                   {10, 0,  0,  1,  0},
                   {0,  20, 1,  0,  15},
                   {10, 8,  0,  15, 0}};
/**
 * @briefSe encarga de abrir y configurar los sockets, ademas de comunicarse con el cliente
 * @return 0 si el proceso es exitoso
 */
int main() {
    Grafo *G=new Grafo;


    G->iniciar();
    G->InsertVert(0);
    G->InsertVert(1);
    G->InsertVert(2);
    G->InsertVert(3);
    G->InsertVert(4);

    G->InsertArista(G->GetVertice(0),G->GetVertice(1),5);
    G->InsertArista(G->GetVertice(1),G->GetVertice(0),5);

    G->InsertArista(G->GetVertice(2),G->GetVertice(3),1);
    G->InsertArista(G->GetVertice(3),G->GetVertice(2),1);

    G->InsertArista(G->GetVertice(0),G->GetVertice(2),10);
    G->InsertArista(G->GetVertice(2),G->GetVertice(0),10);

    G->InsertArista(G->GetVertice(1),G->GetVertice(3),20);
    G->InsertArista(G->GetVertice(3),G->GetVertice(1),20);

    G->InsertArista(G->GetVertice(1),G->GetVertice(4),8);
    G->InsertArista(G->GetVertice(4),G->GetVertice(1),8);

    G->InsertArista(G->GetVertice(0),G->GetVertice(4),10);
    G->InsertArista(G->GetVertice(4),G->GetVertice(0),10);

    G->InsertArista(G->GetVertice(3),G->GetVertice(4),15);
    G->InsertArista(G->GetVertice(4),G->GetVertice(3),15);

    //crear socket
    int listening=socket(AF_INET,SOCK_STREAM,0);
    if(listening==-1){
        cerr<<"no se pudo crear el socket";
        return -1;
    }
    //ponerle ip al socket
    sockaddr_in hint;
    hint.sin_family=AF_INET;
    hint.sin_port=htons(54000);
    inet_pton(AF_INET,"0.0.0.0",&hint.sin_addr);
    if(bind(listening,(sockaddr*)&hint, sizeof(hint)) == -1){
        cerr<<"no ";
        return -2;
    }
    //Probar la escucha del socket
    listen(listening,5);
    if(listen(listening,5)==-1){
        cerr<<"el socket no escucha";
        return -3;
    }
    //Aceptar las llamadas
    sockaddr_in client;
    socklen_t  clientSize= sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    int clientSocket=accept(listening, (sockaddr*)&client, &clientSize);
    if(clientSocket==-1){
        cerr<<"problema con la coneccion";
        return -4;
    }
    //cerrar socket, limpiar host y svc
    close(listening);
    memset(host, 0, NI_MAXHOST);
    memset(svc,0,NI_MAXSERV);
    int result=getnameinfo((sockaddr*)&client, sizeof(client),host,NI_MAXHOST,svc,NI_MAXSERV,0);
    if(result){
        cout<<"host conectado en "<<svc<<endl;
    }else{
        inet_ntop(AF_INET, &client.sin_addr,host,NI_MAXHOST);
        cout<<host<<" conectado en "<<ntohs(client.sin_port)<<endl;
        string bienvenida="Bienvenido, por favor ingrese el nombre del nodo 1";
        send(clientSocket,bienvenida.c_str(),bienvenida.size()+1,0);
    }
    //mientras recibe, imprime y repite el mensaje
    char buf[4096];
    int b=0;
    int cont=0;
    string nodo1;
    string nodo2;
    while(true){
        cout<<"cont: "<<cont<<endl;
        memset(buf,0,4096);
        //limpia el buffer, espera el mensaje y lo imprime
        if(b==0){
            cont++;
            int bytesRecv=recv(clientSocket,buf,4096,0);
            nodo1=string(buf,0,bytesRecv);
            b=1;
            cout<<"n1 "<<nodo1<<endl;
            if(bytesRecv==-1){
                cerr<< "Problema de coneccion"<< endl;
                break;
            }
            if(bytesRecv==0){
                cout<<"Desconectado"<<endl;
                break;
            }
        }
        if(b==1){
            cont++;
            string N2="Por favor ingrese el nombre del nodo 2";
            send(clientSocket,N2.c_str(),N2.size()+1,0);
            memset(buf,0,4096);
            int bytesRecv=recv(clientSocket,buf,4096,0);
            nodo2=string(buf,0,bytesRecv);
            b=2;
            cout<<"n2 "<<nodo2<<endl;
            if(bytesRecv==-1){
                cerr<< "Problema de coneccion"<< endl;
                break;
            }
            if(bytesRecv==0){
                cout<<"Desconectado"<<endl;
                break;
            }
        }
        cout<<"n1: "<<nodo1.size()<<endl;
        cout<<"n2: "<<nodo2.size()<<endl;
        int N1=stoi(nodo1);
        int N2=stoi(nodo2);
        if((nodo1.size() && nodo2.size())==1){
            G->dijkstra(graph,5,N1,N2);
            //DIJKSTRA
            break;
        }
    }
    //Cerrar el socket
    close(clientSocket);
    return 0;
}