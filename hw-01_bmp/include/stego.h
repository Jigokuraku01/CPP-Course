#ifndef STEGO_H_
#define STEGO_H_

#include "bmp.h"

int extract(char** argv, bmp_header_t* input_head, bmp_header_info_t* input_head_info, Pixel_t** input_Pixel_mas);
int insert(char** argv, bmp_header_t* input_head, bmp_header_info_t* input_head_info, Pixel_t** input_Pixel_mas);
#endif // STEGO_H_