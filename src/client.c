#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include "bib_graf.c"

#define clear() printf("\033[H\033[J")

typedef struct data_struct {
  double inangle[21];
  double controle[21];
  double level[21];
  double tempo[21];
} Data;

Data dados;
double sp=50,Kp=10;
double t=0;
int sair=0;

int mili(int milisec){
  struct timespec req = {0};
  req.tv_sec = 0;
  req.tv_nsec = milisec * 1000000L;
  nanosleep(&req, (struct timespec *)NULL);

  return 1;  
}

void *graph(void *arg){
  Tdataholder *data;
  int i,j;
  double time_offset=0;
  
  data = datainit(640,480,55,110,45,0,0);
  
  while(1){
    for(j=1;j<20;j+=5){
      mili(50);
      for(i=j;i<(j+5);i++){
	datadraw(data,dados.tempo[i]-time_offset,dados.level[i],0,dados.controle[i]);
	if((dados.tempo[i]-time_offset)>=55){
	  time_offset+=55;
	  data = datainit(640,480,55,110,45,0,0);
	}
      }
      quitevent();
    }
  }
  sair = 1;
}


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
    //APAGAR
    int i=0;
    double t2=0;
    
    int sockfd, portno, n;
    pthread_t thread_graf;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    
    // Inicio da configuração inicial de sockets 
    // (cria socket e etc) 
    
    if (argc < 4 || argc > 4) {
       fprintf(stderr,"usage %s <hostname> <porta> <consumo>\n", argv[0]);
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
      
      pthread_create(&thread_graf, NULL, graph, NULL);//THREAD GRAFICO
      bzero(buffer,256);
      sprintf(buffer,"setConsumo#%d!",atoi(argv[3]));
      n = write(sockfd,buffer,strlen(buffer));
      
	bzero(buffer,256);
    	n = read(sockfd,buffer,255);
    	printf("%s\n---------------\n",buffer); //Printa a resposta ao tempo de simulaçao inicial

      bzero(buffer,256);
      sprintf(buffer,"iniciaSimulacao!");
      n = write(sockfd,buffer,strlen(buffer));
      
	bzero(buffer,256);
    	n = read(sockfd,buffer,255);
    	printf("%s\n---------------\n",buffer); //Printa a resposta do inicio da simulaçao

    // Criou o socket corretamente, inicia loop de controle e comunicação
    
    // Na real dentro deste else vai chamar 2 threads, de controle e de gráfico... (acho)
    // Chama o thread do grafico, já que vai chamar só 1 vez...
      
    // Chamadas de configuração inicial  (seta tempo de simulação etc)
    
    /*
    if (n < 0) 
	error("ERROR writing to socket");
    */
    
    
    // Inicio loop de controle (inicia simulação)
      
    
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
    
    //--- CONTROLE---//
      while(!sair){
	
	mili(10);
	bzero(buffer,256);
	sprintf(buffer,"getNivel!");
      	n = write(sockfd,buffer,strlen(buffer));
      	
	bzero(buffer,256);
    	n = read(sockfd,buffer,255);
	sscanf(buffer,"%lf",&dados.level[i]);
	dados.level[i]=dados.level[i]*100;
	dados.controle[i]=(sp-dados.level[i])*Kp;
	
	bzero(buffer,256);
	if((dados.controle[i]-dados.controle[i-1])>0.0)
		sprintf(buffer,"abreValvula#%lf!",dados.controle[i]-dados.controle[i-1]);
	else
		sprintf(buffer,"fechaValvula#%lf!",dados.controle[i-1]-dados.controle[i]);
      	n = write(sockfd,buffer,strlen(buffer));
      	
	bzero(buffer,256);
    	n = read(sockfd,buffer,255);
    	printf("%lf\n---------------\n",dados.level[i]); //Printa a resposta de 

	dados.tempo[i]=t;
	t+=0.01;
	i++;
	if(i>=21){
		i=1;
		dados.controle[0]=dados.controle[20];
	}
      }
      printf("Fim do controle ...");
    }
    
    pthread_join(thread_graf, NULL);
    close(sockfd); // Fecha socket
    return 0;
}
