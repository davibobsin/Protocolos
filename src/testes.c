

typedef struct data_struct {
  double saida[20];
  double controle[20];
  double valor[20];
  double tempo[20];
} Data;

double t=0;
Data dados;


int mili(int milisec){
  struct timespec req = {0};
  req.tv_sec = 0;
  req.tv_nsec = milisec * 1000000L;
  nanosleep(&req, (struct timespec *)NULL);

  return 1;  
}

void simul(){
  int i,j=0;
  
  for(i=0;i<2000;i++){
    t+=0.01;
    dados.tempo[j] = t;
    dados.controle[j] = (double)(50+20*cos(t/5));
    dados.valor[j] = (double)(70+10*sin(t/10));
    dados.saida[j] = (double)(20+5*cos(t/2.5));
    mili(10);
    j++;
    if(j>=20)j=0;
  }
}

int main( int argc, const char* argv[] ) {
   pthread_t thread_id;
   pthread_create(&thread_id, NULL, graph, NULL);
   pthread_create(&thread_id, NULL, simul, NULL);
   
   pthread_join(thread_id, NULL);
   exit(0);
}