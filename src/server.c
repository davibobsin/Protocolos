/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h> 	
#include <sys/socket.h>
#include <netinet/in.h>
#include "bib_graf.c"
#include <pthread.h>

#define clear() printf("\033[H\033[J")

/*
 * Server: ang entrada ang saida  e nivel... 
 * cliente(CLP)  ang entrada e  nivel (calculados pelo controle...)
 *
 */ 
int per_sim = 0;
int max = 50;
int valvula = 0;
int nivel = 100;
int simulacao=0;
double t=0;
double pi=3.1415926;


typedef struct data_struct {
  double saida[20];
  double controle[20];
  double tempo[20];
  double level[20]; //Nivel do tanque...
  double inangle[20]; // Angulo de entrada da válvula?
  double outangle[20]; // Angulo de saída da válvula?
  double valor; //valor que vem da comucicacao IP. Valor da abertura da valvula

  int consumo; //Primeira info
  int atualizar; //flag para atualizar o valor da valvula. 1-AbreValvula 2-FechaValvula
} Data;

Data dados;

// Fim das declarações.. inicio das 

int mili(int milisec){
  struct timespec req = {0};
  req.tv_sec = 0;
  req.tv_nsec = milisec * 1000000L;
  nanosleep(&req, (struct timespec *)NULL);

  return 1;  
}

void chamar(char *str,int valor,int qtd,char *print){
  int find=0;
  
  
  if(strcmp(str,"testaConexao")==0)
  {
    strcat(print,"OK!");
    find=1;
  }
  if(strcmp(str,"setPeriodoSimulacao")==0)
  {
    per_sim = valor;
    sprintf(print,"%s%d!",print,per_sim);
    find=1;
  }
  if(strcmp(str,"setConsumo")==0)
  {
    dados.consumo = valor;
    sprintf(print,"%s%d!",print,dados.consumo);
    find=1;
  }
  if(strcmp(str,"iniciaSimulacao")==0)
  {
    simulacao=1;
    strcat(print,"OK!");
    find=1;
  }
  if(strcmp(str,"abreValvula")==0)
  {
    //valvula += valor;
    dados.valor = valor;
    dados.atualizar = 1;
    sprintf(print,"%s%d!",print,valvula);
    find=1;
  }
  if(strcmp(str,"fechaValvula")==0)
  {
    //valvula -= valor;
    dados.valor = valor;
    dados.atualizar = 2;
    sprintf(print,"%s%d!",print,valvula);
    find=1;
  }
  if(strcmp(str,"getNivel")==0)
  {
      sprintf(print,"%s%d!",print,nivel);
      find=1;
  }
  if(!find)
  {
      strcat(print,"Comando inválido!");
  } 
}

