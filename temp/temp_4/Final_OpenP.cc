#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <vector>
#include <iostream>
#include <random>
#include <pthread.h>
#include "pthread/pthread/pthread_barrier_compat.h"
#include <mpi.h>

using namespace std;

int r_histogram[256]={0},g_histogram[256]={0},b_histogram[256]={0};
int r_sum=0,g_sum=0,b_sum=0;
int r_cdf[256],g_cdf[256],b_cdf[256];
int r_min=0,g_min=0,b_min=0;
int r_lookup_table[256], g_lookup_table[256], b_lookup_table[256];

int num_threads = 4;
pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;;

struct image_thread
{
    int id;
    int height;
    int width;
    int channels;
    int threads;
    int starth;
    int endh;
    int startc;
    int endc;
    unsigned char *old_image;
    unsigned char *new_image;     // pointer to shared output buffer
};

unsigned char* initialize_matrix(int height, int width, int channels)
{
    //creates the psuedo 2-D array by timing x*y
    unsigned char* init_matrix = new unsigned char[height*width*channels];

    return init_matrix;
}
void delete_matrix(unsigned char* matrix)
{
    delete[] matrix;
    matrix = nullptr;
}

void *gray_image_worker(void *arg)
{
    image_thread *image = (image_thread *)arg;

    // made declarations much more readable.
    int w = image->width;
    int h = image->height;
    int c = image->channels;

    int startw = image->startc;
    int endw = image->endc;
    int startr = image->starth;
    int endr = image->endh;

    for(int k=startr;k<endr;k++)
    {
        for(int l=startw;l<endw;l++)
        {

            int image_index = (k*w+l)*c;

            int r = image->old_image[image_index + 0];
            int g = image->old_image[image_index + 1];
            int b = image->old_image[image_index + 2];
            int gray=0.3*r+0.59*g+0.11*b;
            image->new_image[image_index+0]=(unsigned char)gray;
            image->new_image[image_index+1]=(unsigned char)gray;
            image->new_image[image_index+2]=(unsigned char)gray;

            if(4==c)
                image->new_image[image_index+3]=image->old_image[image_index+3];

        }
    }

    pthread_exit(NULL);
}


void *negative_image_worker(void *arg)
{
    image_thread *image = (image_thread *)arg;

    // made declarations much more readable.
    int w = image->width;
    int h = image->height;
    int c = image->channels;

    int startw = image->startc;
    int endw = image->endc;
    int startr = image->starth;
    int endr = image->endh;

    for(int k=startr;k<endr;k++)
    {
        for(int l=startw;l<endw;l++)
        {

            int image_index = (k*w+l)*c;

            int r = image->old_image[image_index + 0];
            int g = image->old_image[image_index + 1];
            int b = image->old_image[image_index + 2];
            r=255-r;
            g=255-g;
            b=255-b;
            image->new_image[image_index+0]=(unsigned char)r;
            image->new_image[image_index+1]=(unsigned char)g;
            image->new_image[image_index+2]=(unsigned char)b;

            if(4==c)
                image->new_image[image_index+3]=image->old_image[image_index+3];

        }
    }

    pthread_exit(NULL);
}

void *color_change(void *arg)
{
    image_thread *image = (image_thread *)arg;

    random_device ran_num;
    mt19937 eng(ran_num());
    uniform_int_distribution<> distr(0, 255);
    int w = image->width;
    int h = image->height;
    int c = image->channels;
    int startw = image->startc;
    int endw = image->endc;
    int startr = image->starth;
    int endr = image->endh;

    int image_index,r,g,b;

    for(int k=startr;k<endr;k++)
    {
        for (int l=startw;l<endw;l++)
        {
            image_index=(k*w+l)*c;

            r=distr(eng);
            g=distr(eng);
            b=distr(eng);

            image->new_image[image_index+0]=(unsigned char)r;
            image->new_image[image_index+1]=(unsigned char)g;
            image->new_image[image_index+2]=(unsigned char)b;

            if(4==c)
                image->new_image[image_index+3]=image->old_image[image_index+3];
        }
    }



    pthread_exit(NULL);
}


