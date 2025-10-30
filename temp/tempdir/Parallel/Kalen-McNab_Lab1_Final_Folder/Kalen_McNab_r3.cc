#include "pthread_barrier_compat.h"
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <random>
#include <cstdint>
using namespace std;
using namespace std::chrono;

//pre set the timers for timing job execution
 auto job_time =  chrono::high_resolution_clock::now();
 auto job_end =chrono::high_resolution_clock::now();
 auto duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);


//This if for a thread delcaration later t_x corresponds to how many threads each has
int t_1=1;
int t_2=2;
int t_4=4;
int t_8=8;
//Set JOBS_X to their corresponding value
int JOBS_10=10;
int JOBS_20=20;
int JOBS_50=50;
int JOBS_100=100;
int JOBS_250=250;
int JOBS_1000=1000;

//This creates our jobs arrays
int j10[10];
int j20[20];
int j50[50];
int j100[100];
int j250[250];
int j1000[1000];

//creates a barrier called mybarrier
pthread_barrier_t mybarrier;

//creates a string of characters used for generating a random string for later use in hashing
string characters="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

//creates and intilizes the lock and condtional value
pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t yowait=PTHREAD_COND_INITIALIZER;
//Creates a bool called ready and sets it to false used in the job creation to prevent threads
// from starting jobs early
bool ready=false;

//Job fill used to fill the job arrays with numbers that correspond to different functions
void job_fill()
{
    //These loops are all the same all that changes in length they run based on JOBS_X
    // each value corresponds to a function
    // 1 = hash_gen
    // 2 = add
    // 3 = num_rand
    // 4 = power
    // 5 = loop_prime
    int num=1;
    for(int k=0;k<JOBS_10;k++)
    {
        j10[k]=num;
        if(num==5)
            num=0;
        num++;
    }
    num=1;
    for(int k=0;k<JOBS_20;k++)
    {
        j20[k]=num;
        if(num==5)
            num=0;
        num++;
    }
    num=1;
    for(int k=0;k<JOBS_50;k++)
    {
        j50[k]=num;
        if(num==5)
            num=0;
        num++;
    }
    num=1;
    for(int k=0;k<JOBS_100;k++)
    {
        j100[k]=num;
        if(num==5)
            num=0;
        num++;
    }
    num=1;
    for(int k=0;k<JOBS_250;k++)
    {
        j250[k]=num;
        if(num==5)
            num=0;
        num++;
    }
    num=1;
    for(int k=0;k<JOBS_1000;k++)
    {
        j1000[k]=num;
        if(num==5)
            num=0;
        num++;
    }

}

//Hash_gen creates a string from the string on characters and hashes it
void hash_gen()
{
    hash <string> hashed;
    random_device random_device;
    mt19937 generator(random_device());
    string gen_string(characters);
    hashed(gen_string);

}

//add creates a local total and add to it from 1<=10000 this is simply a test as by making
// it do larger numbers it takes more time
void add()
{
    int total=0;
    int length=10000;

    for(int k=1;k<=length;k++)
    {
        total+=k;
    }

}

//num_rand generates a random number between 1-1000
void num_rand()
{
    int rand_num=rand() % 1000 + 1;

}

//loop prime loops 10000 time trying to find a prime number everytime it finds a prime
// it increments it
void loop_prime()
{
    int prime_total=0;
    int length=10000;

    for(int z=2;z<=length/2;z++)
    {
        if(length%z!=0)
        {
            prime_total+=z;
        }
    }

}

//power takes 2 to the power of k and adds it to the local total
void power()
{
    int p, total=0;
    int length=10000;

    for(int k=1;k<=length;k++)
    {
        p=pow(2, k);
        total+=p;
    }

}

//Run 10 runs threads with 10 jobs
void run_10()
{
    int job;
    for(int k=0;k<10;k++)
    {
          //This allocates a number from the array to the thread
        pthread_mutex_lock(&mylock);
            if(j10[k]!=0)
            {
                job=j10[k];
                j10[k]=0;
            }
        pthread_mutex_unlock(&mylock);

        if(1==job)
        hash_gen();
        else if(2==job)
        add();
        else if(3==job)
        num_rand();
        else if(4==job)
        power();
        else if(5==job)
        loop_prime();

    }

}

//run_20 runs threads with 20 jobs
void run_20()
{
   int job;
    for(int k=0;k<20;k++)
    {
          //This allocates a number from the array to the thread
        pthread_mutex_lock(&mylock);
            if(j20[k]!=0)
            {
                job=j20[k];
                j20[k]=0;
            }
        pthread_mutex_unlock(&mylock);

        if(1==job)
            hash_gen();
        else if(2==job)
            add();
        else if(3==job)
            num_rand();
        else if(4==job)
            power();
        else if(5==job)
            loop_prime();

    }

}

