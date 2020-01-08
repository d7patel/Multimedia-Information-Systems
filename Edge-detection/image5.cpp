#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int checkA(int one);

int main(){
    FILE* originalImg = NULL;
    FILE* imgOne = NULL;
    FILE* imgTwo = NULL;
    FILE* imgThree = NULL;
    FILE* imgFour = NULL;

    int Height = 600;
    int Width = 500;

    // Horizonal
    int arrayH[5][5] = {{-1,-2,-4,-2,-1},
                        {-2,-4,-8,-4,-2},
                        {0,0,0,0,0},
                        {2,4,8,4,2},
                        {1,2,4,2,1}};   
    // Vertical
    int arrayV[5][5] = {{-1,-2,0,2,1},
                        {-2,-4,0,4,2},
                        {-4,-8,0,8,4},
                        {-2,-4,0,4,2},
                        {-1,-2,0,2,1}};

    unsigned char image[600][500];
    unsigned char sobelH[600][500];
    unsigned char sobelV[600][500];
    unsigned char imgGradient[600][500];
    unsigned char imgGradientThreshold[600][500];

    //open file
    originalImg = fopen("img.raw", "r");

    //create the new two image
    imgOne = fopen("imageV5.raw", "wb+");
    imgTwo = fopen("imageH5.raw", "wb+");
    imgThree = fopen("gradient5.raw", "wb+");
    imgFour = fopen("gradientThreshold5.raw", "wb+");

    //read file
    fread(image, sizeof( unsigned char), Height * Width, originalImg);

    // arrays
    int value1[600][500];
    int value2[600][500];
    // convolution for 5x5
    for(int i = 0; i < Height - 4; i++){
        for(int j = 0; j < Width - 4; j++){
            for(int k = 0; k < 5; k++){
                for(int l = 0; l < 5; l++){
                    value1[i+1][j+1] += arrayH[k][l] * (int)(image[i+k][j+l]);
                    value2[i+1][j+1] += arrayV[k][l] * (int)(image[i+k][j+l]);
                }
            }
        }
    }
    //normalizing
    for(int i = 0; i < Height; i++){
        for(int j = 0; j < Width; j++){
            sobelH[i][j] = (unsigned char)(value1[i][j] / 56 + 128);
            sobelV[i][j] = (unsigned char)(value2[i][j] / 56 + 128);
        }
    }

    //gradient
    int value3[600][500];
    for (int i = 0; i < Height; ++i){
        for(int j = 0; j < Width; j++){
            value3[i][j] = (int)sobelH[i][j] - (int)sobelV[i][j];
        }
    }
    int value4 = 0;
    for(int i = 0; i < Height; i++){
        for(int j = 0; j < Width; j++){
            //add 128 to the image
            value4 = (128 + value3[i][j]); 
            imgGradient[i][j] = (unsigned char)value4;
        }
    }
    int value5 = 0;
    for(int i = 0; i < Height; i++){
        for(int j = 0; j < Width; j++){
            value5 =(int)imgGradient[i][j];
            value4 = abs(value5 - 128);
            imgGradientThreshold[i][j] = (unsigned char)value4;
        }
    }
    int num = 10;
    unsigned char number  = (unsigned char)(0);
    for(int i = 0; i < Height; i++){
        for(int j = 0; j < Width; j++){
            value4 = (int)imgGradientThreshold[i][j];

            if(value4 < num){
                imgGradientThreshold[i][j] = number;
            }
        }
    }
    // Write the modified datat to export files
    fwrite(sobelH, sizeof( unsigned char), Height * Width, imgOne);
    fwrite(sobelV, sizeof( unsigned char), Height * Width, imgTwo);
    fwrite(imgGradient, sizeof( unsigned char), Height * Width, imgThree);
    fwrite(imgGradientThreshold, sizeof( unsigned char), Height * Width, imgFour);

    //close the files
    fclose (originalImg); 
    fclose(imgOne);
    fclose(imgTwo);
    fclose (imgThree);
    fclose (imgFour);
    return 0;
}
// this function check the value
int checkA(int one){
    one = (one)/60 + 128;
    return one;
}