void *brightness_transformation(void *arg)
 {
     image_thread *image = (image_thread *)arg;

     int w = image->width;
     int h = image->height;
     int c = image->channels;
     int startw = image->startc;
     int endw = image->endc;
     int startr = image->starth;
     int endr = image->endh;
    //image_index grabs our index from our image where we read the rgb values from
    // r,g,b will hold our images original rgb values
    int image_index,r,g,b,brightness=40;
    for(int k=startr;k<endr;k++)
    {
        for(int l=startw;l<endw;l++)
        {
            //grabs the index of the pixel we are changing
            image_index=(k*w+l)*c;

            //will store the original rgb value from our image
            r=image->old_image[image_index+0];
            g=image->old_image[image_index+1];
            b=image->old_image[image_index+2];

            //will apply the brightness change
            r+=brightness;
            g+=brightness;
            b+=brightness;

            //These if statements apply corrective checing making sure our rgb values stay valid for unsigned chars
            if(r>255)
                r=255;
            if(g>255)
                g=255;
            if(b>255)
                b=255;
            if(r<0)
                r=0;
            if(g<0)
                g=0;
            if(b<0)
                b=0;

            //This will apply our new rgb values to our new image vector
            image->new_image[image_index+0]=(unsigned char)r;
            image->new_image[image_index+1]=(unsigned char)g;
            image->new_image[image_index+2]=(unsigned char)b;

            if(4==c)
                image->new_image[image_index+3]=image->old_image[image_index+3];

        }
    }
    pthread_exit(NULL);
 }

 void *rotate_image(void *arg)
 {
     image_thread *image = (image_thread *)arg;
     int w = image->width;
     int h = image->height;
     int c = image->channels;
     int startw = image->startc;
     int endw = image->endc;
     int startr = image->starth;
     int endr = image->endh;

    int oriIndex,copyIndex,x,y;

    for(int k=startr;k<endr;k++)
    {
        for(int l=startw;l<endw;l++)
        {
            //This will grab the pixel spot we are about to change
            oriIndex=(k*w+l)*c;
            //This will grab new width position we will put the pixel in
            x=w-1-l;
            //This will grab the new height position that we put the pixel in
            y=h-1-k;

            //This is where we grab our new spot to place our pixel in the copy
            copyIndex=(y*w+x)*c;

            //This will loop for how many colors there are in this image and write the pixels to their new location
            for(int m=0;m<c;m++)
                image->new_image[copyIndex+m]=image->old_image[oriIndex+m];
        }
    }
    pthread_exit(NULL);
}


