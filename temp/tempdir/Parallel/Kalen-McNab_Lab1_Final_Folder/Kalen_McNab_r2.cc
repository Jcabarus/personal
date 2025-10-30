#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <stdlib.h>
using namespace std;

//This sets the word JOBS to 15 which is used for our array
#define JOBS 15
//These next three lines create and initialize our lock mylock and our two conditonal variables
// mywait which is used to make the worker thread wait until the jobs are ready
// job_done is used to make the master wait until the worker threads are done
pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mywait=PTHREAD_COND_INITIALIZER;
pthread_cond_t job_done=PTHREAD_COND_INITIALIZER;

//This variable is used for keeping track of our jobs getting completed
int jobs_completed=0;
//This variable is for saying how many total threads we are going to have
int num_threads=5;
//This sets the size of array jobs to JOBS making the size 15
int jobs[JOBS];
//This creates a bool called ready false which is used to make the worker threads wait
bool ready=false;
//This is used to keep track of the running total in our math functions
int total=0;
//These next three variables are used in our math functions for holding random generated numbers
int rand_add;
int rand_sub;
int rand_mult;
//This variable is used for worker threads to keep track of how many have exited
int t_workers=0;
//Used to keep track of our current spot in the array when assigning jobs
int current_index=0;

void add_jobs()
{
    //This creates the variable count which is used for setting spots in our array to specific numbers
    int count=1;
    //This for loop loops through our array setting spots to count
    for(int k=0;k<JOBS;k++)
    {
        jobs[k]=count;
        //one count hits 4 it is reset to 0 then is incremented to 1
        if(count==4)
            count=0;
        count++;
    }
    pthread_mutex_lock(&mylock);
    //We then send a broadcast message to our worker threads that their jobs are ready and
    // they can begin working
    pthread_cond_broadcast(&mywait);
    //we set ready to true
    ready=true;
    //This make our master thread wait until it is signaled by the worker threads that they are done
    while(jobs_completed!=JOBS)
    {
        //master thread waits until it is signal by the workers that it is done
        pthread_cond_wait(&job_done, &mylock);
    }

    pthread_mutex_unlock(&mylock);
}

void add()
{
    //generates a random number
    rand_add=rand() % 101;
    pthread_mutex_lock(&mylock);
    //this locks adds it to the total and increments jobs complete
    total=total+rand_add;
    jobs_completed++;
    pthread_mutex_unlock(&mylock);
}

void substract()
{
    //generates random number
    rand_sub=rand() % 101;
    pthread_mutex_lock(&mylock);
    //locks instance subtracts from total and increments job complete
    total=total-rand_sub;
    jobs_completed++;
    pthread_mutex_unlock(&mylock);
}

void grab_sys_time()
{
    //This grabs current system time
    auto timenow=chrono::system_clock::to_time_t(chrono::system_clock::now());
    cout<<ctime(&timenow)<<endl;
    pthread_mutex_lock(&mylock);
    //locks instance and increments jobs complete
    jobs_completed++;
    pthread_mutex_unlock(&mylock);
}

void multiplication()
{
    //generates random number
    rand_mult=rand() % 101;
    pthread_mutex_lock(&mylock);
    //locks instance and multiplies the total and increments job complete
    total=total*rand_mult;
    jobs_completed++;
    pthread_mutex_unlock(&mylock);
}

void *master(void *t)
{
    //sends the master thread to add jobs and once returned prints out that the master finished
    add_jobs();
    cout<<"Master done"<<endl;
    pthread_exit(NULL);
}


void *workers(void *t)
{
    int j;
    //This lock and while ready if false the worker threads wait till they are singal that they can run
    pthread_mutex_lock(&mylock);
    while(!ready)
        pthread_cond_wait(&mywait,&mylock);
    pthread_mutex_unlock(&mylock);
    //This loop runs until all workers are finished
    while(true)
    {
        //marker is used to alert when threads are
        // If the if statement is bypass then it hits the other if statement and breaks
        int marker=-1;

        pthread_mutex_lock(&mylock);
        if(current_index<JOBS)
        {
            //If we still have jobs to run we set marker to current_index
            // j to the number in the array
            // set the array spot to 0 to signfy that the job is taken
            // and increment current index
            marker=current_index;
            j=jobs[marker];
            jobs[marker]=0;
            current_index++;
        }
        pthread_mutex_unlock(&mylock);

        if(marker==-1)
        {
            //This is used as another variable used in conjuction with jobs complete to send a signal
            // to the master thread
           t_workers++;
            break;
        }
        //The numbers from the array call specific functions
        // 1 is addtion
        // 2 is subtract
        // 3 is multiplication
        // 4 is grab sys time
        else if(1==j)
            add();
        else if(2==j)
            substract();
        else if(3==j)
            multiplication();
        else if(4==j)
            grab_sys_time();

    }
    cout<<"Exiting Workers"<<t<<endl;
    //Once this condition is meant the pthread signal alerts the master wake up
    if(t_workers==4 && jobs_completed==JOBS)
        pthread_cond_signal(&job_done);
    pthread_exit(NULL);
}


int main()
{
    //Sets are threads to the number of threads we specify
    pthread_t threads[num_threads];
    //Starts clock that keeps track of how long the program runs
    auto start_time = chrono::high_resolution_clock::now();
    //Sends master thread to the master function
    pthread_create(&threads[0], NULL, master, (void *) 0);

    //Creates the worker threads
    pthread_create(&threads[1], NULL, workers, (void *) 1);
    pthread_create(&threads[2], NULL, workers, (void *) 2);
    pthread_create(&threads[3], NULL, workers, (void *) 3);
    pthread_create(&threads[4], NULL, workers, (void *) 4);

    //Joins all threads back together
     for(int k=0;k<num_threads;k++)
         pthread_join(threads[k], NULL);
     //Stops the clock and grabs how long the program ran
    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::milliseconds>(stop_time-start_time);

    //Prints out the total, jobs completed, total time in millisecondsm and average time per job
     cout<<"Total: "<<total<<endl;
     cout<<"Jobs Completed: "<<jobs_completed<<endl;
    cout<<"Total Time MS: "<<duration.count()<<endl;
    double average_job = static_cast<double>(duration.count())/jobs_completed;
     cout<<"Average Job Time: "<<average_job<<endl;

     pthread_mutex_destroy(&mylock);
    return 0;
}
