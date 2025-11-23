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

void *rotate_image_debug(void *arg)
{
    image_thread *image = (image_thread *)arg;
    int w = image->width;
    int h = image->height;
    int c = image->channels;
    int startw = image->startc;
    int endw = image->endc;
    int startr = image->starth;
    int endr = image->endh;

    // DEBUG: Thread info
    printf("Thread %d: Processing rows %d-%d, cols %d-%d in buffer %dx%dx%d\n",
           image->id, startr, endr, startw, endw, h, w, c);

    int oriIndex, copyIndex, x, y;
    int pixels_processed = 0;

    for(int k = startr; k < endr; k++)
    {
        for(int l = startw; l < endw; l++)
        {
            oriIndex = (k * w + l) * c;
            x = w - 1 - l;
            y = h - 1 - k;
            copyIndex = (y * w + x) * c;
            
            if (copyIndex + c - 1 < h * w * c) {
                for(int m = 0; m < c; m++)
                    image->new_image[copyIndex + m] = image->old_image[oriIndex + m];
                pixels_processed++;
            } else {
                printf("ERROR: Thread %d - copyIndex out of bounds: %d (max: %d)\n", 
                       image->id, copyIndex, h * w * c - 1);
                pthread_exit(NULL);
            }
        }
    }
    
    printf("Thread %d: Processed %d pixels successfully\n", image->id, pixels_processed);
    pthread_exit(NULL);
}

// void *rotate_image(void *arg)
// {
//     image_thread *image = (image_thread *)arg;
//     int w = image->width;           // Local width (same as global)
//     int h = image->height;          // Local height (pthread_rows)
//     int c = image->channels;
//     int startw = image->startc;
//     int endw = image->endc;
//     int startr = image->starth;
//     int endr = image->endh;

//     // Verify we're within local bounds
//     if (endr > h || endw > w) {
//         printf("ERROR: Thread bounds exceed local image dimensions\n");
//         pthread_exit(NULL);
//     }

//     int oriIndex, copyIndex, x, y;

//     for(int k = startr; k < endr; k++)
//     {
//         for(int l = startw; l < endw; l++)
//         {
//             // Calculate source position in LOCAL buffer
//             oriIndex = (k * w + l) * c;
            
//             // Calculate destination position in LOCAL buffer (180° rotation within chunk)
//             x = w - 1 - l;
//             y = h - 1 - k;
//             copyIndex = (y * w + x) * c;
            
//             // Verify destination is within local buffer
//             if (copyIndex + c - 1 < h * w * c) {
//                 for(int m = 0; m < c; m++)
//                     image->new_image[copyIndex + m] = image->old_image[oriIndex + m];
//             } else {
//                 printf("ERROR: copyIndex out of bounds: %d (max: %d)\n", 
//                        copyIndex, h * w * c - 1);
//             }
//         }
//     }
//     pthread_exit(NULL);
// }

void save_image(int width, int height, int channels, unsigned char* image, string name)
{
    name=name+".png";
    if (!stbi_write_png(name.c_str(), width, height, channels, image, width * channels)) {
           cout<<"Failed to write PNG\n";
       } else {
           cout<<"Saved: "<<name<<endl;
       }
}

