#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *teclado(void *arg);
void *imprime(void *arg);

main()
{
     pthread_t thread1, thread2;
     const char *message1 = "Thread 1";
     const char *message2 = "Thread 2";
     int  iret1, iret2;

    /* Create independent threads each of which will execute function */
      system("clear");
     iret1 = pthread_create( &thread1, NULL, teclado, NULL);
     if(iret1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
         exit(EXIT_FAILURE);
     }

     iret2 = pthread_create( &thread2, NULL, imprime, NULL);
     if(iret2)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
         exit(EXIT_FAILURE);
     }

     //printf("pthread_create() for thread 1 returns: %d\n",iret1);
     //printf("pthread_create() for thread 2 returns: %d\n",iret2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 
SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Missing file","File is missing. Please reinstall the program.",NULL);
    exit(EXIT_SUCCESS);
}

void *teclado(void *arg)
{
  char a;
  int j;	
  system ("/bin/stty raw");
  for (j=0;j<5;j++){
    printf("%c",'a');
    fflush(stdin);
  }
}

void *imprime(void *arg)
{
  int i;
  for(i=0;i<12;i++){
    printf("%d",i);
    sleep(1);
  }
}
