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
        std::cout << "flash_noise_remover.exe [path to image 1 BMP] [path to image 2 BMP] [path to result image BMP]\n"; 
        return 0;
    }

    FILE* header_file   = fopen(argv[1], "rb");
    FILE* file_out      = fopen(argv[3], "wb");

    byte pixel1;
    byte pixel2;

    for (int i = 0; i < 54; i++) {
        putc(getc(header_file), file_out);
    }
    fclose(header_file);
    
    FILE* file1 = fopen(argv[1], "rb");
    FILE* file2 = fopen(argv[2], "rb");

    BITMAPFILEHEADER header1 = readHeader(file1);
    BITMAPINFOHEADER bmiHeader1 = readBmiHeader(file1);
    BITMAPFILEHEADER header2 = readHeader(file2);
    BITMAPINFOHEADER bmiHeader2 = readBmiHeader(file2);
    
    for (int i = 0; i < bmiHeader1.biWidth; i++) {
        for (int j = 0; j < bmiHeader1.biHeight; j++) {
            pixel1 = read_u8(file1);
            pixel2 = read_u8(file2);
            if (pixel1 > pixel2) {
                //putc(pixel2, file_out);
                putc(pixel2, file_out);
            } else {
                putc(pixel1, file_out);
            }
        }
    }

    int val;
    do{
        val = getc(file1);
        putc(val, file_out);
        //val != EOF
    } while (val!=EOF);

    fclose(file1);
    fclose(file2);
    fclose(file_out);

    std::cout << "Finish!\n";

    return 1;
}


