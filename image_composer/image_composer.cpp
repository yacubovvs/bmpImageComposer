#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bmp.cpp"


#define byte unsigned char

int main(int argc, char* argv[])
{

    //std::cout << argc << "\n" << argv[1] << "\n" << argv[2] << "\n" << argv[3] << "\n";
    
    if (argc < 4) {
        std::cout << "Too few arguments\n";
        std::cout << "Usage:\n";
        std::cout << "image_composer.exe [full path to image 1 BMP] [full path to image 2 BMP] [full path to result image BMP]\n";
        //std::cout << "or:\n";
        //std::cout << "image_composer.exe [path to image 1 BMP] [path to image 2 BMP] [path to result image BMP] [-r]\n";
        //std::cout << "-r Rotation 180 degrees of 2nd image";
        std::cout << "both images should have same sizes";
        return 0;
    }
    

    FILE* file1     = fopen(argv[1], "rb");
    FILE* file2     = fopen(argv[2], "rb");
    FILE* file_out  = fopen(argv[3], "wb");
    

    
    /*
    FILE* file1     = fopen("C:\\2\\1\\cam2_2.bmp", "rb");
    FILE* file2     = fopen("C:\\2\\1\\cam1_2.bmp", "rb");
    FILE* file_out  = fopen("C:\\2\\1\\cam_out.bmp", "wb");
    */
    //FILE* file_out2 = fopen("C:\\2\\1\\cam_out2.hex", "wb");

    BITMAPFILEHEADER header1 = readHeader(file1);
    BITMAPINFOHEADER bmiHeader1 = readBmiHeader(file1);
    BITMAPFILEHEADER header2 = readHeader(file2);
    BITMAPINFOHEADER bmiHeader2 = readBmiHeader(file2);

    bmiHeader1.biHeight *= 2;
    header1.bfSize *= 2;
    
    writeHeader(header1, file_out);
    writeHeader(bmiHeader1, file_out);

    byte pixel;

    long length = header1.bfSize / 2; //bmiHeader1.biWidth * bmiHeader1.biHeight / 2;
    byte *mass = new byte[length];
    byte *mass_invert = new byte[length];

    fread(mass, 1, length, file1);

    //fwrite(mass_invert, 1, length, file_out);
    fwrite(mass, 1, length, file_out);

    fread(mass, 1, length, file2);
    /*
    for (int i = 0; i < bmiHeader1.biWidth/2 + 54*2; i++) {
        putc(0xff, file_out);
    }*/

    //if(argc==5 && argv[4]=="-r"){
        for (int i = 0; i < length; i++) {
            mass_invert[length - i - 1] = mass[i];
            //mass_invert[i] = mass[i];
        }

        fwrite(mass_invert, 1, length, file_out);
    /*
    }else {
        fwrite(mass, 1, length, file_out);
    }
    */

    delete []mass;
    delete []mass_invert;

    int val;
    do {
        val = getc(file1);
        putc(val, file_out);
    } while (val != EOF);

    fclose(file1);
    fclose(file2);
    fclose(file_out);

    std::cout << "Finish!\n";

    return 1;
}


