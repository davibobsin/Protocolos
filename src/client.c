#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define clear() printf("\033[H\033[J")

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int ident_param(char *str)
{
  int i = 0,j=0;
  char param[25];  
  
  while(str[i]!='!'){
    param[i]=str[i];
    i++;
  }
  
  return atoi(param);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n,sair=0;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    
    // Inicio da configuração inicial de sockets 
    // (cria socket e etc) 
    
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    
    // Fim configuração dos sockets 
    
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting"); //Nao criou socket
    else{  
    // Criou o socket corretamente, inicia loop de controle e comunicação
    
    // Na real dentro deste else vai chamar 2 threads, de controle e de gráfico... (acho)
    // Chama o thread do grafico, já que vai chamar só 1 vez...
      
    // Chamadas de configuração inicial  (seta tempo de simulação etc)
    printf("Qual o consumo inicial? Padrão: 50");
    bzero(buffer,256);
    fgets(buffer,255,stdin);  
    n = write(sockfd,buffer,strlen(buffer));
    /*
    if (n < 0) 
	error("ERROR writing to socket");
    */
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
     /*
    if (n < 0) 
	error("ERROR reading from socket");
    */
    printf("%s\n---------------\n",buffer); //Printa a resposta ao tempo de simulaçao inicial
    
    // Inicio loop de controle (inicia simulação)
    printf("Inicio da simulação ...>> ");
    
//      while(!sair){ // este loop deve ser executado a cada xxms
//        
// //     	if(strcmp(buffer,"sair")==0){
// //	  sair=1;
// //	}
// 	
// 	bzero(buffer,256);
// 	//fgets(buffer,255,stdin);
// 	strcpy(buffer,"getNivel!"); 
// 	n = write(sockfd,buffer,strlen(buffer)); //Envia msg pedindo nível	
// 	if (n < 0) 
// 	    error("ERROR writing to socket");
// 	
// 	bzero(buffer,256);
// 	n = read(sockfd,buffer,255); //Resposta com o nível da planta
// 	
// 	
// 		
// 	
// 
// 	n = write(sockfd,buffer,strlen(buffer));
// 		
// 	if (n < 0) 
// 	    error("ERROR writing to socket");
// 	bzero(buffer,256);
// 	n = read(sockfd,buffer,255);
// 
// 	if (n < 0) 
// 	    error("ERROR reading from socket");
// 	printf("%s\n---------------\n",buffer);
//      }
    }
    
    // Aqui devemos fechar a thread do gráfico...
    
    printf("Fim da simulação ...>> ");
    
    close(sockfd); // Fecha socket
    return 0;
}