//run_50 runs threads with 50 jobs
void run_50()
{
    int job;

    for(int k=0;k<50;k++)
    {
          //This allocates a number from the array to the thread
        pthread_mutex_lock(&mylock);
            if(j50[k]!=0)
            {
                job=j50[k];
                j50[k]=0;
            }
        pthread_mutex_unlock(&mylock);
        if(1==job)
        hash_gen();
        else if(2==job)
        add();
        else if(3==job)
        num_rand();
        else if(4==job)
        power();
        else if(5==job)
        loop_prime();

    }

}

//run_100 runs threads with 100 jobs
void run_100()
{
    int job;

    for(int k=0;k<100;k++)
    {
          //This allocates a number from the array to the thread
        pthread_mutex_lock(&mylock);
            if(j100[k]!=0)
            {
                job=j100[k];
                j100[k]=0;
            }
        pthread_mutex_unlock(&mylock);

        if(1==job)
        hash_gen();
        else if(2==job)
        add();
        else if(3==job)
        num_rand();
        else if(4==job)
        power();
        else if(5==job)
        loop_prime();

    }
}

//run_250 runs threads with 250 jobs
void run_250()
{
    int job;
    for(int k=0;k<250;k++)
    {
          //This allocates a number from the array to the thread
        pthread_mutex_lock(&mylock);
            if(j250[k]!=0)
            {
                job=j250[k];
                j250[k]=0;
            }
        pthread_mutex_unlock(&mylock);

        if(1==job)
        hash_gen();
        else if(2==job)
        add();
        else if(3==job)
        num_rand();
        else if(4==job)
        power();
        else if(5==job)
        loop_prime();

    }
}

//run_1000 runs threads with 1000 jobs
void run_1000()
{
    int job;
    for(int k=0;k<1000;k++)
    {
        //This allocates a number from the array to the thread
        pthread_mutex_lock(&mylock);
            if(j1000[k]!=0)
            {
                job=j1000[k];
                j1000[k]=0;
            }
        pthread_mutex_unlock(&mylock);
        if(1==job)
        {
            hash_gen();
        }
        else if(2==job)
        {
            add();

        }
        else if(3==job)
        {
            num_rand();

        }
        else if(4==job)
        {
            power();

        }
        else if(5==job)
        {
            loop_prime();

        }

    }
}

//test for 1 thread
void *tester1(void * id)
{
    //makes the worker wait till the jobs are ready
    pthread_mutex_lock(&mylock);
        while(!ready)
            pthread_cond_wait(&yowait, &mylock);
    pthread_mutex_unlock(&mylock);
    //times 10 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_10();
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
   cout<<"1 thread with 10 jobs took MS: "<<duration_execution.count()<<endl;
 //times 20 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_20();
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    cout<<"1 thread with 20 jobs took MS: "<<duration_execution.count()<<endl;

     //times 50 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_50();
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    cout<<"1 thread with 50 jobs took MS: "<<duration_execution.count()<<endl;
     //times 100 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_100();
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    cout<<"1 thread with 100 jobs took MS: "<<duration_execution.count()<<endl;

     //times 250 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_250();
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    cout<<"1 thread with 250 jobs took MS: "<<duration_execution.count()<<endl;

     //times 1000 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_1000();
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    cout<<"1 thread with 1000 jobs took MS: "<<duration_execution.count()<<endl;
    pthread_exit(NULL);

}

//test function for 2 threads
void *tester2(void * id)
{
     //makes the worker wait till the jobs are ready
    pthread_mutex_lock(&mylock);
        while(!ready)
            pthread_cond_wait(&yowait, &mylock);
    pthread_mutex_unlock(&mylock);

     //times 10 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_10();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"2 thread with 10 jobs took MS: "<<duration_execution.count()<<endl;

 //times 20 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_20();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"2 thread with 20 jobs took MS: "<<duration_execution.count()<<endl;

     //times 50 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_50();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"2 thread with 50 jobs took MS: "<<duration_execution.count()<<endl;

     //times 100 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_100();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"2 thread with 100 jobs took MS: "<<duration_execution.count()<<endl;

    //times 250 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_250();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"2 thread with 250 jobs took MS: "<<duration_execution.count()<<endl;

    //times 1000 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_1000();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"2 thread with 1000 jobs took MS: "<<duration_execution.count()<<endl;



    pthread_exit(NULL);

}

//Test function for 4 threads
void *tester4(void * id)
{
     //makes the worker wait till the jobs are ready
    pthread_mutex_lock(&mylock);
        while(!ready)
            pthread_cond_wait(&yowait, &mylock);
    pthread_mutex_unlock(&mylock);

     //times 10 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_10();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"4 thread with 10 jobs took MS: "<<duration_execution.count()<<endl;

    //times 20 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_20();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"4 thread with 20 jobs took MS: "<<duration_execution.count()<<endl;

    //times 50 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_50();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"4 thread with 50 jobs took MS: "<<duration_execution.count()<<endl;

    //times 100 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_100();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"4 thread with 100 jobs took MS: "<<duration_execution.count()<<endl;

    //times 250 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_250();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"4 thread with 250 jobs took MS: "<<duration_execution.count()<<endl;

    //times 1000 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_1000();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"4 thread with 1000 jobs took MS: "<<duration_execution.count()<<endl;



    pthread_exit(NULL);

}

