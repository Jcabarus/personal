#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <vector>
#include <iostream>
#include <random>
#include <pthread.h>
// #include "pthread_barrier_compat.h"
using namespace std;
int th_per_row;
int th_per_column;
struct image_thread
{
    int id;
    int height;
    int width;
    int channels;
    int threads;
    pthread_mutex_t lock_flag;
    unsigned char *old_image;
    vector<unsigned char>new_image;

    image_thread()
    {
        pthread_mutex_init(&lock_flag, NULL);

    }
    ~ image_thread()
    {
        pthread_mutex_destroy(&lock_flag);

    }
};

int get_number_of_threads(int width, int height)
{
    int threads;


    //pthead def
    if(height<=480 && width<=640)
        threads=4;
    else if(height<=1280 && width<=720)
        threads=8;
    else if(height<=1920 && width<=1080)
        threads=16;
    else if(height<=2560 && width<=1440)
        threads=32;
    else if(height<=3840 && width<=2160)
        threads=64;
    else
     threads=128;

    return threads;
}
int row_per_thread(int height, int threads)
{
    int per_thread;
    per_thread=height/threads;
    return per_thread;
}

int column_per_thread(int width, int threads)
{
    int per_thread;
    per_thread=width/threads;
    return per_thread;
}

void *gray_image_worker(void *arg)
{
    image_thread* image = (image_thread*)arg;
    unsigned char *old_im=image->old_image;
    int r,g,b,gray;
    int w=image->width,h=image->height,c=image->channels, threa=image->threads;
    vector<unsigned char>im_gray(h*w*c);
    int image_index;
   // for(int j=0;j<threa;j++)
    //{
        //pthread_mutex_lock(&image->lock_flag);
       // for(int k=0;k<h/(threa+1);k++)
       for(int k=0;k<h;k++)
        {
            //for(int l=0;l<w/(threa+1);l++)
            for(int l=0;l<w;l++)
            {
                image_index=(k*w+l)*c;

                r=old_im[image_index+0];
                g=old_im[image_index+1];
                b=old_im[image_index+2];
                gray=0.3*r+0.59*g+0.11*b;
                image->new_image[image_index+0]=(unsigned char)gray;
                image->new_image[image_index+1]=(unsigned char)gray;
                image->new_image[image_index+2]=(unsigned char)gray;
                /*
                 *
                im_gray[image_index+0]=(unsigned char)gray;
                im_gray[image_index+1]=(unsigned char)gray;
                im_gray[image_index+2]=(unsigned char)gray;
                 */

                if(4==c)
                    image->new_image[image_index+3]=old_im[image_index+3];
                 //   im_gray[image_index+3]=old_im[image_index+3];
            }
        }
       // pthread_mutex_unlock(&image->lock_flag);
       //}
    image->new_image=im_gray;
    pthread_exit(NULL);
}


int main(int argc, char * argv[])
{
    //If we do not supply and image the program quits
    if(argc<2)
    {
        cout<<"Did not supply an image"<<endl;
        return 0;
    }
    int flag=0;
    struct image_thread pro_threads;
    int width,height,channels;
    unsigned char *image = stbi_load(argv[1], &width, &height, &channels, 0);
    pro_threads.threads=get_number_of_threads(width, height);
    th_per_column=column_per_thread(width, pro_threads.threads);
    th_per_row=row_per_thread(height, pro_threads.threads);
    pro_threads.new_image.resize(height*width*channels);

    int num_threads,thread_height,thread_width;

    /*
     *
    pro_threads.height=height;
    pro_threads.width=width;
    pro_threads.channels=channels;
    pro_threads.old_image=image;
    pro_threads.threads=get_number_of_threads(width, height);
    cout<<pro_threads.threads<<endl;
     */
    pthread_t thread[pro_threads.threads];
    //vector<unsigned char>new_im(height*width*channels);
    for(int k=0;k<pro_threads.threads;k++)
    {
        if(flag==1)
            pro_threads.width=thread_width*(k+1);
        flag=0;
        pro_threads.height=th_per_row*(k+1);
        pro_threads.id=k;
        pro_threads.height=height;
        pro_threads.width=width;
        pro_threads.channels=channels;
        pro_threads.old_image=image;
        //pro_threads.new_image=new_im;
        pthread_create(&thread[k], NULL, gray_image_worker,(void *)&pro_threads);

        if(pro_threads.height==height)
            pro_threads.height=th_per_row;
        if(pro_threads.width==thread_width)
            pro_threads.height=thread_width;
    }

    for(int k=0;k<pro_threads.threads;k++)
        pthread_join(thread[k], NULL);

    string name;
    name="P-Gray.png";
    if (!stbi_write_png(name.c_str(), width, height, channels, pro_threads.new_image.data(), width * channels)) {
           cout<<"Failed to write PNG\n";
       } else {
           cout<<"Saved: "<<name<<endl;
       }
    return 0;
}
