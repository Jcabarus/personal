#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <vector>
#include <iostream>
#include <pthread.h>
using namespace std;

struct image_thread
{
    int id;
    int height;
    int width;
    int channels;
    int threads;

    unsigned char *old_image;
    vector<unsigned char>* new_image;   // pointer to shared output
};

int get_number_of_threads(int width, int height)
{
    if(height<=480 && width<=640) return 4;
    if(height<=1280 && width<=720) return 8;
    if(height<=1920 && width<=1080) return 16;
    if(height<=2560 && width<=1440) return 32;
    if(height<=3840 && width<=2160) return 64;
    return 128;
}

void *gray_image_worker(void *arg)
{
    image_thread* t = (image_thread*)arg;

    int id = t->id;
    int h = t->height;
    int w = t->width;
    int c = t->channels;
    int threads = t->threads;

    unsigned char* old_im = t->old_image;
    vector<unsigned char>& out = *(t->new_image);

    // Split rows among threads
    int rows_per_thread = h / threads;
    int start_row = id * rows_per_thread;
    int end_row   = (id == threads - 1) ? h : start_row + rows_per_thread;

    for(int k = start_row; k < end_row; k++)
    {
        for(int l = 0; l < w; l++)
        {
            int idx = (k * w + l) * c;

            int r = old_im[idx + 0];
            int g = old_im[idx + 1];
            int b = old_im[idx + 2];

            int gray = 0.3*r + 0.59*g + 0.11*b;

            out[idx + 0] = gray;
            out[idx + 1] = gray;
            out[idx + 2] = gray;

            if (c == 4)
                out[idx + 3] = old_im[idx + 3];
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        cout << "Did not supply an image" << endl;
        return 0;
    }

    int width, height, channels;
    unsigned char *image = stbi_load(argv[1], &width, &height, &channels, 0);

    if (!image)
    {
        cout << "Failed to load image\n";
        return 0;
    }

    int threads = get_number_of_threads(width, height);
    cout << "Using " << threads << " threads" << endl;

    vector<unsigned char> new_image(width * height * channels);

    pthread_t thread[threads];
    image_thread thread_data[threads];

    for(int i = 0; i < threads; i++)
    {
        thread_data[i].id = i;
        thread_data[i].height = height;
        thread_data[i].width = width;
        thread_data[i].channels = channels;
        thread_data[i].threads = threads;
        thread_data[i].old_image = image;
        thread_data[i].new_image = &new_image;

        pthread_create(&thread[i], NULL, gray_image_worker, &thread_data[i]);
    }

    for(int i = 0; i < threads; i++)
        pthread_join(thread[i], NULL);

    string name = "P-Gray.png";
    if (!stbi_write_png(name.c_str(), width, height, channels, new_image.data(), width * channels))
        cout << "Failed to write PNG\n";
    else
        cout << "Saved: " << name << endl;

    stbi_image_free(image);

    return 0;
}
