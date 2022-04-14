/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpazhaid
 *
 * Created on February 16, 2022, 8:17 AM
 */

#include  <stdio.h> /* printf */
#include  <sys/types.h> /* pid_t */
#include <unistd.h> /* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h>  /* wait */
#include <pthread.h>
#include <sys/stat.h>



void * count(void *);
int globalNumber = 0;
//Create a mutex
pthread_mutex_t mutex1;

int main(void) {
    int i;
    pthread_t counterThread[5];
    
    pthread_mutex_init(&mutex1, NULL);
    
    pthread_create(&counterThread[0], NULL, count, NULL);
    pthread_create(&counterThread[1], NULL, count, NULL);
    pthread_create(&counterThread[2], NULL, count, NULL);
    pthread_create(&counterThread[3], NULL, count, NULL);
    pthread_create(&counterThread[4], NULL, count, NULL);
    
    pthread_join(counterThread[0], NULL);
    pthread_join(counterThread[1], NULL);
    pthread_join(counterThread[2], NULL);
    pthread_join(counterThread[3], NULL);
    pthread_join(counterThread[4], NULL);
    //Create the 5 threads
    //Wait for all treads to finish
    pthread_mutex_destroy(&mutex1);
    return (0);
}

void * count(void * junk) {
    int loopCount = 0;
    pthread_mutex_lock(&mutex1);
    while (loopCount < 10) {
        int tmpNumber = globalNumber;
        printf("counter: %d, Thread: %ld, PID: %d\n",
                tmpNumber, pthread_self(), getpid());
        tmpNumber = globalNumber;
        tmpNumber++;
        usleep(random() % 2);
        globalNumber = tmpNumber;
        loopCount++;
    }
    pthread_mutex_unlock(&mutex1);
    return (0);
}
