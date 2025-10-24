#include <iostream>
#include <pthread.h>
#include <chrono>
#include <thread>
using namespace std;

pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full=PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty=PTHREAD_COND_INITIALIZER;
bool full=false;
int fill_many=0;
int remove_many=0;
 int total;
void *producer(void* arg)
{

    this_thread::sleep_for(chrono::seconds(5));
    pthread_mutex_lock(&mylock);
    int *array = (int*) arg;
    while(full)
    {
        pthread_cond_wait(&not_full, &mylock);
    }
    for(int k=0;k<fill_many;k++)
    {
        array[k]=k;
        //usleep(5);
    }

    full=true;
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mylock);
    pthread_exit(NULL);
}

void *consumer(void* arg)
{
    int sum=0;
    pthread_mutex_lock(&mylock);
    int *array = (int *) arg;
    while(!full)
    {
        cout<<"Waiting"<<endl;
        pthread_cond_wait(&not_empty, &mylock);
        cout<<"Exiting wait"<<endl;
    }
    if(remove_many>total)
        remove_many=total;
    for(int k=0;k<remove_many;k++)
    {
        //cout<<array[k]<<" "<<k<<" "<<endl;
        //for(int l=0;l<total;l++)
          //  cout<<"Current Array "<<array[l]<<" ";
        cout<<endl;
        sum=sum+array[0];
        total--;
        for(int z=0;z<total;z++)
            array[z]=array[z+1];
    }
    if(total!=0)
        for(int k=0;k<total;k++)
            cout<<"Current array "<<array[k]<<endl;
    //6-3 = 3 array[6] array[0-2] = array [3-5]
    full=false;
    cout<<sum<<endl;
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mylock);
    pthread_exit(NULL);
}

int main()
{
    //int fill_many=0;
    //int remove_many=0;
    cin>>fill_many;
    while(fill_many<=0)
        cin>>fill_many;
    cin>>remove_many;
    while(remove_many<=0)
        cin>>remove_many;
    int array[fill_many];
    total=fill_many;
    //int* arg=(int*) array[fill_many];
    pthread_t thread[2];

    pthread_create(&thread[0], NULL, &producer, &array);
    pthread_create(&thread[1], NULL, &consumer, &array);
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    return 0;
}
