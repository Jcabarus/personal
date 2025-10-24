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

pthread_mutex_t lock_flag = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t wait_flag;

// auto job_time =  chrono::high_resolution_clock::now();
// auto job_end =chrono::high_resolution_clock::now();
// auto duration_execution = duration_cast<milliseconds>(job_end - job_time);

int j10[10]={0};
int j20[20]={0};
int j50[50]={0};
int j100[100]={0};
int j250[250]={0};
int j1000[1000]={0};
int jobs_done=0;

void set_arrays()
{
    int num = 1;
    for(int k = 0;k < 10;k++)
    {
        j10[k] = num;
        if(5 == num)
            num=0;
        num++;
    }

    for(int k=0;k<20;k++)
    {
        j20[k]=num;
        if(5==num)
            num=0;
        num++;
    }

    for(int k=0;k<50;k++)
    {
        j50[k]=num;
        if(5==num)
            num=0;
        num++;
    }

    for(int k=0;k<100;k++)
    {
        j100[k]=num;
        if(5==num)
            num=0;
        num++;
    }

    for(int k=0;k<250;k++)
    {
        j250[k]=num;
        if(5==num)
            num=0;
        num++;
    }

    for(int k=0;k<1000;k++)
    {
        j1000[k]=num;
        if(5==num)
            num=0;
        num++;
    }
}

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
    jobs_done++;
}

void add()
{
    int total=0;
    int length=10000;

    for(int k=1;k<=length;k++)
    {
        total+=k;
    }
    jobs_done++;
}

void num_rand()
{
    int rand_num=rand() % 1000 + 1;
    jobs_done++;
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
    jobs_done++;
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
    jobs_done++;
}

void run_10(thread_info &thread_info)
{
    pthread_mutex_lock(&lock_flag);
    for(int k=0;k<10;k++)
    {
        if(1==j10[k])
        hash_gen();
        else if(2==j10[k])
        add();
        else if(3==j10[k])
        num_rand();
        else if(4==j10[k])
        power();
        else if(5==j10[k])
        loop_prime();
        // thread_info.thread_job_counter++;
    }
    pthread_mutex_unlock(&lock_flag);
}

void run_20(thread_info &thread_info)
{
    pthread_mutex_lock(&lock_flag);
    for(int k=0;k<20;k++)
    {
        if(1==j20[k])
            hash_gen();
        else if(2==j20[k])
            add();
        else if(3==j20[k])
            num_rand();
        else if(4==j20[k])
            power();
        else if(5==j20[k])
            loop_prime();
        // thread_info.thread_job_counter++;
    }
    pthread_mutex_unlock(&lock_flag);
}

void run_50(thread_info &thread_info)
{
    pthread_mutex_lock(&lock_flag);
    for(int k=0;k<50;k++)
    {
        if(1==j50[k])
        hash_gen();
        else if(2==j50[k])
        add();
        else if(3==j50[k])
        num_rand();
        else if(4==j50[k])
        power();
        else if(5==j50[k])
        loop_prime();
        // thread_info.thread_job_counter++;
    }
     pthread_mutex_unlock(&lock_flag);
}

void run_100(thread_info &thread_info)
{
     pthread_mutex_lock(&lock_flag);
    for(int k=0;k<100;k++)
    {
        if(1==j100[k])
        hash_gen();
        else if(2==j100[k])
        add();
        else if(3==j100[k])
        num_rand();
        else if(4==j100[k])
        power();
        else if(5==j100[k])
        loop_prime();
        // thread_info.thread_job_counter++;
    }
     pthread_mutex_unlock(&lock_flag);
}

void run_250(thread_info &thread_info)
{
     pthread_mutex_lock(&lock_flag);
    for(int k=0;k<250;k++)
    {
        if(1==j100[k])
        hash_gen();
        else if(2==j100[k])
        add();
        else if(3==j100[k])
        num_rand();
        else if(4==j100[k])
        power();
        else if(5==j100[k])
        loop_prime();
        // thread_info.thread_job_counter++;
    }
     pthread_mutex_unlock(&lock_flag);
}

void run_1000(thread_info &thread_info)
{
    pthread_mutex_lock(&lock_flag);
    for(int k=0;k<1000;k++)
    {
        if(1==j1000[k])
        hash_gen();
        else if(2==j1000[k])
        add();
        else if(3==j1000[k])
        num_rand();
        else if(4==j1000[k])
        power();
        else if(5==j1000[k])
        loop_prime();
        // thread_info.thread_job_counter++;
    }
    pthread_mutex_unlock(&lock_flag);
}

