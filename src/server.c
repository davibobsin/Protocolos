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

int per_sim = 0;
int max = 50;
int valvula = 0;
int nivel = 100;
int simulacao=0;


typedef struct data_struct {
  double saida[20];
  double controle[20];
  double tempo[20];
  double level[20]; //Nivel do tanque...
  double valor; //valor que vem da comucicacao IP. Valor da abertura da valvula
  int atualizar; //flag para atualizar o valor da valvula. 1-AbreValvula 2-FechaValvula
} Data;

Data dados;

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
    max = valor;
    sprintf(print,"%s%d!",print,max);
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

void Graph(){
  
}

void Plant(){
  int dT=1, T=0 ,i=0;
  double delta=0, inangle[20], outangle[20];
  
  //MUTEX ON
  dados.level[0]=0.4;
  //MUTEX OFF
 
  
  //** INICIO LOOP INFINITO**
  while(1){   
    for(i=0;i<20;i++){ 
     
    mili(10);
      
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
    
   /* 
      if(delta > 0) {
	if(delta < 0.02*dT){
	    in.angle(T+dT)= in.angle(T)+delta
	    delta = 0 
	} else{
	    in.angle(T+dT)=  in.angle(T)+0.02*dT
	    delta -=  0.02*dT 
	    }
      }else if(delta < 0){  
	if(delta > -0.02*dT){
	    in.angle(T+dT)= in.angle(T)+delta
	    delta = 0
	}else{
	    in.angle(T+dT)=  in.angle(T)-0.02*dT
	    delta +=  0.02*dT
	}
      }
    

      influx = 1*sin(pi/2*in.angle/100)
      outflux= (MAX/100)*(level(T)/1.25+0.2)*sin(pi/2*out.angle/100)

      //**** INICIO MUTEX2 PLANTA***
      level(0)=0.4
      level(T+dT)=level(T)+0.00001*dT*(influx-outflux)
      //**** FIM MUTEX2 PLANTA****/
    }
    // in.angle(0)=in.angle(19); //Reseta o vetor, ultimo valor é o primeiro
    
    T=0; // Fim do FOR, somente reseta o vetor pra salvar só 20 posições....

}
//** FIM LOOP INFINITO*



//dT em miliseconds <=> setPeriodo
//MAX <=> setConsumo
//===================================

// **** N SEI Q Q A FUNCAO OUTANGLE FAZ

//   double outangle(double t) {
//     if(t <= 0) {
//       return 50;
//     }
//     if(t<20000) {
//       return (50+t/400);
//     }
//     if(t<30000) {
//       return 100;
//     }
//     if(t<50000) {
//       return (100-(t-30000)/250);
//     }
//     if(t<70000) {
//       return (20 + (t-50000)/1000);
//     }
// 
//     if(t<100000) {
//       return(40+20*cos((t-70000)*2*pi/10000));
//     }
//     return 100;
//   }

}



void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    //thread ip server..
     IPServer(argv[1]);
     
    //Planta
     
    //thread do grafico
}