void ident(char *str,char *print){
  int i = 0,j=0,flag_qtd=0,valor;
  char param[25],func[25];
  
  strcpy(print,"");		//Limpa string 'print'
  
  while(str[i]!='\0'){
    if(str[i]=='!')
    {
      param[j]='\0';
      if(flag_qtd){
	valor=atoi(param);
      }
      else
      strcpy(func,param);
	chamar(func,valor,flag_qtd,print);
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



// **** N SEI Q Q A FUNCAO OUTANGLE FAZ
double outangle(double t) {
   if(t <= 0) {
     return 50;
    }
    if(t<20000) {
      return (50+t/400);
    }
    if(t<30000) {
      return 100;
    }
    if(t<50000) {
      return (100-(t-30000)/250);
    }
    if(t<70000) {
      return (20 + (t-50000)/1000);
    }
    if(t<100000) {
      return (40+20*cos((t-70000)*2*pi/10000));
    }
    return 100;
}



void error(const char *msg)
{
    perror(msg);
    exit(1);
}


void IPServer(char *port){
     int sockfd, newsockfd, portno,sair=0;
     socklen_t clilen;
     char buffer[256],escrita[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n,m;
     if (strlen(port)<2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(port);
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
	ident(buffer,escrita);
	if(strcmp(buffer,"sair")==0){
	  sair=1;
	  printf("Saindo\n");
	  n = write(newsockfd,"Closing connection",18);
	}
	
	if (n < 0) error("ERROR reading from socket");
	
	n = write(newsockfd,escrita,200);
	if (n < 0) error("ERROR writing to socket");
     }
     close(newsockfd);
     close(sockfd);
}


void *plant(){
  int dT=1, T=0 ,i=0;
  double delta=0, influx, outflux;
  
  //MUTEX ON
  dados.level[0]=0.4;

  //MUTEX OFF
  dados.inangle[0]=0;
  
  //** INICIO LOOP INFINITO**
  while(1){   
   
    for(i=0;i<19;i++){    
      
    //**** INICIO MUTEX1 PLANTA***
      if(dados.atualizar==1) { //Abre Valvula
	delta += (dados.valor); //valor a abrir a valvula
	dados.atualizar=0;
      }
      if(dados.atualizar==2) { //Fecha Valvula
	delta -= (dados.valor); //Valor a fechar a valvula
	dados.atualizar=0;
      }
    //****FIM MUTEX1 PLANTA***
    
      
     mili(10); // Executa a rotina da planta a cada 10ms... 

      if(delta > 0) {
	if(delta < 0.02*dT){
	    dados.inangle[T+1]= dados.inangle[T]+delta;
	    delta = 0;
	} else{
	    dados.inangle[T+1]= dados.inangle[T]+0.02*dT;
	    delta -=  0.02*dT; 
	    }
      }else if(delta < 0){  
	if(delta > -0.02*dT){
	    dados.inangle[T+1]= dados.inangle[T]+delta;
	    delta = 0;
	}else{
	    dados.inangle[T+1]=  dados.inangle[T]-0.02*dT;
	    delta +=  0.02*dT;
	}
      }
         
      t = t+T;
      dados.tempo[i]=t;
      dados.outangle[i]=outangle(t);
      influx = 1*sin(pi/2*dados.inangle[T]/100);
      outflux= (dados.consumo/100)*(dados.level[T]/1.25+0.2)*sin(pi/2*dados.outangle[i]/100); //outangle é uma função...

      //**** INICIO MUTEX2 PLANTA***
      //dados.level[0]=0.4;
      dados.level[T+1]=dados.level[T]+0.00001*dT*(influx-outflux);
      //**** FIM MUTEX2 PLANTA**
    //  printf("%lf %lf %lf %lf \n", dados.level[T], dados.inangle[T], outangle(t), delta);

      T++;
    }

    dados.inangle[0]=dados.inangle[19]; //Reseta o vetor, ultimo valor é o primeiro   
    dados.level[0]=dados.level[19];
    T=0; // Fim do FOR, somente reseta o vetor pra salvar só 20 posições....
    quitevent();  
   }
}

//** FIM LOOP INFINITO*
//dT em miliseconds <=> setPeriodo
//MAX <=> setConsumo
//===================================


void *graph(){ //void *arg){
  Tdataholder *data;
  int i,j=0;
  double time_offset=0;
  
  data = datainit(640,480,55,110,45,0,0);
/*
  for (t=0;t<55;t+=0.1) {
    datadraw(data,t,(double)(50+20*cos(t/5)),(double)(70+10*sin(t/10)),(double)(20+5*cos(t/2.5)));
  }*/
  
  while(1){
    for(j=0;j<20;j+=5){
      mili(50);
      for(i=j;i<(j+5);i++){
	//printf("%d \n", dados.level[i]);
	datadraw(data,dados.tempo[i],dados.level[i],dados.outangle[i],dados.inangle[i]);  //dados.tempo[i]-time_offset,dados.controle[i],dados.valor[i],dados.saida[i]);
	if((dados.tempo[i]-time_offset)>=55){
	  time_offset+=55;
	  data = datainit(640,480,55,110,45,0,0);
	}
      }
      quitevent();
    }
  }
}


int main(int argc, char *argv[])
{
    pthread_t thread_graf, thread_plant;
    //thread ip server..
   // IPServer(argv);
      
    dados.consumo = 50;
    dados.valor = 50;
    dados.atualizar = 1;
    
   // plant();
   // graph();	
    
   
    pthread_create(&thread_graf, NULL, graph, NULL);
    pthread_create(&thread_plant, NULL, plant, NULL);
  
      
    pthread_join(thread_graf, NULL);
    pthread_join(thread_plant, NULL);

    exit(0);
    
    
     
    //thread do grafico
}
