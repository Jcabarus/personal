#include "CSC718/pthread/pthread/pthread_barrier_compat.h"
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

pthread_mutex_t lock_flag=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t wait_flag;

struct thread_info // Degugging information, delete later
{
    int thread_id;
    int thread_job_counter;
    string remarks;
};

void initialize_thread_info(thread_info& thread_info, int& thread_id, string remarks) // Degugging information, delete later
{
    thread_id++;

    thread_info.thread_id = thread_id;
    thread_info.remarks = remarks;
}

void thread_result(thread_info& thread_info) // Degugging information, delete later
{
    cout << endl;
    cout << "Thread ID: " <<thread_info.thread_id << endl;
    cout << "|    Jobs ran: " <<thread_info.thread_job_counter << endl;
    cout << "|    Remarks: " <<thread_info.remarks << endl;
}

void hash_gen()
{
    // cout < "hash_gen()" << endl;
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
    int rand_num=10000;
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

void run_10(thread_info &thread_info) // Degugging information: thread_info &thread_info, delete later
{
    for(int k=0;k<10;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++; // Degugging information, delete later
    }
}

void run_20(thread_info &thread_info) // Degugging information: thread_info &thread_info, delete later
{
    for(int k=0;k<20;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++; // Degugging information, delete later
    }
}

void run_50(thread_info &thread_info) // Degugging information: thread_info &thread_info, delete later
{
    for(int k=0;k<50;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++; // Degugging information, delete later
    }
}

void run_100(thread_info &thread_info) // Degugging information: thread_info &thread_info, delete later
{
    for(int k=0;k<100;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++; // Degugging information, delete later
    }
}

void run_250(thread_info &thread_info) // Degugging information: thread_info &thread_info, delete later
{
    for(int k=0;k<250;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++; // Degugging information, delete later
    }
}

void run_1000(thread_info &thread_info) // Degugging information: thread_info &thread_info, delete later
{
    for(int k=0;k<1000;k++)
    {
        hash_gen();
        add();
        num_rand();
        power();
        loop_prime();
        thread_info.thread_job_counter++; // Degugging information, delete later
    }
}

void *work_1(void* arg)
{
    thread_info info; // Degugging information, delete later
    initialize_thread_info(info, *(int *) arg, "work_1");

    run_10(info);
    run_20(info);
    run_50(info);
    run_100(info);
    run_250(info);
    run_1000(info);

   thread_result(info); // Degugging information, delete later

    pthread_exit(NULL);
}

void *work_2(void * arg)
{
    thread_info info; // Degugging information, delete later
    initialize_thread_info(info, *(int *) arg, "work_2");
    
    // cout << info.thread_id << "is executing run_10" << endl; // Degugging information, delete later
    run_10(info);
    // cout << info.thread_id << "is done executing, now waiting" << endl; // Degugging information, delete later

    pthread_barrier_wait(&wait_flag);
    
    // cout << info.thread_id << "is executing run_20" << endl; // Degugging information, delete later
    run_20(info);
    // cout << info.thread_id << "is done executing, now waiting" << endl; // Degugging information, delete later

    pthread_barrier_wait(&wait_flag);
    
    // cout << info.thread_id << "is executing run_50" << endl; // Degugging information, delete later
    run_50(info);
    // cout << info.thread_id << "is done executing, now" << endl; // Degugging information, delete later

    pthread_barrier_wait(&wait_flag);

    // cout << info.thread_id << "is executing run_100" << endl; // Degugging information, delete later
    run_100(info);
    // cout << info.thread_id << "is done executing, now waiting" << endl; // Degugging information, delete later
    
    pthread_barrier_wait(&wait_flag);
    
    // cout << info.thread_id << "is executing run_250" << endl; // Degugging information, delete later
    run_250(info);
    // cout << info.thread_id << "is done executing, now waiting" << endl; // Degugging information, delete later

    pthread_barrier_wait(&wait_flag);
    
    // cout << info.thread_id << "is executing run_1000" << endl; // Degugging information, delete later
    run_1000(info);
    // cout << info.thread_id << "is done executing, now waiting" << endl; // Degugging information, delete later

    pthread_barrier_wait(&wait_flag); // Degugging information, delete later

    pthread_mutex_lock(&lock_flag); // Degugging information, delete later
    thread_result(info); // Degugging information, delete later
    pthread_mutex_unlock(&lock_flag); // Degugging information, delete later

    pthread_exit(NULL);
}

void *work_4(void * arg)
{
    thread_info info; // Degugging information, delete later
    initialize_thread_info(info, *(int *) arg, "work_4"); // Degugging information, delete later
    
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
    
    pthread_mutex_lock(&lock_flag); // Degugging information, delete later
    thread_result(info); // Degugging information, delete later
    pthread_mutex_unlock(&lock_flag); // Degugging information, delete later

    pthread_exit(NULL);
}

void *work_8(void * arg)
{
    thread_info info; // Degugging information, delete later
    initialize_thread_info(info, *(int *) arg, "work_8"); // Degugging information, delete later
    
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

    pthread_mutex_lock(&lock_flag); // Degugging information, delete later
    thread_result(info); // Degugging information, delete later
    pthread_mutex_unlock(&lock_flag); // Degugging information, delete later

    pthread_exit(NULL);
}

int main()
{
    // srand(time(NULL));

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
    auto start_time = chrono::high_resolution_clock::now(); // Degugging information, delete later

    pthread_create(&thread_1, NULL, work_1, &id_thread_1);
    pthread_join(thread_1, NULL);
    
    auto end_time = chrono::high_resolution_clock::now(); // Degugging information, delete later
    auto duration_execution = duration_cast<milliseconds>(end_time - start_time); // Degugging information, delete later

    cout << "-----------------------------" << endl;
    cout << "1 Thread execution time (ms):" << duration_execution.count() << endl;;
    cout << "-----------------------------" << endl;
    
    
    // Thread 2 Execution
    pthread_barrier_init(&wait_flag, NULL, 2);
    
    start_time = chrono::high_resolution_clock::now(); // Degugging information, delete later
    for(int k=0;k<2;k++)
    {
        pthread_create(&thread_2[k], NULL, work_2, &id_thread_2);
    }
    
    for(int k=0;k<2;k++)
    {
        pthread_join(thread_2[k], NULL);
    }

    pthread_barrier_destroy(&wait_flag);
    
    end_time = chrono::high_resolution_clock::now(); // Degugging information, delete later
    duration_execution = duration_cast<milliseconds>(end_time - start_time); // Degugging information, delete later
    
    cout << "-----------------------------" << endl;
    cout << "2 Threads execution time (ms):" << duration_execution.count() << endl; // Degugging information, delete later
    cout << "-----------------------------" << endl;
    
    // Thread 4 Execution
    pthread_barrier_init(&wait_flag, NULL,4);
    
    start_time = chrono::high_resolution_clock::now(); // Degugging information, delete later
    for(int k=0;k<4;k++)
    {
        pthread_create(&thread_4[k], NULL, work_4, &id_thread_4);
    }
    
    for(int k=0;k<4;k++)
    {
        pthread_join(thread_4[k], NULL);
    }

    pthread_barrier_destroy(&wait_flag);

    end_time = chrono::high_resolution_clock::now(); // Degugging information, delete later
    duration_execution = duration_cast<milliseconds>(end_time - start_time); // Degugging information, delete later

    cout << "-----------------------------" << endl;
    cout << "4 Threads execution time (ms):" << duration_execution.count() << endl; // Degugging information, delete later
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
    
    end_time = chrono::high_resolution_clock::now(); // Degugging information, delete later
    duration_execution = duration_cast<milliseconds>(end_time - start_time); // Degugging information, delete later

    cout << "-----------------------------" << endl;
    cout << "8 Threads execution time (ms):" << duration_execution.count() << endl; // Degugging information, delete later
    cout << "-----------------------------" << endl;

    cout<<"Yay test works"<<endl;

    return 0;
}
