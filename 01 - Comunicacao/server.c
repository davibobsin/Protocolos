/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define clear() printf("\033[H\033[J")


void chamar(char *str,int valor,int qtd){
  int find=0;
  if(strcmp(str,"testaConexao")==0)
  {
    find=1;
  }
  if(strcmp(str,"setPeriodoSimulacao")==0)
  {
    printf("PERIOD SIM: %d\n",valor);
    find=1;
  }
  if(strcmp(str,"setConsumo")==0)
  {
      printf("CONSM AQUI: %d\n",valor);
    find=1;
  }
  if(strcmp(str,"iniciaSimulacao")==0)
  {
      printf("SIMULAC\n");
    find=1;
  }
  if(strcmp(str,"abreValvula")==0)
  {
      printf("ABRIU OTÁRIO:%d\n",valor);
    find=1;
  }
  if(strcmp(str,"fechaValvula")==0)
  {
      printf("FESHOW:%d\n",valor);
    find=1;
  }
  if(strcmp(str,"getNivel")==0)
  {
      printf("NIVEL AQUI\n");
    find=1;
  }
  if(!find)
  {
      printf("Comando inválido!\n");
  } 
}

void ident(char *str){
  int i = 0,j=0,flag_qtd=0,valor;
  char param[25],func[25];
  while(str[i]!='\0'){
    if(str[i]=='!')
    {
      param[j]='\0';
      if(flag_qtd){
	valor=atoi(param);
      }
      else
      strcpy(func,param);
	chamar(func,valor,flag_qtd);
      j=0;
      flag_qtd=0;
    }
    else if(str[i]=='#')
    {
      param[j]='\0';
      strcpy(func,param);
      j=0;
      flag_qtd=1;
    }
    else{
      param[j]=str[i];
      j++;
    }
    i++;
  }
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno,sair=0;
     socklen_t clilen;
     char buffer[256],escrita[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n,m;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening s	ocket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
      listen(sockfd,5);
      clilen = sizeof(cli_addr);
      newsockfd = accept(sockfd, 
		  (struct sockaddr *) &cli_addr, 
		  &clilen);
      if (newsockfd < 0) 
	    error("ERROR on accept");
	clear();
      while(!sair){

	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	ident(buffer);
	if(strstr(buffer,"sair")==0){
	  sair=1;
	  printf("Saindo\n");
	  n = write(newsockfd,"Closing connection",18);
	}
	
	if (n < 0) error("ERROR reading from socket");
	
	n = write(newsockfd,"Planta: gotcha",18);
	if (n < 0) error("ERROR writing to socket");
     }
     close(newsockfd);
     close(sockfd);
 
     return 0; 
}
