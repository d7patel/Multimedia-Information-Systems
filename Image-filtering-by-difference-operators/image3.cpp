#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main()
    {
    FILE* originalImg = NULL;
    FILE* imgOne = NULL; 
    FILE* imgTwo = NULL;

    int Height = 600;
    int Width = 500;

    // Horizontal
    int arrayH[3][3] = {{-1,-2,-1},
                        {0,0,0},
                        {1,2,1}};    
    // Vertical
    int arrayV[3][3] = {{-1,0,1},
                        {-2,0,2},
                        {-1,0,1}};     

    unsigned char image[600][500];
    unsigned char sobelH[600][500];
    unsigned char sobelV[600][500];

    originalImg = fopen("img.raw", "r");

    //create the new two image
    imgOne = fopen("imageV3.raw", "wb+");
    imgTwo = fopen("imageH3.raw", "wb+");

    //read file
    fread(image, sizeof( unsigned char), Height * Width, originalImg);

    //arrays
    int value1[600][500];
    int value2[600][500];
    //convolution for 3x3
    for(int i = 0; i < Height - 2; i++){
        for(int j = 0; j < Width - 2; j++){
            for(int k = 0; k < 3; k++){
                for(int l = 0; l < 3; l++){
                    value1[i+1][j+1] += arrayH[k][l] * (int)(image[i+k][j+l]);
                    value2[i+1][j+1] += arrayV[k][l] * (int)(image[i+k][j+l]);
                }
            }
        }
    }
    //normalizing
    for(int i = 0; i < Height; i++){
        for(int j = 0; j < Width; j++){
            sobelH[i][j] = (unsigned char)(value1[i][j] / 8 + 128);
            sobelV[i][j] = (unsigned char)(value2[i][j] / 8 + 128);
        }
    }
    // Write the modified datat to export files
    fwrite(sobelH, sizeof( unsigned char), Height * Width, imgOne);
    fwrite(sobelV, sizeof( unsigned char), Height * Width, imgTwo);

    //close the files
    fclose (originalImg);
    fclose (imgOne);
    fclose (imgTwo);
    return 0;
}