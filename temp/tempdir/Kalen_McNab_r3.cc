#include "CSC718/pthread/pthread/pthread_barrier_compat.h"
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <ctime>
using namespace std;
using namespace chrono;

pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t mybarrier;
int jobs_10=10;
int jobs_20=20;
int jobs_50=50;
int jobs_100=100;
int jobs_250=250;
int jobs_1000=1000;

int t_1[6];
int t_2[6];
int t_4[6];
int t_8[6];


void hash_gen()
{

}

void add()
{
    int total=0;
    int length=rand()%1000 + 250;
    for(int k=1;k<=length;k++)
        total+=k;

}

void num_rand()
{
    int rand_num=rand()%1000+1;
}

void loop_prime()
{
    int prime_total=0;
    int length=rand()%1000 + 2;
    for(int z=2;z<=length/2;z++)
        if(length%z!=0)
            prime_total+=z;


}

void power()
{
    int p, total=0;
    int length=rand()%100 + 1;
    for(int k=1;k<=length;k++)
    {
        p=2*k;
        total+=p;
    }
}




void run_10()
{
    for(int k=0;k<jobs_10;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
    }
}

void run_20()
{
    for(int k=0;k<jobs_20;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
    }

}

void run_50()
{
    for(int k=0;k<jobs_50;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
    }


}

void run_100()
{

    hash_gen();
    add();
    num_rand();
    power();
    loop_prime();

}

void run_250()
{
    for(int k=0;k<jobs_250;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
    }

}

void run_1000()
{
    for(int k=0;k<jobs_1000;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
    }

}


void *tester_1(void * id)
{
    run_10();
    run_20();
    run_50();
    run_100();
    run_250();
    run_1000();
    pthread_exit(NULL);
}


void *tester_2(void * id)
{
    auto start_time = chrono::high_resolution_clock::now();
    run_10();
    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::microseconds>(stop_time-start_time);
    int ret=pthread_barrier_wait(&mybarrier);
    //if(ret==PTHREAD_BARRIER_SERIAL_THREAD)
        cout<<"2 Threads 10 jobs MS: "<<duration.count()<<endl;

    start_time = chrono::high_resolution_clock::now();
    run_20();
     stop_time = chrono::high_resolution_clock::now();
     duration = duration_cast<chrono::microseconds>(stop_time-start_time);
    // pthread_barrier_wait(&mybarrier);
     ret=pthread_barrier_wait(&mybarrier);
     //if(ret==PTHREAD_BARRIER_SERIAL_THREAD)
         cout<<"2 Threads 20 jobs MS: "<<duration.count()<<endl;



    start_time = chrono::high_resolution_clock::now();
    run_50();
     stop_time = chrono::high_resolution_clock::now();
      duration = duration_cast<chrono::microseconds>(stop_time-start_time);
   // pthread_barrier_wait(&mybarrier);
    ret=pthread_barrier_wait(&mybarrier);
    //if(ret==PTHREAD_BARRIER_SERIAL_THREAD)
        cout<<"2 Threads 50 jobs MS: "<<duration.count()<<endl;


    start_time = chrono::high_resolution_clock::now();
    run_100();
     stop_time = chrono::high_resolution_clock::now();
     duration = duration_cast<chrono::microseconds>(stop_time-start_time);
    //pthread_barrier_wait(&mybarrier);
    ret=pthread_barrier_wait(&mybarrier);
    //if(ret==PTHREAD_BARRIER_SERIAL_THREAD)
        cout<<"2 Threads 100 jobs MS: "<<duration.count()<<endl;


    start_time = chrono::high_resolution_clock::now();
    run_250();
     stop_time = chrono::high_resolution_clock::now();
      duration = duration_cast<chrono::microseconds>(stop_time-start_time);
    //pthread_barrier_wait(&mybarrier);
    ret=pthread_barrier_wait(&mybarrier);
    //if(ret==PTHREAD_BARRIER_SERIAL_THREAD)
        cout<<"2 Threads 250 jobs MS: "<<duration.count()<<endl;


    start_time = chrono::high_resolution_clock::now();
    run_1000();
     stop_time = chrono::high_resolution_clock::now();
     duration = duration_cast<chrono::microseconds>(stop_time-start_time);
    //pthread_barrier_wait(&mybarrier);
    ret=pthread_barrier_wait(&mybarrier);
    //if(ret==PTHREAD_BARRIER_SERIAL_THREAD)
        cout<<"2 Threads 1000 jobs MS: "<<duration.count()<<endl;

     pthread_exit(NULL);
}


void *tester_4(void * id)
{
    run_10();
    run_20();
    run_50();
    run_100();
    run_250();
    run_1000();
    pthread_exit(NULL);
}


void *tester_8(void * id)
{
    run_10();
    run_20();
    run_50();
    run_100();
    run_250();
    run_1000();
     pthread_exit(NULL);
}




int main()
{
    srand(time(NULL));

    // ID assignment
    int id_thread_1=1111;
    int id_thread_2=2221;
    int id_thread_4=4441;
    int id_thread_8=8881;

    pthread_t thread_1[1];
    pthread_t thread_2[2];
    pthread_t thread_4[4];
    pthread_t thread_8[8];

    pthread_create(&thread_1[0], NULL, tester_1, (void *) id_thread_1);
    pthread_join(thread_1[0],NULL);


    pthread_barrier_init(&mybarrier, NULL,2);
    for(int k=0;k<2;k++)
    {
        pthread_create(&thread_2[k], NULL, tester_2, (void *) id_thread_2);
        id_thread_2++;
    }
    pthread_barrier_destroy(&mybarrier);
    for(int k=0;k<2;k++)
        pthread_join(thread_2[k], NULL);

    for(int k=0;k<4;k++)
    {
        pthread_create(&thread_4[k], NULL, tester_4, (void *) id_thread_4);
        id_thread_4++;
    }
    for(int k=0;k<4;k++)
        pthread_join(thread_4[k], NULL);

    for(int k=0;k<8;k++)
    {
        pthread_create(&thread_8[k], NULL, tester_8, (void *) id_thread_8);
        id_thread_8++;
    }
    for(int k=0;k<8;k++)
        pthread_join(thread_8[k], NULL);



    cout<<"Yay test works"<<endl;
    return 0;
}
