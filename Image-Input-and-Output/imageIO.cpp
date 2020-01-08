#include<iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
    //define the height and width
    int height= 500;
    int width = 750;

    //Image reversing
    unsigned char imageR[height][width];
    FILE *image1 = fopen("image1.raw", "rb+");
    fread(imageR, sizeof(unsigned char), height * width, image1);
    fclose(image1);

    //this double for loop will go to the each pixel and subtract 255 from the pixel value. So all pixel will be reverse.
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            imageR[i][j] = 255 - imageR[i][j];
        }
    }
    FILE *imgReverse = fopen( "imgReverse.raw", "wb+");
    fwrite(imageR, sizeof(unsigned char), height * width, imgReverse);
    fclose(imgReverse);

    //add 20 on the image
    unsigned char imageAdd[height][width];
    FILE *image2 = fopen("image2.raw", "rb+");
    fread(imageAdd, sizeof(unsigned char), height * width, image2);
    fclose(image2);

    //this double for loop will go to the each pixel and add 20 from the pixel value
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            imageAdd[i][j] = 20 + imageAdd[i][j];
        }
    }
    FILE *imgAddOne = fopen( "imgAddOne.raw", "wb+");
    fwrite(imageAdd, sizeof(unsigned char), height * width, imgAddOne);
    fclose(imgAddOne);

    //add 128 on the image
    unsigned char img_Add[height][width];
    FILE *image3 = fopen("image3.raw", "rb+");
    fread(img_Add, sizeof(unsigned char), height * width, image3);
    fclose(image3);

    //this double for loop will go to the each pixel and add 128 from the pixel value
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            img_Add[i][j] = 128 + img_Add[i][j];
        }
    }
    FILE *imgAddTwo = fopen( "imgAddTwo.raw", "wb+");
    fwrite(img_Add, sizeof(unsigned char), height * width, imgAddTwo);
    fclose(imgAddTwo);
}

