/* librairie standard ... */
#include <stdlib.h>
/* pour getopt */
#include <unistd.h>
/* déclaration des types de base */
#include <sys/types.h>



#include <winsock2.h>
#include <windows.h>

/* constantes relatives aux domaines, types et protocoles */
// #include <sys/socket.h>
/* constantes et structures propres au domaine UNIX */
// #include <sys/un.h>
/* constantes et structures propres au domaine INTERNET */
// #include <netinet/in.h>
/* structures retournées par les fonctions de gestion de la base de
données du réseau */
// #include <netdb.h>



/* pour les entrées/sorties */
#include <stdio.h>
/* pour la gestion des erreurs */
#include <errno.h>



void construire_message (char *message, char motif, int lg) {
int i;
for (i=0 ; i<lg; i++) message[i] = motif; }
void afficher_message (char *message, int lg) {
int i;
printf("message construit : ");
for (i=0 ; i<lg ; i++) printf("%c", message[i]) ; printf("\n"); }



void main (int argc, char **argv)
{
	int c;
	extern char *optarg;
	extern int optind;
	int nb_message = -1; /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
	int lg_message = 30;  /*Longueur de 30 octets par défaut*/
	int source = -1 ; /* 0=puits, 1=source */
	int protocole=0; /*0=TCP, 1= TCP*/
	while ((c = getopt(argc, argv, "pn:s")) != -1) {
		switch (c) {
		case 'p':
			if (source == 1) {
				printf("usage: cmd [-p|-s][-n ##]\n");
				exit(1);
			}
			source = 0;
			break;

		case 'u':
			protocole = 1;		/*on met la variable protocole à 1 pour UDP*/
			break;     

		case 's':
			if (source == 0) {
				printf("usage: cmd [-p|-s][-n ##]\n");
				exit(1) ;
			}
			source = 1;
			break;

		case 'n':
			nb_message = atoi(optarg);
			break;

		default:
			printf("usage: cmd [-p|-s][-n ##]\n");
			break;
		}
	}

	if (source == -1) {
		printf("usage: cmd [-p|-s][-n ##]\n");
		exit(1) ;
	}

	if (source == 1)
		printf("on est dans la source\n");
	else
		printf("on est dans le puits\n");

	if (nb_message != -1) {
		if (source == 1)
			printf("nb de tampons à envoyer : %d\n", nb_message);
		else
			printf("nb de tampons à recevoir : %d\n", nb_message);
	} else {
		if (source == 1) {
			nb_message = 10 ;
			printf("nb de tampons à envoyer = 10 par défaut\n");
		} else
		printf("nb de tampons à envoyer = infini\n");

	}

	if(protocole ==1){
		if(source==1){
			int sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP); /*On crée le socket UDP 
			(pas sur de ce qu'il faut mettre en dernier arg car pas précisé dans le cours, simple deduction depuis la doc windows)*/

			// struct sockaddr_in server;

			// server.sin_addr.s_addr = inet_addr("192.168.1.4");
			// server.sin_family = AF_INET;
			// server.sin_port = htons( 8080 );
		}	
	}
}
