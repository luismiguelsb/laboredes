#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#define SOCKET int

int main(int argc, char **argv)
{
	struct sockaddr_in peer;	//Estrutura que define os campos para o socket
	SOCKET s;	//Descritor do socket
	int porta, peerlen;	//Porta e peerlen  serão utilizadas ao realizar o bind. 
	int rc, i;	//Em "rc" será salvo o retorno do recvfrom e 'i' é uma variável auxiliar para o parser
	char ip[16], buffer[1250];	//Buffers para guardar o endereço IP e o conteudo do pacote. Serão 1250 bytes contendo lixo
	double rate;	//Taxa de transmissão

	if (argc < 7)  //Testa se o numero de argumentos para o parser está correto
	{
		printf("Utilizar:\n");
		printf("trans -h <numero_ip> -p <porta> -r <rate>\n");
		exit(1);
	}

	// Realiza o parser dos parametros
	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 'h': // Numero IP
				i++;
				strcpy(ip, argv[i]);
				break;

			case 'p': // porta
				i++;
				porta = atoi(argv[i]);
				if (porta < 1024)
				{
					printf("Valor da porta invalido\n");
					exit(1);
				}
				break;
			case 'r':
				i++;
				rate = atof(argv[i]);
				break;

			default:
				printf("Parametro invalido %d: %s\n", i, argv[i]);
				exit(1);
			}
		}
		else
		{
			printf("Parametro %d: %s invalido\n", i, argv[i]);
			exit(1);
		}
	}

	// Cria o socket na familia AF_INET (Internet) e do tipo UDP (SOCK_DGRAM)
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Falha na criacao do socket\n");
		exit(1);
	}
	//strcpy(ip,"127.0.0.1");
	printf("oi\n");
	printf("ip: %s\nporta: %d\n", ip, atoi(argv[4]));



	// Cria a estrutura com quem vai conversar
	peer.sin_family = AF_INET;	//Ajusta a estrutura peer para a familia internet
	peer.sin_port = htons(porta);	//Ajusta a porta do peer com a porta. A função htons coloca na ordem da rede //Ajusta o ip destino da estrutura peer
	peer.sin_addr.s_addr = inet_addr(ip);	//Ajusta o ip destino da estrutura peer
	peerlen = sizeof(peer);

	// Envia pacotes de 1250 bytes "infinitamente"
	while (1)
	{
		sendto(s, buffer, sizeof(buffer), 0, (struct sockaddr *)&peer, peerlen);
		printf("enviando\n");
		usleep(10000000 / rate); //sleep que evita rajadas na transmissão e leva em consideração a taxa de transmissão
	}
}

