#include <iostream>
#include <pthread.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <stdlib.h>
using namespace std;

#define JOBS 15

pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mywait=PTHREAD_COND_INITIALIZER;
int jobs_completed=0;
int num_threads=5;
int jobs[JOBS];
bool ready=false;
int total=0;
int rand_add;
int rand_sub;
int rand_mult;
void add_jobs()
{
    int done=0;
    int count=1;
    for(int k=0;k<JOBS;k++)
    {
        jobs[k]=count;
        if(count==4)
            count=0;
        count++;
    }
    pthread_mutex_lock(&mylock);
    pthread_cond_broadcast(&mywait);
    ready=true;
    pthread_mutex_unlock(&mylock);
    //pthread_cond_broadcast(&mywait);
    while(true)
    {
        for(int z=0;z<JOBS;z++)
            if(jobs[z]==0)
            {
                done++;
                if(done==JOBS)
                    return;
            }
            else
            {
                done=0;
                break;
            }
    }
}

void add()
{
    //pthread_mutex_lock(&mylock);
    rand_add=rand() % 101;
    total=total-rand_add;
    jobs_completed++;
    //pthread_mutex_unlock(&mylock);
 //   pthread_exit(NULL);
}

void substract()
{
    //pthread_mutex_lock(&mylock);
    rand_sub=rand() % 101;
    total=total-rand_sub;
    jobs_completed++;
    //pthread_mutex_unlock(&mylock);
//    pthread_exit(NULL);

}

void grab_sys_time()
{
    auto timenow=chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout<<ctime(&timenow)<<endl;
    //pthread_mutex_lock(&mylock);
    jobs_completed++;
    //pthread_mutex_unlock(&mylock);
    //pthread_exit(NULL);
}

void multiplication()
{
    //pthread_mutex_lock(&mylock);
    rand_mult=rand() % 101;
    total=total*rand_mult;
    jobs_completed++;
    //pthread_mutex_unlock(&mylock);
    //pthread_exit(NULL);

}

void *master(void *t)
{
    add_jobs();
    cout<<"Master done"<<endl;
   // pthread_mutex_lock(&mylock);
    //pthread_cond_broadcast(&mywait);
    //pthread_mutex_unlock(&mylock);

    pthread_exit(NULL);
}

void *workers(void *t)
{
    int zero_count=0;
    pthread_mutex_lock(&mylock);
    while(!ready)
        pthread_cond_wait(&mywait,&mylock);
    pthread_mutex_unlock(&mylock);
    for(int k=0;k<JOBS;k++)
    {
        pthread_mutex_lock(&mylock);
        if(1==jobs[k])
        {
            //pthread_mutex_lock(&mylock);
            zero_count=0;
            add();
            jobs[k]=0;
            //pthread_mutex_unlock(&mylock);
        }
        else if(2==jobs[k])
        {
             //pthread_mutex_lock(&mylock);
             zero_count=0;
             substract();
             jobs[k]=0;
            //pthread_mutex_unlock(&mylock);
        }
        else if(3==jobs[k])
        {
            //pthread_mutex_lock(&mylock);
             zero_count=0;
             grab_sys_time();
             jobs[k]=0;
             //pthread_mutex_unlock(&mylock);
        }
        else if(4==jobs[k])
        {
             //pthread_mutex_lock(&mylock);
             zero_count=0;
             multiplication();
             jobs[k]=0;
             //pthread_mutex_unlock(&mylock);
        }
        /*
         *
        else
        {
            //pthread_mutex_lock(&mylock);
            zero_count++;
        }
         */
        if(jobs_completed>=JOBS)
            {
                cout<<"Exiting Workers"<<endl;
                zero_count=0;
                pthread_mutex_unlock(&mylock);
                pthread_exit(NULL);
            }
        pthread_mutex_unlock(&mylock);
    }
}

int main()
{
    //pthread_mutex_t mylock;
    //pthread_mutex_init(&mylock, NULL);
    pthread_t threads[num_threads];

    auto start_time = chrono::high_resolution_clock::now();
    //int total=0;
    //time_t start,end;
    //time(&start);



    pthread_create(&threads[0], NULL, master, (void *) 0);

    pthread_create(&threads[1], NULL, workers, (void *) 1);
    pthread_create(&threads[2], NULL, workers, (void *) 2);
    pthread_create(&threads[3], NULL, workers, (void *) 3);
    pthread_create(&threads[4], NULL, workers, (void *) 4);




/*
 *
    for(long i=0; i < num_threads; i++){
        pthread_create(&threads[i], NULL, workers, (void *) i);
    }
 */

    /*
     *
    while(true)
    {
        //The threads get created and the master assigns tasks to the workers


        //Main threads waits for the jobs to be completed before running again
        for(int k=0;k<num_threads;k++)
            pthread_join(threads[k], NULL);
    }
     */
     //cout<<"Here"<<endl;
     for(int k=0;k<num_threads;k++)
         pthread_join(threads[k], NULL);
    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::milliseconds>(stop_time-start_time);
    // time(&end);
     //time_t duration=end-start;
     //float average_job= (float)duration/jobs_completed;
     cout<<"Total: "<<total<<endl;
     cout<<"Jobs Completed: "<<jobs_completed<<endl;
    cout<<"Total Time MS: "<<duration.count()<<endl;
    double average_job = static_cast<double>(duration.count())/jobs_completed;
     cout<<"Average Job Time: "<<average_job<<endl;

     pthread_mutex_destroy(&mylock);
    return 0;
}
