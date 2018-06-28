#include "bib_graf.c"
#include <pthread.h>

typedef struct data_struct {
  double saida[20];
  double controle[20];
  double valor[20];
  double tempo[20];
} Data;

Data dados;
double t=0;

int mili(int milisec){
  struct timespec req = {0};
  req.tv_sec = 0;
  req.tv_nsec = milisec * 1000000L;
  nanosleep(&req, (struct timespec *)NULL);

  return 1;  
}

void *graph(void *arg){
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
	datadraw(data,dados.tempo[i]-time_offset,dados.controle[i],dados.valor[i],dados.saida[i]);
	if((dados.tempo[i]-time_offset)>=55){
	  time_offset+=55;
	  data = datainit(640,480,55,110,45,0,0);
	}
      }
      quitevent();
    }
  }
}

void simul(){
  int i,j;
  for(j=0;j<500;j++){
    for(i=0;i<20;i++){
      t += 0.01; 
      dados.tempo[i] = t;
      dados.controle[i] = (double)(50+20*cos(dados.tempo[i]/5));
      dados.valor[i] = (double)(70+10*sin(dados.tempo[i]/10));
      dados.saida[i] = (double)(20+5*cos(dados.tempo[i]/2.5));
      mili(10);
    }
  }
}

int main( int argc, const char* argv[] ) {
   pthread_t thread_graf, thread_simul;
   
   pthread_create(&thread_graf, NULL, graph, NULL);
   pthread_create(&thread_simul, NULL, simul, NULL);
   
   pthread_join(thread_graf, NULL);
   pthread_join(thread_simul, NULL);
   exit(0);
}