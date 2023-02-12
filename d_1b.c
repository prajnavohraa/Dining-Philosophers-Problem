#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t forks[5];
sem_t mutex;

//helper functions
int left_fork(int p){
    return p;
}

int right_fork(int p){
    return (p+1)%5;
}

//pick fork
void * pick_fork(void *p){
    //while(1){
        int philosopher=*(int *)p;
        sem_wait(&mutex);
        printf("Philosopher %d has bowl\n", philosopher);
        if(philosopher==4){
            sem_wait(&forks[right_fork(philosopher)]);
            sem_wait(&forks[left_fork(philosopher)]);
        }
        else{
        sem_wait(&forks[left_fork(philosopher)]);
        sem_wait(&forks[right_fork(philosopher)]);
        }
        printf("Philosopher %d is eating\n", philosopher);
        sem_post(&forks[left_fork(philosopher)]);
        sem_post(&forks[right_fork(philosopher)]);
        printf("Philosopher %d has released bowl\n", philosopher);
        sem_post(&mutex);
        printf("Philosoper %d has had his food\n", philosopher);
    //}
}


int main(){
    int phil_array[5]={1,2,3,4,5};
    pthread_t pid[5];
    sem_init(&mutex,0,2);

    for(int i=0; i<5; i++){
        sem_init(&forks[i],0,1);
    }

    for(int i=0; i<5; i++){
        pthread_create(&pid[i], NULL, pick_fork, (void *)&phil_array[i]);
    }

    for(int i=0; i<5; i++){
        pthread_join(pid[i],NULL);
    }
}