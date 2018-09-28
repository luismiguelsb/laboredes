// testecli.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define	SOCKET	int
#define INVALID_SOCKET  ((SOCKET)~0)

//#define STR_IPSERVIDOR "192.168.0.146"

int main(int argc, char* argv[])
{
  SOCKET s; //Descritor do socket
  struct sockaddr_in  s_cli, s_serv; //Estrutura que define os campos para o socket


  // abre socket TCP
  if ((s = socket(AF_INET, SOCK_STREAM, 0))==INVALID_SOCKET)
  {
    printf("Erro iniciando socket\n");
    return(0);
  }

  // seta informacoes IP/Porta locais
  s_cli.sin_family = AF_INET; //Ajusta a estrutura peer para a familia internet
  s_cli.sin_addr.s_addr = htonl(INADDR_ANY); //Ajusta o endereço do cliente
  s_cli.sin_port = htons(atoi(argv[3])); //Ajusta a porta do peer com a porta. A função htons coloca na ordem da rede

  // associa configuracoes locais com socket
  if ((bind(s, (struct sockaddr *)&s_cli, sizeof(s_cli))) != 0)
  {
    printf("erro no bind\n");
    close(s);
    return(0);
  }

  // seta informacoes IP/Porta do servidor remoto
  s_serv.sin_family = AF_INET; //Ajusta a estrutura peer para a familia internet
  s_serv.sin_addr.s_addr = inet_addr(argv[1]); //Ajusta o ip destino da estrutura peer
  s_serv.sin_port = htons(atoi(argv[2])); //Ajusta a porta do peer com a porta. A função htons coloca na ordem da rede

  // connecta socket aberto no cliente com o servidor
  if(connect(s, (struct sockaddr*)&s_serv, sizeof(s_serv)) != 0)
  {
    //printf("erro na conexao - %d\n", WSAGetLastError());
    printf("erro na conexao");
    close(s);
    exit(1);
  }

#if 0
  // envia mensagem de conexao - aprimorar para dar IP e porta
  if ((send(s, "Conectado\n", 11,0)) == SOCKET_ERROR);
  {
    printf("erro na transmissão - %d\n", WSAGetLastError());
    closesocket(s);
    return 0;
  }
#endif

  char str[1250]; //Buffer de 1250 bytes a ser enviado 
  char ch; //Caracetere utilizado para get/scan
  int i; //Inteiro para auxiliar nesse scan

  //Le do teclado e salva em str
  for (i = 0; (i<80) && (ch = getchar()) != '\n'; i++)  
	  str[i] = (char)ch;
  str[i] = '\0';

  //envia essa string infinitamente sobrecarregando o servidor
  while(1)
  {

    if ((send(s, (const char *)&str, sizeof(str),0)) < 0)
    {
      close(s);
      return 0;
    }
  }

  // fecha socket e termina programa
  printf("Fim da conexao\n");
  close(s);
  return 0;
}