void *blurring_image(void *arg)
 {
     image_thread *image = (image_thread *)arg;
     int w = image->width;
     int h = image->height;
     int c = image->channels;
     int startw = image->startc;
     int endw = image->endc;
     int startr = image->starth;
     int endr = image->endh;

     //Radius of our blur matrix this matrix is a 15x15 so our radius is 15/2
     // The radius tells us how far from the center pixel we look in each direction at ourneighbors
     int radius=7;

     //rgb hold color of the pxiels
     // image_index grabs the pixel of the image we are blurring
     //total_iteration number of our valid neighbors
     // blur_index where we write our blurred pixel to
     int r,g,b,image_index,total_iteration,blur_index;
     //neighrbor coordinates
     int holdx,holdy;

     for(int k=startr;k<endr;k++)
     {
         for(int l=startw;l<endw;l++)
         {
             //Resets values for the new pixel
             r=0,g=0,b=0, total_iteration=0;
             //These next two for loops go through our neighbors scan of our blur matrix which is 15x15
             for(int m=-radius;m<=radius;m++)
            {
                for(int n=-radius;n<=radius;n++)
                {
                    //Holds the result of our neighbor coordinates we find
                    holdx=l+n;
                    holdy=k+m;

                    //Bounds check prevents us from going out of bounds and seg faulting
                    if(holdx<0||holdx>=w||holdy<0||holdy>=h)
                        continue;
                    //computes the pixel index
                    image_index=(holdy*w+holdx)*c;

                    //sums up all of the rgb values
                    r+=image->old_image[image_index+0];
                    g+=image->old_image[image_index+1];
                    b+=image->old_image[image_index+2];

                    //holds how many total pixels were included
                    total_iteration++;

                }
            }
            //finds what spot we put our new blurred pixel in
            blur_index=(k*w+l)*c;

            //computes the new average rgb values we put into the new spot
            image->new_image[blur_index+0]=r/total_iteration;
            image->new_image[blur_index+1]=g/total_iteration;
            image->new_image[blur_index+2]=b/total_iteration;

            //if the image has an alpha channel we copt it into the new spot unchanged
            if(4==c)
                image->new_image[blur_index+3]=image->old_image[blur_index+3];
         }
     }



     pthread_exit(NULL);
 }


 void *histogram_image(void *arg)
 {
     image_thread *image = (image_thread *)arg;
     int w = image->width;
     int h = image->height;
     int c = image->channels;
     int startw = image->startc;
     int endw = image->endc;
     int startr = image->starth;
     int endr = image->endh;

     int image_index,r,g,b,negative;

     for(int k=startr;k<endr;k++)
     {
         for(int l=startw;l<endw;l++)
         {
              image_index=(k*w+l)*c;

              r=image->old_image[image_index+0];
              g=image->old_image[image_index+1];
              b=image->old_image[image_index+2];

              image->new_image[image_index+0]=(unsigned char)r_lookup_table[r];
              image->new_image[image_index+1]=(unsigned char)g_lookup_table[g];
              image->new_image[image_index+2]=(unsigned char)b_lookup_table[b];

              if(4==c)
                  image->new_image[image_index+3]=image->old_image[image_index+3];
         }
     }


     pthread_exit(NULL);
 }


void histogram_table_build(unsigned char *image, int height, int width, int channels)
{
    int c=channels,w=width,h=height;
     int image_index,r,g,b;
    for(int k=0;k<h;k++)
    {
        for(int l=0;l<w;l++)
        {
            image_index=(k*w+l)*c;
            //grab old values
            r=image[image_index+0];
            g=image[image_index+1];
            b=image[image_index+2];

            r_histogram[r]++;
            g_histogram[g]++;
            b_histogram[b]++;
        }
    }

    for(int k=0;k<256;k++)
    {
        r_sum+=r_histogram[k];
        g_sum+=g_histogram[k];
        b_sum+=b_histogram[k];

        r_cdf[k]=r_sum;
        g_cdf[k]=g_sum;
        b_cdf[k]=b_sum;
    }

    for(int k=0;k<256;k++)
    {
        if(0==r_min && r_cdf[k]>0)
            r_min=r_cdf[k];
        if(0==g_min && g_cdf[k]>0)
            g_min=g_cdf[k];
        if(0==b_min && b_cdf[k]>0)
            b_min=b_cdf[k];

    }

    for(int k=0;k<256;k++)
    {
        r_lookup_table[k]=round((r_cdf[k]-r_min)*255.0/((h*w)-r_min));
        g_lookup_table[k]=round((g_cdf[k]-g_min)*255.0/((h*w)-g_min));
        b_lookup_table[k]=round((b_cdf[k]-b_min)*255.0/((h*w)-b_min));
    }
}


void save_image(int width, int height, int channels, unsigned char* image, string name)
{
    name=name+".png";
    if (!stbi_write_png(name.c_str(), width, height, channels, image, width * channels)) {
           cout<<"Failed to write PNG\n";
       } else {
           cout<<"Saved: "<<name<<endl;
       }
}