void *work_1(void* arg)
{
    thread_info info;
    initialize_thread_info(info, *(int *) arg, "work_1");

    auto job_time=chrono::high_resolution_clock::now();
    run_10(info);
    auto job_end=chrono::high_resolution_clock::now();

    auto job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout << "1 thread for 10 Jobs took ms: "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_20(info);
    job_end=chrono::high_resolution_clock::now();

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"1 thread for 20 Jobs took ms: "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_50(info);
    job_end=chrono::high_resolution_clock::now();

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"1 thread for 50 Jobs took ms: "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_100(info);
    job_end=chrono::high_resolution_clock::now();


    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"1 thread for 100 Jobs took ms: "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_250(info);
    job_end=chrono::high_resolution_clock::now();


    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"1 thread for 250 Jobs took ms: "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_1000(info);
    job_end=chrono::high_resolution_clock::now();

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"1 thread for 1000 Jobs took ms: "<< job_execution.count()<<endl;

    // thread_result(info);

    pthread_exit(NULL);
}

void *work_2(void * arg)
{
    thread_info info;
    initialize_thread_info(info, *(int *) arg, "work_2");

    if(info.thread_id == 2001)
    {
        auto job_time=chrono::high_resolution_clock::now();
        run_10(info);
        auto job_end=chrono::high_resolution_clock::now();
        pthread_barrier_wait(&wait_flag);
        auto job_execution=duration_cast<milliseconds>(job_end - job_time);
        cout<<"2 thread for 10 Jobs took "<< job_execution.count()<<endl;
    }


    if(info.thread_id == 2002)
    {
        auto job_time=chrono::high_resolution_clock::now();
        run_20(info);
        auto job_end=chrono::high_resolution_clock::now();
        pthread_barrier_wait(&wait_flag);
        auto job_execution=duration_cast<milliseconds>(job_end - job_time);
        cout<<"2 thread for 20 Jobs took "<< job_execution.count()<<endl;
    }

    if(info.thread_id == 2001)
    {
        auto job_time=chrono::high_resolution_clock::now();
        run_50(info);
        auto job_end=chrono::high_resolution_clock::now();
        pthread_barrier_wait(&wait_flag);
        auto job_execution=duration_cast<milliseconds>(job_end - job_time);
        cout<<"2 thread for 50 Jobs took "<< job_execution.count()<<endl;
    }

    if(info.thread_id == 2002)
    {
        auto job_time=chrono::high_resolution_clock::now();
        run_100(info);
        auto job_end=chrono::high_resolution_clock::now();
        pthread_barrier_wait(&wait_flag);
        auto job_execution=duration_cast<milliseconds>(job_end - job_time);
        cout<<"2 thread for 100 Jobs took "<< job_execution.count()<<endl;
    }

    if(info.thread_id == 2001)
    {
        auto job_time=chrono::high_resolution_clock::now();
        run_250(info);
        auto job_end=chrono::high_resolution_clock::now();
        pthread_barrier_wait(&wait_flag);
        auto job_execution=duration_cast<milliseconds>(job_end - job_time);
        cout<<"2 thread for 250 Jobs took "<< job_execution.count()<<endl;
    }

    if(info.thread_id == 2002)
    {
        auto job_time=chrono::high_resolution_clock::now();
        run_1000(info);
        auto job_end=chrono::high_resolution_clock::now();
        pthread_barrier_wait(&wait_flag);
        auto job_execution=duration_cast<milliseconds>(job_end - job_time);
        cout<<"2 thread for 1000 Jobs took "<< job_execution.count()<<endl;
    }

    pthread_mutex_lock(&lock_flag);
    thread_result(info);
    pthread_mutex_unlock(&lock_flag);

    pthread_exit(NULL);
}

void *work_4(void * arg)
{
    thread_info info;
    initialize_thread_info(info, *(int *) arg, "work_4");

    auto job_time=chrono::high_resolution_clock::now();
    run_10(info);
    auto job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    auto job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"4 thread for 10 Jobs took "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_20(info);
    job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"4 thread for 20 Jobs took "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_50(info);
    job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"4 thread for 50 Jobs took "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_100(info);
    job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"4 thread for 100 Jobs took "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_250(info);
    job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"4 thread for 250 Jobs took "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_1000(info);
    job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"4 thread for 1000 Jobs took "<< job_execution.count()<<endl;

    // pthread_mutex_lock(&lock_flag);
    // thread_result(info);
    // pthread_mutex_unlock(&lock_flag);

    pthread_exit(NULL);
}