void MPI_RUN_DEBUG(int id, int p, unsigned char* image, int height, int width, int channels, int num_threads)
{
    string name;
    unsigned char* new_image;
    if(0==id)
         new_image=initialize_matrix(height, width, channels);
    
    int rows_per_process=height/p;
    int rows_per_process_remainder=height%p;

    vector<int> send_array(p), displace_array(p);
    int send, displace=0;

    for(int k=0; k<p; k++) {
        send = rows_per_process;
        if(k < rows_per_process_remainder)
            send++;
        send_array[k] = send * width * channels;
        displace_array[k] = displace;
        displace += send_array[k];
    }

    int pthread_rows = rows_per_process;
    if(id < rows_per_process_remainder)
        pthread_rows++;

    unsigned char* local_image = initialize_matrix(pthread_rows, width, channels);
    unsigned char* return_image = initialize_matrix(pthread_rows, width, channels);

    vector<image_thread> threads_args(num_threads);
    vector<pthread_t> threads(num_threads);

    MPI_Scatterv(image, send_array.data(), displace_array.data(), MPI_UNSIGNED_CHAR,
                local_image, send_array[id], MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    for (int k = 0; k < num_threads; k++) 
    {
        threads_args[k].id = k;
        threads_args[k].height = pthread_rows;
        threads_args[k].width = width;
        threads_args[k].channels = channels;
        threads_args[k].threads = num_threads;
        threads_args[k].old_image = local_image;
        threads_args[k].new_image = return_image;
        threads_args[k].starth = (k * pthread_rows) / num_threads;
        threads_args[k].endh = ((k + 1) * pthread_rows) / num_threads;
        threads_args[k].startc = 0;
        threads_args[k].endc = width;
        
        pthread_create(&threads[k], NULL, rotate_image_debug, &threads_args[k]);
    }
    
    for(int k=0; k<num_threads; k++)
        pthread_join(threads[k], NULL);

    // CORRECT REVERSE ORDERING:
    // Calculate where each process's data should be stored in reverse order
    vector<int> reverse_displace(p);
    
    // Process (p-1-k) should be stored at position k
    // So we calculate displacements backwards
    reverse_displace[p-1] = 0;  // Last position gets process 0's data
    for(int k = p-2; k >= 0; k--) {
        reverse_displace[k] = reverse_displace[k+1] + send_array[k+1];
    }

    // DEBUG: Print the mapping
    if(id == 0) {
        cout << "Reverse mapping:" << endl;
        for(int k=0; k<p; k++) {
            cout << "Position " << k << ": process " << p-1-k << " data (size " 
                 << send_array[p-1-k] << ") at displacement " << reverse_displace[k] << endl;
        }
    }

    // Use original send_array for recvcounts, reverse_displace for storage positions
    MPI_Gatherv(return_image, send_array[id], MPI_UNSIGNED_CHAR,
               new_image, send_array.data(), reverse_displace.data(), 
               MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    if(id == 0) {
        name = "MPI+Pthreads Rotated Image Change";
        save_image(width, height, channels, new_image, name);
        delete_matrix(new_image); 
    }

    delete_matrix(local_image);
    delete_matrix(return_image);
}

// void MPI_RUN(int id, int p, unsigned char* image, int height, int width, int channels, int num_threads)
// {
//     string name;
//     unsigned char* new_image;
//     if(0==id)
//          new_image=initialize_matrix(height, width, channels);
    
//     int rows_per_process=height/p;
//     int rows_per_process_remainder=height%p;

//     vector<int> send_array(p), displace_array(p);
//     int send, displace=0;

//     for(int k=0; k<p; k++) {
//         send = rows_per_process;
//         if(k < rows_per_process_remainder)
//             send++;
//         send_array[k] = send * width * channels;
//         displace_array[k] = displace;
//         displace += send_array[k];
//     }

//     int pthread_rows = rows_per_process;
//     if(id < rows_per_process_remainder)
//         pthread_rows++;

//     unsigned char* local_image = initialize_matrix(pthread_rows, width, channels);
//     unsigned char* return_image = initialize_matrix(pthread_rows, width, channels);

//     vector<image_thread> threads_args(num_threads);
//     vector<pthread_t> threads(num_threads);

//     MPI_Scatterv(image, send_array.data(), displace_array.data(), MPI_UNSIGNED_CHAR,
//                 local_image, send_array[id], MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

//     // FIXED: Pass &threads_args[k] instead of &arg
//     for (int k = 0; k < num_threads; k++) 
//     {
//         threads_args[k].id = k;
//         threads_args[k].height = pthread_rows;     // LOCAL height
//         threads_args[k].width = width;             // LOCAL width (same as global)
//         threads_args[k].channels = channels;
//         threads_args[k].threads = num_threads;
//         threads_args[k].old_image = local_image;
//         threads_args[k].new_image = return_image;
//         threads_args[k].starth = (k * pthread_rows) / num_threads;
//         threads_args[k].endh = ((k + 1) * pthread_rows) / num_threads;
//         threads_args[k].startc = 0;
//         threads_args[k].endc = width;
        
//         pthread_create(&threads[k], NULL, rotate_image, &threads_args[k]);
//     }
    
//     for(int k=0; k<num_threads; k++)
//         pthread_join(threads[k], NULL);

//     vector<int> reverse_send(p);
//     for(int k=0; k<p; k++) {
//         reverse_send[k] = send_array[p-1-k];
//     }

//     vector<int> reverse_displace(p);
//     reverse_displace[0] = 0;
//     for(int k=1; k<p; k++) {
//         reverse_displace[k] = reverse_displace[k-1] + reverse_send[k-1];
//     }

//     MPI_Gatherv(return_image, send_array[id], MPI_UNSIGNED_CHAR,
//                new_image, reverse_send.data(), reverse_displace.data(), 
//                MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

//     if(id == 0) {
//         name = "MPI+Pthreads Rotated Image Change";
//         save_image(width, height, channels, new_image, name);
//         delete_matrix(new_image); 
//     }

//     delete_matrix(local_image);
//     delete_matrix(return_image);
// }

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        cout << "Did not supply an image" << endl;
        return 0;
    }

    num_threads = 4;
    if (argc >= 3) {
        num_threads = atoi(argv[2]);
    }
    if (num_threads <= 0 || num_threads > 100) {
        cout << "Invalid thread range provided. Arg[3] must be 1-100. Defaulting to 4";
        num_threads = 4;
    }

    int id, p;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // Proper process limiting
    if(p > 7) {
        if(id == 0) {
            cout << "Error: Maximum 7 processes supported. Requested: " << p << endl;
        }
        MPI_Finalize();
        return 0;
    }

    if(id == 0) {
        cout << "Thread Count: " << num_threads << endl;
    }

    int width = 0, height = 0, channels = 0;
    unsigned char *image = stbi_load(argv[1], &width, &height, &channels, 0);
    if (!image) {
        if(id == 0) {
            cerr << "Failed to load image: " << argv[1] << endl;
        }
        MPI_Finalize();
        return 1;
    }

    if(id == 0) {
        cout << "Loaded image: " << width << " x " << height << " x " << channels << endl;
    }

    MPI_RUN_DEBUG(id, p, image, height, width, channels, num_threads);
    
    stbi_image_free(image);  // Free the original image
    MPI_Finalize();
    pthread_mutex_destroy(&mylock);
    return 0;
}