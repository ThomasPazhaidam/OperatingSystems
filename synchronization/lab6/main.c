/**
 *
 * COE 628 - Operating Systems
 * Lab 6
 * Thomas Pazhaidam
 **/
// if not already compiled run: (wont build in netbeans)
// gcc -pthread -o main main.c
// else if the main executable is already in folder you can just run it
#include <stdlib.h>     /* NULL */
#include  <stdio.h>	/* printf */
#include  <sys/types.h>	/* pid_t */
#include <unistd.h>	/* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h> 	/* wait */
#include <pthread.h>

#define PRODUCER_NO 5	//Number of producers, can change here
#define NUM_PRODUCED 20 //2000 //Number of items to be produced, can change here

void *generator_function(void*);
void *print_function(void*);
long sum; /* Sum of generated values*/
long finished_producers; /* number of the producer that finished producing */

//C: Mutex declaration and initialization
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
 

//F: Condition variable declaration and initialization
pthread_cond_t condition= PTHREAD_COND_INITIALIZER;

int main(void) {
    int i;
    /* initialize random seed: */
    srand(time(NULL));
    sum = 0;
    finished_producers=0;
    
    //A: Creates five generator thread
    int treturn[PRODUCER_NO];
    pthread_t thread[PRODUCER_NO];
    pthread_t tprint;
    
    treturn[0]=pthread_create(&thread[0],NULL,generator_function,NULL);
    treturn[2]=pthread_create(&thread[1],NULL,generator_function,NULL);
    treturn[3]=pthread_create(&thread[2],NULL,generator_function,NULL);
    treturn[4]=pthread_create(&thread[3],NULL,generator_function,NULL);
    treturn[5]=pthread_create(&thread[4],NULL,generator_function,NULL);
    
    //D: Creates print thread
    int printtreturn=pthread_create(&tprint,NULL,print_function,NULL);
    
    //B: Makes sure that all generator threads has finished before proceeding
   pthread_join(thread[0],NULL); 
   pthread_join(thread[1],NULL); 
   pthread_join(thread[2],NULL); 
   pthread_join(thread[3],NULL); 
   pthread_join(thread[4],NULL); 
    //E: Makes sure that print thread has finished before proceeding
   pthread_join(tprint, NULL);
    return (0);

}

void * generator_function(void* junk) {
    pthread_mutex_lock(&mutex1); // lock
    
    long counter = 0;
    long sum_this_generator = 0;
   
    while (counter < NUM_PRODUCED) {

      long tmpNumber = sum;
      long rnd_number = 1;//rand() % 10; 
        // can make = 1, output should be 100 (20 loops*5 threads)
      printf("current sum of the generated number up to now is %ld going to add %ld to it.\n", tmpNumber, rnd_number);
        sum = tmpNumber + rnd_number;
        counter++;
        sum_this_generator += rnd_number;
        usleep(1000);
    }
    
    
    printf("--+---+----+----------+---------+---+--+---+------+----\n");
    printf("The sum of produced items for this number generator at the end is: %ld \n", sum_this_generator);
    printf("--+---+----+----------+---------+---+--+---+------+----\n");
    finished_producers++;
    pthread_mutex_unlock(&mutex1); // unlock
    
    //H: If all generator has finished fire signal for condition variable
   if(finished_producers==PRODUCER_NO)
       pthread_cond_signal(&condition);
    
   return (0);
}

void *print_function(void* junk) {
    //G: Wait until all generator has finished
    pthread_mutex_lock(&mutex1);
    while(finished_producers != PRODUCER_NO)
        pthread_cond_wait(&condition,&mutex1);
    
    
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("The value of counter at the end is: %ld \n", sum);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}