//test function for 8 threads
void *tester8(void * id)
{
    //makes the worker wait till the jobs are ready
    pthread_mutex_lock(&mylock);
        while(!ready)
            pthread_cond_wait(&yowait, &mylock);
    pthread_mutex_unlock(&mylock);

    //times 10 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_10();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"8 thread with 10 jobs took MS: "<<duration_execution.count()<<endl;



    //times 20 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_20();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"8 thread with 20 jobs took MS: "<<duration_execution.count()<<endl;



    //times 50 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_50();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"8 thread with 50 jobs took MS: "<<duration_execution.count()<<endl;



    //times 100 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_100();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"8 thread with 100 jobs took MS: "<<duration_execution.count()<<endl;



    //times 250 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_250();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"8 thread with 250 jobs took MS: "<<duration_execution.count()<<endl;



    //times 1000 jobs in milliseconds
    job_time=chrono::high_resolution_clock::now();
    run_1000();
    pthread_barrier_wait(&mybarrier);
    job_end=chrono::high_resolution_clock::now();
    duration_execution = duration_cast<chrono::milliseconds>(job_end - job_time);
    if(id==0)
        cout<<"8 thread with 1000 jobs took MS: "<<duration_execution.count()<<endl;




    pthread_exit(NULL);
}



int main()
{
    //sets thread_1 to t_1
    pthread_t thread_1[t_1];
    int num=0;
    //creates thread 1 and sends it to tester 1
    pthread_create(&thread_1[0], NULL, tester1, (void *) 0);
    //locks the lock calls job fill, sets ready to true and signals the worker thread can run
    pthread_mutex_lock(&mylock);
    job_fill();
    ready=true;
    pthread_cond_broadcast(&yowait);
    pthread_mutex_unlock(&mylock);

    //Joins thread_1
    pthread_join(thread_1[0], NULL);

    //sets ready to false for job_fill
    ready=false;

    //sets thread_2 equal to t_2
    pthread_t thread_2[t_2];
    //creates a barrier and sets it equal to two threads
    pthread_barrier_init(&mybarrier, NULL, 2);
    for(int k=0;k<t_2;k++)
    {
        //creates thread_2
         pthread_create(&thread_2[k], NULL, tester2, (void *) num);
         num++;
    }
    //Debug Statement
    //cout<<"Got through thread 1"<<endl;
    //  //locks the lock calls job fill, sets ready to true and signals the worker thread can run
    pthread_mutex_lock(&mylock);
    job_fill();
    ready=true;
    pthread_cond_broadcast(&yowait);
    pthread_mutex_unlock(&mylock);

    num=0;
    for(int k=0;k<t_2;k++)
    {
        //Joins the threads together
        pthread_join(thread_2[k],NULL);
    }
    //destroys the barrier
    pthread_barrier_destroy(&mybarrier);
    //sets ready to false
    ready=false;
    //debug statement
    //cout<<"Got through thread 2"<<endl;
    //Set thread_4 equal t_4
    pthread_t thread_4[t_4];
    //creates the new barrier for 4 threads
    pthread_barrier_init(&mybarrier, NULL, 4);
    for(int k=0;k<t_4;k++)
    {
        //creates the new 4 threads
         pthread_create(&thread_4[k], NULL, tester4, (void *) num);
         num++;
    }
    //fixes the job queues and singals the worker threads to work
    pthread_mutex_lock(&mylock);
    job_fill();
    ready=true;
    pthread_cond_broadcast(&yowait);
    pthread_mutex_unlock(&mylock);
    num=0;
    for(int k=0;k<t_4;k++)
    {
        //joins the threads together
        pthread_join(thread_4[k],NULL);
    }
    //destroys the barrier
    pthread_barrier_destroy(&mybarrier);
    //sets the bool back to false
    ready=false;
    //debug statement
    //cout<<"Got through thread 4"<<endl;

    //sets thread_8 equal to t_8
    pthread_t thread_8[t_8];
    //Creates a barrier for 8 threads
    pthread_barrier_init(&mybarrier, NULL, 8);
    for(int k=0;k<t_8;k++)
    {
        //creates the new threads
         pthread_create(&thread_8[k], NULL, tester8, (void *) num);
         num++;
    }
    //fixes the bob arrays back to their orginal value and signal the workers that they can work
    pthread_mutex_lock(&mylock);
    job_fill();
    ready=true;
    pthread_cond_broadcast(&yowait);
    pthread_mutex_unlock(&mylock);



    for(int k=0;k<t_8;k++)
    {
        //joins the threads togther
        pthread_join(thread_8[k],NULL);
    }
    pthread_barrier_destroy(&mybarrier);
    //Debug statement
    //cout<<"Got through thread 8"<<endl;
    return 0;
}
