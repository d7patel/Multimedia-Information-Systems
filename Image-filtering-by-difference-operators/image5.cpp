#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* originalImg = NULL;
    FILE* imgOne = NULL;
    FILE* imgTwo = NULL;

    int Height = 600;
    int Width = 500;

    // Horizonal
    int arrayH[5][5] = {{-2,-3, -4,-3,-2},
                        {-1,-2,-3,-2,-1},
                        {0,0,0,0,0},
                        {1,2,3,2,1},
                        {2,3,4,3,2}};   
    // Vertical
    int arrayV[5][5] = {{-2,-1,0,1,2},
                        {-3,-2,0,2,3},
                        {-4,-3,0,3,4},
                        {-3,-2,0,2,3},
                        {-2,-1,0,1,2}};

    unsigned char image[600][500];
    unsigned char sobelH[600][500];
    unsigned char sobelV[600][500];

    originalImg = fopen("img.raw", "r");

    //create the new two image
    imgOne = fopen("imageV5.raw", "wb+");
    imgTwo = fopen("imageH5.raw", "wb+");

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

    // Write the modified datat to export files
    fwrite(sobelH, sizeof( unsigned char), Height * Width, imgOne);
    fwrite(sobelV, sizeof( unsigned char), Height * Width, imgTwo);

    //close the files
    fclose (originalImg); 
    fclose(imgOne);
    fclose(imgTwo);
    return 0;
}