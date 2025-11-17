#include <atomic>
#include <stdio.h>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <random>
using namespace std;

//Function for rotating the image this function will rotate 180 degrees
// We return a vector of unsigned chars to main as this is how we store the image
// We pass the image height, width, channels, and pointer to original copy
 vector<unsigned char> rotate_image(int height, int width, int channels, unsigned char *old_image)
 {
    //This creates oriIndex, copyIndex,x,y
    // oriIndex is used to grab the original index from the old image that we use to grab the orignal pixel spot before we place it in the new spot
    // copyIndex is where we put the pixel from the old_image into its new spot in image_rotation
    // x is for holding our width spot
    // y is for holding our height spot
    int oriIndex,copyIndex,x,y;

    //This creates a vector to hold our new image after we rotate it
    vector<unsigned char> image_rotation(height*width*channels);

    for(int k=0;k<height;k++)
    {
        for(int l=0;l<width;l++)
        {
            //This will grab the pixel spot we are about to change
            oriIndex=(k*width+l)*channels;
            //This will grab new width position we will put the pixel in
            x=width-1-l;
            //This will grab the new height position that we put the pixel in
            y=height-1-k;

            //This is where we grab our new spot to place our pixel in the copy
            copyIndex=(y*width+x)*channels;

            //This will loop for how many colors there are in this image and write the pixels to their new location
            for(int m=0;m<channels;m++)
                image_rotation[copyIndex+m]=old_image[oriIndex+m];
        }
    }
    //we return our rotated image to main
    return image_rotation;
}

//Function for blurring our image
// We return a vector of unsigned chars to main as this is how we store the image
// We pass the image height, width, channels, and pointer to original copy
vector<unsigned char> blurring_image(int height, int width, int channels, unsigned char *image)
 {
     //This will create a vector of usigned chars to hold our blur image before returning to main
     vector<unsigned char> blurred_image(height*width*channels);

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

     for(int k=0;k<height;k++)
     {
         for(int l=0;l<width;l++)
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
                    if(holdx<0||holdx>=width||holdy<0||holdy>=height)
                        continue;
                    //computes the pixel index
                    image_index=(holdy*width+holdx)*channels;

                    //sums up all of the rgb values
                    r+=image[image_index+0];
                    g+=image[image_index+1];
                    b+=image[image_index+2];

                    //holds how many total pixels were included
                    total_iteration++;

                }
            }
            //finds what spot we put our new blurred pixel in
            blur_index=(k*width+l)*channels;

            //computes the new average rgb values we put into the new spot
            blurred_image[blur_index+0]=r/total_iteration;
            blurred_image[blur_index+1]=g/total_iteration;
            blurred_image[blur_index+2]=b/total_iteration;

            //if the image has an alpha channel we copt it into the new spot unchanged
            if(4==channels)
                blurred_image[blur_index+3]=image[blur_index+3];
         }
     }



     return blurred_image;
 }


//Function for changing the images color
//We return a vector of unsigned chars to main as this is how we store the image
//We pass the image height, width, channels, and pointer to original copy
vector<unsigned char> brightness_transformation(int height, int width, int channels, unsigned char *image)
 {
     //This will create a vector of unsigned chars to hold our new image with color transformation
     vector<unsigned char> image_color_change(height*width*channels);

    //image_index grabs our index from our image where we read the rgb values from
    // r,g,b will hold our images original rgb values
    int image_index,r,g,b,brightness=40;
    for(int k=0;k<height;k++)
    {
        for(int l=0;l<width;l++)
        {
            //grabs the index of the pixel we are changing
            image_index=(k*width+l)*channels;

            //will store the original rgb value from our image
            r=image[image_index+0];
            g=image[image_index+1];
            b=image[image_index+2];

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
            image_color_change[image_index+0]=(unsigned char)r;
            image_color_change[image_index+1]=(unsigned char)g;
            image_color_change[image_index+2]=(unsigned char)b;

            if(4==channels)
                image_color_change[image_index+3]=image[image_index+3];

        }
    }
    return image_color_change;
 }


vector<unsigned char> color_change(int height, int width, int channels, unsigned char *image)
{
    vector<unsigned char> image_color_change(height*width*channels);

    random_device ran_num;
    mt19937 eng(ran_num());
    uniform_int_distribution<> distr(0, 255);

    int image_index,r,g,b;

    for(int k=0;k<height;k++)
    {
        for (int l=0;l<width;l++)
        {
            image_index=(k*width+l)*channels;

            r=distr(eng);
            g=distr(eng);
            b=distr(eng);

            image_color_change[image_index+0]=(unsigned char)r;
            image_color_change[image_index+1]=(unsigned char)g;
            image_color_change[image_index+2]=(unsigned char)b;

            if(4==channels)
                image_color_change[image_index+3]=image[image_index+3];
        }
    }



    return image_color_change;
}