void *work_8(void * arg)
{
    thread_info info;
    initialize_thread_info(info, *(int *) arg, "work_8");

    auto job_time=chrono::high_resolution_clock::now();
    run_10(info);
    auto job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    auto job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"8 thread for 10 Jobs took "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_20(info);
    job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"8 thread for 20 Jobs took "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_50(info);
    job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"8 thread for 50 Jobs took "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_100(info);
    job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"8 thread for 100 Jobs took "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_250(info);
    job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"8 thread for 250 Jobs took "<< job_execution.count()<<endl;

    job_time=chrono::high_resolution_clock::now();
    run_1000(info);
    job_end=chrono::high_resolution_clock::now();

    pthread_barrier_wait(&wait_flag);

    job_execution=duration_cast<milliseconds>(job_end - job_time);
    cout<<"8 thread for 1000 Jobs took "<< job_execution.count()<<endl;

    // pthread_mutex_lock(&lock_flag);
    // thread_result(info);
    // pthread_mutex_unlock(&lock_flag);

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

    // set_arrays();

    // Thread 1 Execution
    // auto whole_start_time = chrono::high_resolution_clock::now();

    // pthread_create(&thread_1, NULL, work_1, &id_thread_1);
    // pthread_join(thread_1, NULL);

    // auto whole_end_time = chrono::high_resolution_clock::now();
    // auto duration_execution = duration_cast<milliseconds>(whole_end_time - whole_start_time);

    // cout << "-----------------------------" << endl;
    // cout << "              Jobs Completed: " <<jobs_done << endl;
    // cout << "1 Thread execution time (ms): " << duration_execution.count() << endl;;
    // cout << "-----------------------------" << endl;
    // jobs_done=0;
    // set_arrays();

    // // Thread 2 Execution
    pthread_barrier_init(&wait_flag, NULL, 2);

    auto whole_start_time = chrono::high_resolution_clock::now();

    for(int k=0;k<2;k++)
    {
        pthread_create(&thread_2[k], NULL, work_2, &id_thread_2);
    }

    for(int k=0;k<2;k++)
    {
        pthread_join(thread_2[k], NULL);
    }

    pthread_barrier_destroy(&wait_flag);

    auto whole_end_time = chrono::high_resolution_clock::now();
    auto duration_execution = duration_cast<milliseconds>(whole_end_time - whole_start_time);

    cout << "-----------------------------" << endl;
    cout << "-------Jobs Completed-------:" <<jobs_done << endl;
    cout << "2 Threads execution time (ms):" << duration_execution.count() << endl;
    cout << "-----------------------------" << endl;
    jobs_done=0;
    set_arrays();

    // // Thread 4 Execution
    // pthread_barrier_init(&wait_flag, NULL, 4);

    // whole_start_time = chrono::high_resolution_clock::now();
    // for(int k=0;k<4;k++)
    // {
    //     pthread_create(&thread_4[k], NULL, work_4, &id_thread_4);
    // }

    // for(int k=0;k<4;k++)
    // {
    //     pthread_join(thread_4[k], NULL);
    // }

    // pthread_barrier_destroy(&wait_flag);

    // whole_end_time = chrono::high_resolution_clock::now();
    // duration_execution = duration_cast<milliseconds>(whole_end_time - whole_start_time);

    // cout << "-----------------------------" << endl;
    // cout << "-------Jobs Completed-------:" <<jobs_done << endl;
    // cout << "4 Threads execution time (ms):" << duration_execution.count() << endl;
    // cout << "-----------------------------" << endl;
    // jobs_done=0;
    // set_arrays();

    //Thread 8
    // pthread_barrier_init(&wait_flag, NULL, 8);

    // whole_start_time=chrono::high_resolution_clock::now();

    // for(int k=0;k<8;k++)
    // {
    //     pthread_create(&thread_8[k], NULL, work_8, &id_thread_8);
    // }

    // for(int k=0;k<8;k++)
    // {
    //     pthread_join(thread_8[k], NULL);
    // }

    // pthread_barrier_destroy(&wait_flag);

    // whole_end_time = chrono::high_resolution_clock::now();
    // duration_execution = duration_cast<milliseconds>(whole_end_time - whole_start_time);

    // cout << "-----------------------------" << endl;
    // cout << "-------Jobs Completed-------:" <<jobs_done << endl;
    // cout << "8 Threads execution time (ms):" << duration_execution.count() << endl;
    // cout << "-----------------------------" << endl;

    // cout<<"Yay test works"<<endl;

    return 0;
}
