#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
/**
 * @author Sergio
 * @brief Socket parte del cliente
 */
using namespace std;
/**
 * @brief Se encarga de abrir y configurar el socket cliente, ademas de conectarse con el socket servidor
 * @return
 */
int main()
{
    //	Crea el socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    //	Le asigna una direccion al socket
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Conecta al servidor en el socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 2;
    }
    char buf[4096];
    string userInput;
    int b=0;
    do {
        if(b==0){
            int bytesReceived = recv(sock, buf, 4096, 0);
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
            b=1;
        }
        cout << "> ";
        getline(cin, userInput);

        //	Envia al servidor
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //	Espera la respuesta
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            // Muestra la respuesta
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
        }
    } while(true);
    //	Cierra el socket
    close(sock);
    return 0;
}