void MPI_RUN(int id, int p, unsigned char* image, int height, int width, int channels, int num_threads)
{
    string name;
    unsigned char* new_image;
    if(0==id)
         new_image=initialize_matrix(height, width, channels);
    int rows_per_process=height/p;
    int rows_per_process_remainder=height%p;

    vector<int> send_array(p), displace_array(p);
    int send,displace=0;

    //if(0==id)
    //{
        for(int k=0;k<p;k++)
        {
            send=rows_per_process;
          if(k<rows_per_process_remainder)
              send++;
          send_array[k]=send*width*channels;
          displace_array[k]=displace;
          displace+=send_array[k];
        }
        //}

    int pthread_rows=rows_per_process;
    if(id<rows_per_process_remainder)
        pthread_rows++;

    unsigned char* local_image=initialize_matrix(pthread_rows, width, channels);
    unsigned char* return_image=initialize_matrix(pthread_rows, width, channels);

    vector<image_thread> threads_args(num_threads);
    vector<pthread_t> threads(num_threads);
    MPI_Scatterv(image, send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,local_image,send_array[id],MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

    for (int k=0;k<num_threads;k++)
    {
        image_thread &arg = threads_args[k];
        arg.id = k;
        arg.height = pthread_rows;
        arg.width = width;
        arg.channels = channels;
        arg.threads = num_threads;
        arg.old_image = local_image;
        arg.new_image = return_image;

        // replaced the helper function with in-line math.

        arg.starth = (k * pthread_rows) / num_threads;
        arg.endh = ((k + 1) * pthread_rows) / num_threads;

        // Each thread works on entire column
        arg.startc = 0;
        arg.endc   = width;

        pthread_create(&threads[k], NULL, gray_image_worker, &arg);
    }
    for(int k=0;k<num_threads;k++)
        pthread_join(threads[k], NULL);
    MPI_Gatherv(return_image,send_array[id],MPI_UNSIGNED_CHAR,new_image,send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

    if(id==0)
    {

        name="MPI+Pthreads Gray Color Change";
        save_image(width,height,channels,new_image,name);
        //delete_matrix(new_image);
    }
    delete_matrix(local_image);
    delete_matrix(return_image);


   // pthread_rows=rows_per_process;
    //if(id<rows_per_process_remainder)
      //  pthread_rows++;

   local_image=initialize_matrix(pthread_rows, width, channels);
   return_image=initialize_matrix(pthread_rows, width, channels);

    MPI_Scatterv(image, send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,local_image,send_array[id],MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

    for (int k=0;k<num_threads;k++)
    {
        image_thread &arg = threads_args[k];
        arg.id = k;
        arg.height = pthread_rows;
        arg.width = width;
        arg.channels = channels;
        arg.threads = num_threads;
        arg.old_image = local_image;
        arg.new_image = return_image;

        // replaced the helper function with in-line math.

        arg.starth = (k * pthread_rows) / num_threads;
        arg.endh = ((k + 1) * pthread_rows) / num_threads;

        // Each thread works on entire column
        arg.startc = 0;
        arg.endc   = width;

        pthread_create(&threads[k], NULL, negative_image_worker, &arg);
    }
    for(int k=0;k<num_threads;k++)
        pthread_join(threads[k], NULL);
    MPI_Gatherv(return_image,send_array[id],MPI_UNSIGNED_CHAR,new_image,send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

    if(id==0)
    {

        name="MPI+Pthreads Negative Image Change";
        save_image(width,height,channels,new_image,name);
        //delete_matrix(new_image);
    }
    delete_matrix(local_image);
    delete_matrix(return_image);


    local_image=initialize_matrix(pthread_rows, width, channels);
    return_image=initialize_matrix(pthread_rows, width, channels);

     MPI_Scatterv(image, send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,local_image,send_array[id],MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

     for (int k=0;k<num_threads;k++)
     {
         image_thread &arg = threads_args[k];
         arg.id = k;
         arg.height = pthread_rows;
         arg.width = width;
         arg.channels = channels;
         arg.threads = num_threads;
         arg.old_image = local_image;
         arg.new_image = return_image;

         // replaced the helper function with in-line math.

         arg.starth = (k * pthread_rows) / num_threads;
         arg.endh = ((k + 1) * pthread_rows) / num_threads;

         // Each thread works on entire column
         arg.startc = 0;
         arg.endc   = width;

         pthread_create(&threads[k], NULL, brightness_transformation, &arg);
     }
     for(int k=0;k<num_threads;k++)
         pthread_join(threads[k], NULL);
     MPI_Gatherv(return_image,send_array[id],MPI_UNSIGNED_CHAR,new_image,send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

     if(id==0)
     {

         name="MPI+Pthreads Brightness Image Change";
         save_image(width,height,channels,new_image,name);
         //delete_matrix(new_image);
     }
     delete_matrix(local_image);
     delete_matrix(return_image);


     local_image=initialize_matrix(pthread_rows, width, channels);
     return_image=initialize_matrix(pthread_rows, width, channels);

      MPI_Scatterv(image, send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,local_image,send_array[id],MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

      // image_thread p_thread_args[num_threads]; // Potential fix
      vector<image_thread> p_thread_args(num_threads);

      for (int k=0;k<num_threads;k++)
      {
          // image_thread arg = p_thread_args[k];
          p_thread_args[k].id = k;
          p_thread_args[k].id = k;
          p_thread_args[k].height = pthread_rows;
          p_thread_args[k].width = width;
          p_thread_args[k].channels = channels;
          p_thread_args[k].threads = num_threads;
          p_thread_args[k].old_image = local_image;
          p_thread_args[k].new_image = return_image;

          // arg.id = k;
          // arg.height = pthread_rows;
          // arg.width = width;
          // arg.channels = channels;
          // arg.threads = num_threads;
          // arg.old_image = local_image;
          // arg.new_image = return_image;


          // replaced the helper function with in-line math.

          // arg.starth = (k * pthread_rows) / num_threads;
          // arg.endh = ((k + 1) * pthread_rows) / num_threads;

          p_thread_args[k].starth = (k * pthread_rows) / num_threads;
          p_thread_args[k].endh = ((k + 1) * pthread_rows) / num_threads;

          // Each thread works on entire column
          // arg.startc = 0;
          // arg.endc   = width;

          p_thread_args[k].startc = 0;
          p_thread_args[k].endc   = width;

          pthread_create(&threads[k], NULL, rotate_image, &p_thread_args[k]);
      }

      for(int k=0;k<num_threads;k++)
          pthread_join(threads[k], NULL);

      vector<int> reverse_displace(p);
      reverse_displace[p-1]=0;

      for(int k=p-2;k>=0;k--)
      {
          reverse_displace[k]=reverse_displace[k+1]+send_array[k+1];
      }

      MPI_Gatherv(return_image,send_array[id],MPI_UNSIGNED_CHAR,new_image,send_array.data(),reverse_displace.data(),MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

      if(id==0)
      {

          name="MPI+Pthreads Rotated Image Change";
          save_image(width,height,channels,new_image,name);
          //delete_matrix(new_image);
      }
      delete_matrix(local_image);
      delete_matrix(return_image);

      local_image=initialize_matrix(pthread_rows, width, channels);
      return_image=initialize_matrix(pthread_rows, width, channels);

       MPI_Scatterv(image, send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,local_image,send_array[id],MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

       for (int k=0;k<num_threads;k++)
       {
           image_thread &arg = threads_args[k];
           arg.id = k;
           arg.height = pthread_rows;
           arg.width = width;
           arg.channels = channels;
           arg.threads = num_threads;
           arg.old_image = local_image;
           arg.new_image = return_image;

           // replaced the helper function with in-line math.

           arg.starth = (k * pthread_rows) / num_threads;
           arg.endh = ((k + 1) * pthread_rows) / num_threads;

           // Each thread works on entire column
           arg.startc = 0;
           arg.endc   = width;

           pthread_create(&threads[k], NULL, histogram_image, &arg);
       }
       for(int k=0;k<num_threads;k++)
           pthread_join(threads[k], NULL);
       MPI_Gatherv(return_image,send_array[id],MPI_UNSIGNED_CHAR,new_image,send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

       if(id==0)
       {

           name="MPI+Pthreads Histogram Image Change";
           save_image(width,height,channels,new_image,name);
           //delete_matrix(new_image);
       }
       delete_matrix(local_image);
       delete_matrix(return_image);

       local_image=initialize_matrix(pthread_rows, width, channels);
       return_image=initialize_matrix(pthread_rows, width, channels);

        MPI_Scatterv(image, send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,local_image,send_array[id],MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

        for (int k=0;k<num_threads;k++)
        {
            image_thread &arg = threads_args[k];
            arg.id = k;
            arg.height = pthread_rows;
            arg.width = width;
            arg.channels = channels;
            arg.threads = num_threads;
            arg.old_image = local_image;
            arg.new_image = return_image;

            // replaced the helper function with in-line math.

            arg.starth = (k * pthread_rows) / num_threads;
            arg.endh = ((k + 1) * pthread_rows) / num_threads;

            // Each thread works on entire column
            arg.startc = 0;
            arg.endc   = width;

            pthread_create(&threads[k], NULL, color_change, &arg);
        }
        for(int k=0;k<num_threads;k++)
            pthread_join(threads[k], NULL);
        MPI_Gatherv(return_image,send_array[id],MPI_UNSIGNED_CHAR,new_image,send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

        if(id==0)
        {

            name="MPI+Pthreads Color Image Change";
            save_image(width,height,channels,new_image,name);
            //delete_matrix(new_image);
        }
        delete_matrix(local_image);
        delete_matrix(return_image);


        local_image=initialize_matrix(pthread_rows, width, channels);
        return_image=initialize_matrix(pthread_rows, width, channels);

         MPI_Scatterv(image, send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,local_image,send_array[id],MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

         for (int k=0;k<num_threads;k++)
         {
             image_thread &arg = threads_args[k];
             arg.id = k;
             arg.height = pthread_rows;
             arg.width = width;
             arg.channels = channels;
             arg.threads = num_threads;
             arg.old_image = local_image;
             arg.new_image = return_image;

             // replaced the helper function with in-line math.

             arg.starth = (k * pthread_rows) / num_threads;
             arg.endh = ((k + 1) * pthread_rows) / num_threads;

             // Each thread works on entire column
             arg.startc = 0;
             arg.endc   = width;

             pthread_create(&threads[k], NULL, blurring_image, &arg);
         }
         for(int k=0;k<num_threads;k++)
             pthread_join(threads[k], NULL);
         MPI_Gatherv(return_image,send_array[id],MPI_UNSIGNED_CHAR,new_image,send_array.data(),displace_array.data(),MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

         if(id==0)
         {

             name="MPI+Pthreads Blurred Image Change";
             save_image(width,height,channels,new_image,name);
             delete_matrix(new_image);
         }
         delete_matrix(local_image);
         delete_matrix(return_image);
}

int main(int argc, char * argv[])
{
    if(argc<2)
    {
        cout<<"Did not supply an image"<<endl;
        return 0;
    }

     num_threads = 4;
    if (argc >= 3){
        num_threads = atoi(argv[2]);
    }
    if (num_threads <= 0 || num_threads > 100){
        cout << "Invalid thread range provided. Arg[3] must be 1-100. Defaulting to 4";
    }
    int id,p;
    //init our processes that we specified in the command line
    MPI_Init(&argc, &argv);
    //grabs the ranks of our processes
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    //grabs the total number of processes we are using
    MPI_Comm_size(MPI_COMM_WORLD, &p);



    int num_threads = 4;
    if (argc >= 3){
        num_threads = atoi(argv[2]);
    }
    if (num_threads <= 0 || num_threads > 100){
        if(0==id)
        cout << "Invalid thread range provided. Arg[3] must be 1-100. Defaulting to 4";
    }
    if(0==id)
        cout<<"Thread Count: "<<num_threads<<endl;

    int width = 0, height = 0, channels = 0;
    unsigned char *image = stbi_load(argv[1], &width, &height, &channels, 0);
    if (!image) {
        cerr << "Failed to load image\n";
        return 1;
    }

    histogram_table_build(image, height,width, channels);
    MPI_RUN(id,p,image,height,width,channels, num_threads);





    MPI_Finalize();
    pthread_mutex_destroy(&mylock);
    return 0;
}
