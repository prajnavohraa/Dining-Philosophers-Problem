#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
 
sem_t dining;
sem_t forks[5];
int phil_state[5];

//sates
//1 -> thinking
//2 -> Eating

//helper functions
int left_fork(int p){
    return p;
}

int right_fork(int p){
    return (p+1)%5;
}

void check_to_eat(int p){
    if (phil_state[p]==1 && (phil_state[left_fork(p)]!=2 && phil_state[right_fork(p)]!= 2)) {
        phil_state[p]=2;
    }
}


void get_fork(int p){
    check_to_eat(p);
    sem_post(&forks[p]);
    sem_post(&dining);
    sem_wait(&forks[p]);
}
 

void put_fork(int p){
    printf("Philosopher %d has finished eating\n", p);
    check_to_eat(left_fork(p));
    sem_post(&forks[left_fork(p)]);
    check_to_eat(right_fork(p));
    sem_post(&forks[right_fork(p)]);
    sem_post(&dining);
}
 
void * dining_philosopher(void* p){
    //while (1) {
        int philosopher=*(int *)p;
        sem_wait(&dining);
        sleep(1);
        phil_state[philosopher]=1;
        printf("Philosopher %d is thinking\n", philosopher);
        get_fork(philosopher);
        sleep(1);
        printf("Philosopher %d has bowl\n", philosopher);
        printf("Philosopher %d is Eating\n", philosopher);
        sem_wait(&dining);
        phil_state[philosopher]=1;
        put_fork(philosopher);
    //}
}
 
int main(){
    pthread_t pid[5];
    int phil_array[5]={0,1,2,3,4};
    sem_init(&dining, 0, 2);
    for (int i=0; i<5; i++)
        sem_init(&forks[i], 0, 0);

    for (int i=0; i<5; i++) {
        pthread_create(&pid[i], NULL, dining_philosopher, &phil_array[i]);
    }
    for (int i=0; i<5;i++)
        pthread_join(pid[i], NULL);
}