vector<unsigned char> gray_scale(int height, int width, int channels, unsigned char *image)
{
    vector<unsigned char> gray_image(height*width*channels);
    int image_index,r,g,b,gray;
    for(int k=0;k<height;k++)
    {
        for(int l=0;l<width;l++)
        {
            image_index=(k*width+l)*channels;

            r=image[image_index+0];
            g=image[image_index+1];
            b=image[image_index+2];
            gray=0.3*r+0.59*g+0.11*b;
            gray_image[image_index+0]=(unsigned char)gray;
            gray_image[image_index+1]=(unsigned char)gray;
            gray_image[image_index+2]=(unsigned char)gray;

            if(4==channels)
                gray_image[image_index+3]=image[image_index+3];
        }
    }


    return gray_image;
}

void save_image(int width, int height, int channels, vector<unsigned char>&image, string name)
{
    name=name+".png";
    if (!stbi_write_png(name.c_str(), width, height, channels, image.data(), width * channels)) {
           cout<<"Failed to write PNG\n";
       } else {
           cout<<"Saved: "<<name<<endl;
       }
}

vector<unsigned char> negative_image(int height, int width, int channels, unsigned char *image)
{
    vector<unsigned char> image_negative(height*width*channels);
    int image_index,r,g,b,negative;

    for(int k=0;k<height;k++)
    {
        for(int l=0;l<width;l++)
        {
            image_index=(k*width+l)*channels;

            r=image[image_index+0];
            g=image[image_index+1];
            b=image[image_index+2];
            r=255-r;
            g=255-g;
            b=255-b;

            image_negative[image_index+0]=(unsigned char)r;
            image_negative[image_index+1]=(unsigned char)g;
            image_negative[image_index+2]=(unsigned char)b;

            if(4==channels)
                image_negative[image_index+3]=image[image_index+3];
        }
    }


    return image_negative;
}

vector<unsigned char> histogram_image(int height, int width, int channels, unsigned char *image)
{
    vector<unsigned char> histogram(height*width*channels);
    int image_index,r,g,b,negative;
    int r_histogram[256]={0},g_histogram[256]={0},b_histogram[256]={0};
    int r_sum=0,g_sum=0,b_sum=0;
    int r_cdf[256],g_cdf[256],b_cdf[256];
    int r_min=0,g_min=0,b_min=0;
    int r_lookup_table[256], g_lookup_table[256], b_lookup_table[256];

    for(int k=0;k<height;k++)
    {
        for(int l=0;l<width;l++)
        {
            image_index=(k*width+l)*channels;
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
        r_lookup_table[k]=round((r_cdf[k]-r_min)*255.0/((height*width)-r_min));
        g_lookup_table[k]=round((g_cdf[k]-g_min)*255.0/((height*width)-g_min));
        b_lookup_table[k]=round((b_cdf[k]-b_min)*255.0/((height*width)-b_min));
    }

    for(int k=0;k<height;k++)
    {
        for(int l=0;l<width;l++)
        {
             image_index=(k*width+l)*channels;

             r=image[image_index+0];
             g=image[image_index+1];
             b=image[image_index+2];

             histogram[image_index+0]=(unsigned char)r_lookup_table[r];
             histogram[image_index+1]=(unsigned char)g_lookup_table[g];
             histogram[image_index+2]=(unsigned char)b_lookup_table[b];

             if(4==channels)
                 histogram[image_index+3]=image[image_index+3];
        }
    }


    return histogram;
}




int main(int argc, char * argv[])
{
    //If we do not supply and image the program quits
    if(argc<2)
    {
        cout<<"Did not supply an image"<<endl;
        return 0;
    }

    int width,height,channels;
   unsigned char *image = stbi_load(argv[1], &width, &height, &channels, 0);

    vector<unsigned char> image_rotation, image_color_change, blurred_image, brightness_change, gray, negative, histo;
    string name;

   //This if statement checks if the image cannot be opened and if it cannot be opened we quit the program
   if(!image)
   {
       cout<<"Cannot open image "<<argv[1]<<endl;
       return 0;
   }



   //Calls our rotate image function and saves output to image_rotation
   image_rotation=rotate_image(height,width,channels, image);

   //Calls our image color change function and saves output to image_color_change
   brightness_change=brightness_transformation(height,width,channels,image);

   image_color_change=color_change(height,width,channels,image);

   //Calls our blur image function and saves output to blurred_image
   blurred_image=blurring_image(height,width,channels,image);

   gray=gray_scale(height,width,channels,image);

   negative=negative_image(height,width,channels,image);

   histo=histogram_image(height,width,channels,image);

   name="image rotation";
   save_image(width, height,channels,image_rotation,name);
   name="Color Change";
   save_image(width, height,channels,image_color_change,name);
   name="Brightness Change";
   save_image(width, height,channels,brightness_change,name);
   name="Gray Scale";
   save_image(width,height,channels,gray,name);
   name="Negative-Image";
   save_image(width,height,channels,negative,name);
   name="Histogram-Image";
   save_image(width,height,channels,histo,name);
   //Frees the allocated memory we used to read in our image from the command line
   stbi_image_free(image);
    return 0;
}
