#include "CSC718/pthread/pthread/pthread_barrier_compat.h"
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <ctime>
#include <random>

using namespace std;
using namespace std::chrono;

string characters="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

pthread_mutex_t lock_flag=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t wait_flag;

struct thread_info
{
    int thread_id;
    int thread_job_counter;
    string remarks;
};

void initialize_thread_info(thread_info& thread_info, int& thread_id, string remarks)
{
    thread_id++;

    thread_info.thread_id = thread_id;
    thread_info.remarks = remarks;
}

void thread_result(thread_info& thread_info)
{
    cout << endl;
    cout << "Thread ID: " <<thread_info.thread_id << endl;
    cout << "|    Jobs ran: " <<thread_info.thread_job_counter << endl;
    cout << "|    Remarks: " <<thread_info.remarks << endl;
}

void hash_gen()
{
    hash <string> hashed;
    random_device random_device;
    mt19937 generator(random_device());
    string gen_string(characters);
    hashed(gen_string);

}

void add()
{
    int total=0;
    int length=10000;

    for(int k=1;k<=length;k++)
    {
        total+=k;
    }
}

void num_rand()
{

    int rand_num=rand() % 1000 + 1;
}

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

void power()
{
    int p, total=0;
    int length=10000;

    for(int k=1;k<=length;k++)
    {
        p=2*k;
        total+=p;
    }
}

void run_10(thread_info &thread_info)
{
    for(int k=0;k<10;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++;
    }
}

void run_20(thread_info &thread_info)
{
    for(int k=0;k<20;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++;
    }
}

void run_50(thread_info &thread_info)
{
    for(int k=0;k<50;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++;
    }
}

void run_100(thread_info &thread_info)
{
    for(int k=0;k<100;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++;
    }
}

void run_250(thread_info &thread_info)
{
    for(int k=0;k<250;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++;
    }
}

void run_1000(thread_info &thread_info)
{
    for(int k=0;k<1000;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++;
    }
}

void *work_1(void* arg)
{
    thread_info info;
    initialize_thread_info(info, *(int *) arg, "work_1");

    run_10(info);
    run_20(info);
    run_50(info);
    run_100(info);
    run_250(info);
    run_1000(info);

   thread_result(info);

    pthread_exit(NULL);
}

void *work_2(void * arg)
{
    thread_info info;
    initialize_thread_info(info, *(int *) arg, "work_2");


    run_10(info);
    pthread_barrier_wait(&wait_flag);

    run_20(info);
    pthread_barrier_wait(&wait_flag);

    run_50(info);
    pthread_barrier_wait(&wait_flag);


    run_100(info);
    pthread_barrier_wait(&wait_flag);

    run_250(info);
    pthread_barrier_wait(&wait_flag);


    run_1000(info);
    pthread_barrier_wait(&wait_flag);

    pthread_mutex_lock(&lock_flag);
    thread_result(info);
    pthread_mutex_unlock(&lock_flag);

    pthread_exit(NULL);
}

void *work_4(void * arg)
{
    thread_info info;
    initialize_thread_info(info, *(int *) arg, "work_4");

    run_10(info);
    pthread_barrier_wait(&wait_flag);
    run_20(info);
    pthread_barrier_wait(&wait_flag);
    run_50(info);
    pthread_barrier_wait(&wait_flag);
    run_100(info);
    pthread_barrier_wait(&wait_flag);
    run_250(info);
    pthread_barrier_wait(&wait_flag);
    run_1000(info);

    pthread_barrier_wait(&wait_flag);

    pthread_mutex_lock(&lock_flag);
    thread_result(info);
    pthread_mutex_unlock(&lock_flag);

    pthread_exit(NULL);
}

void *work_8(void * arg)
{
    thread_info info;
    initialize_thread_info(info, *(int *) arg, "work_8");

    run_10(info);
    pthread_barrier_wait(&wait_flag);
    run_20(info);
    pthread_barrier_wait(&wait_flag);
    run_50(info);
    pthread_barrier_wait(&wait_flag);
    run_100(info);
    pthread_barrier_wait(&wait_flag);
    run_250(info);
    pthread_barrier_wait(&wait_flag);
    run_1000(info);

    pthread_barrier_wait(&wait_flag);

    pthread_mutex_lock(&lock_flag);
    thread_result(info);
    pthread_mutex_unlock(&lock_flag);

    pthread_exit(NULL);
}

int main()
{

    srand(time(NULL));
    // Threads
    pthread_t thread_1;
    pthread_t thread_2[2];
    pthread_t thread_4[4];
    pthread_t thread_8[8];

    // ID assignment
    int id_thread_1 = 1000;
    int id_thread_2 = 2000;
    int id_thread_4 = 4000;
    int id_thread_8 = 8000;

    // Thread 1 Execution
    auto start_time = chrono::high_resolution_clock::now();

    pthread_create(&thread_1, NULL, work_1, &id_thread_1);
    pthread_join(thread_1, NULL);

    auto end_time = chrono::high_resolution_clock::now();
    auto duration_execution = duration_cast<milliseconds>(end_time - start_time);

    cout << "-----------------------------" << endl;
    cout << "1 Thread execmution time (ms):" << duration_execution.count() << endl;;
    cout << "-----------------------------" << endl;


    // Thread 2 Execution
    pthread_barrier_init(&wait_flag, NULL, 2);

    start_time = chrono::high_resolution_clock::now();
    for(int k=0;k<2;k++)
    {
        pthread_create(&thread_2[k], NULL, work_2, &id_thread_2);
    }

    for(int k=0;k<2;k++)
    {
        pthread_join(thread_2[k], NULL);
    }

    pthread_barrier_destroy(&wait_flag);

    end_time = chrono::high_resolution_clock::now();
    duration_execution = duration_cast<milliseconds>(end_time - start_time);
    cout << "-----------------------------" << endl;
    cout << "2 Threads execution time (ms):" << duration_execution.count() << endl;
    cout << "-----------------------------" << endl;

    // Thread 4 Execution
    pthread_barrier_init(&wait_flag, NULL,4);

    start_time = chrono::high_resolution_clock::now();
    for(int k=0;k<4;k++)
    {
        pthread_create(&thread_4[k], NULL, work_4, &id_thread_4);
    }

    for(int k=0;k<4;k++)
    {
        pthread_join(thread_4[k], NULL);
    }

    pthread_barrier_destroy(&wait_flag);

    end_time = chrono::high_resolution_clock::now();
    duration_execution = duration_cast<milliseconds>(end_time - start_time);

    cout << "-----------------------------" << endl;
    cout << "4 Threads execution time (ms):" << duration_execution.count() << endl;
    cout << "-----------------------------" << endl;

    //Thread 8
    pthread_barrier_init(&wait_flag, NULL, 8);

    for(int k=0;k<8;k++)
    {
        pthread_create(&thread_8[k], NULL, work_8, &id_thread_8);

    }

    for(int k=0;k<8;k++)
    {
        pthread_join(thread_8[k], NULL);
    }

    pthread_barrier_destroy(&wait_flag);

    end_time = chrono::high_resolution_clock::now();
    duration_execution = duration_cast<milliseconds>(end_time - start_time);
    cout << "-----------------------------" << endl;
    cout << "8 Threads execution time (ms):" << duration_execution.count() << endl;
    cout << "-----------------------------" << endl;

    cout<<"Yay test works"<<endl;

    return 0;
}
