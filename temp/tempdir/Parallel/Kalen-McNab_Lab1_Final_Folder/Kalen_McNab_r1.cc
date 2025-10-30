#include <cstddef>
#include <iostream>
#include <pthread.h>
#include <sys/wait.h>
using namespace std;
int jobs_completed=0;
//Creates my threaded queue struct
struct threaded_queue
{
    //Declare my mutex lock and my two conditional values
    pthread_mutex_t mylock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
    //delcares the items my struct has access to
    void enqueue(int x);
    void dequeue();
    int t_queue[10];
    int count;
    //initilizes my condtional and locl
    threaded_queue()
    {
        pthread_mutex_init(&mylock, NULL);
        pthread_cond_init (&not_full, NULL);
        pthread_cond_init (&not_empty, NULL);
    }
    //deconstructer destroys all items once the program finsihes and is killed
    ~ threaded_queue()
    {
    pthread_mutex_destroy(&mylock);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    }
};

void threaded_queue::enqueue(int x)
{
    //sets the lock for enque
    pthread_mutex_lock(&mylock);

    //says while the count is max tell the thread to wait
    while(count==10)
    {
        cout<<"Waiting full\n";
        pthread_cond_wait(&not_full, &mylock);
    }
    //Once it is done waiting put the value in the spot and increment and unlock the lock
    cout<<"inserting "<<x<<endl;
    t_queue[count]=x;
    count++;
    jobs_completed++;
    //We signal that the queue is not longer empty
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mylock);


}

void threaded_queue::dequeue()
{
    //we lock the queue
    pthread_mutex_lock(&mylock);

    while(count==0)
    {
        //we wait while the queue is empty because we cannot remove while there is nothing
        cout<<"Waiting empty\n";
        pthread_cond_wait(&not_empty, &mylock);
    }
    count--;
    int l=t_queue[0];
    cout<<"Removing "<<l<<endl;
    for(int k=0;k<count;k++)
    {
        t_queue[k]=t_queue[k+1];

    }
    jobs_completed++;
    //We then signal not full that there is space in the queue
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mylock);

}

void *consumer_test(void *t)
{
    //We create a pointer to the class queue
    threaded_queue* con = (threaded_queue*)t;

    for(int k=0;k<15;k++)
    {
        con->dequeue();

    }
    //exit the thread
    pthread_exit(NULL);

}

void *producer_test(void *t)
{
    //create a pointer to the class queue
    threaded_queue* pro = (threaded_queue*)t;

    for(int k=0;k<15;k++)
    {
        pro->enqueue(k);
    }
    pthread_exit(NULL);
}

int main()
{

    //create an instance of the class threaded queue
    struct threaded_queue r1;
    //we set the count to 0
    r1.count=0;
    //we make the thread variable
    pthread_t threads[4];

    //we create the threads and send them to the functions
    pthread_create(&threads[0], NULL, producer_test,(void *)&r1);
    pthread_create(&threads[1], NULL, consumer_test,(void *)&r1);
    pthread_create(&threads[2], NULL, producer_test,(void *)&r1);
    pthread_create(&threads[3], NULL,consumer_test,(void *) &r1);

    //we join all the threads back together
    for(int k=0;k<4;k++)
        pthread_join(threads[k], NULL);
    //we printout how many jobs were completed this also a debugging step to make sure all jobs
    // are registered
    std::cout<<"Jobs Completed "<<jobs_completed<<endl;

    return 0;

}
