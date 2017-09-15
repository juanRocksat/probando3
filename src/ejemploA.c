/*
 ============================================================================
 Name        : ejemploA.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//#include <stdio.h>
//#include <arpa/inet.h>
//#include <sys/socket.h>
//#include <sys/types.h>
//#include <errno.h>
//#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
typedef char* string;

typedef struct sockaddr_in InformacionDeDireccionDeSocket_v2;
InformacionDeDireccionDeSocket_v2 preparaDirecciondelServidor(){
	InformacionDeDireccionDeSocket_v2 direccionDeSocket;
	direccionDeSocket.sin_family = AF_INET;
	direccionDeSocket.sin_addr.s_addr = INADDR_ANY;
	direccionDeSocket.sin_port = htons(8080);
	return direccionDeSocket;
}
int  verificarError(int n, string s){
	if(n==-1 || n !=0){
		perror(strcat("error en: ",s));
		return 1;
	}
}
int main(void) {
	puts("comenzando");
	InformacionDeDireccionDeSocket_v2 direccionServer1 = preparaDirecciondelServidor();
	int servidor = socket(AF_INET, SOCK_STREAM, 0);

	int loDeBind = bind(servidor, (void*) &direccionServer1, sizeof(direccionServer1));
	verificarError(loDeBind,"bind");
	printf("Estoy escuchando\n");
	listen(servidor, 100);
	puts("parte 2 ");
	InformacionDeDireccionDeSocket_v2 direccionCliente;
	unsigned int len ;
	int cliente = accept(servidor,(void*)&direccionCliente,&len);
	printf("recibi una conexion en %d !! \n",cliente);
	send(cliente,"Buenas ",sizeof("Buenas "),0);
	send(cliente,"lol",sizeof("lol"),0);

	for(;;);

	puts("finihs");
return EXIT_SUCCESS;
}
