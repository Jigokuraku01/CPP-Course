#ifndef BMP_H_
#define BMP_H_
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct
{
  short Signature;
  int File_Size;
  short Reserved1;
  short Reserved2;
  int File_Offset_To_Pixel_Array;
} bmp_header_t;

typedef struct
{
  int DIB_header_size;
  int Width;
  int Height;
  short Planes;
  short Bits_Per_Pixel;
  int Compression;
  int ImageSize;
  int XPixelsPerMeter;
  int YPixelsPerMeter;
  int ColorsUsed;
  int ColorsImportant;
} bmp_header_info_t;

typedef struct
{
  unsigned char B;
  unsigned char G;
  unsigned char R;
} Pixel_t;
#pragma pack(pop)

int save_bmp(char* File_Path, bmp_header_t* head, bmp_header_info_t* head_info, Pixel_t** Pixel_mas);
int load_bmp(char* File_Path, bmp_header_t* head, bmp_header_info_t* head_info, Pixel_t** Pixel_mas);
int crop(Pixel_t** Prev_mas, Pixel_t** Input_Rotate_crop_mas, int x, int y, int w, int h, int prev_wight);
int rotate(Pixel_t** Cut_Pixel_mas, Pixel_t** Input_Rotate_rotate_mas, int w, int h);

#endif // BMP_H_