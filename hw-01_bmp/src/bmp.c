#include"bmp.h"

int load_bmp(char* File_Path, bmp_header_t* head, bmp_header_info_t* head_info, Pixel_t** Pixel_mas)
{
	int tmp_int_for_padding;

	FILE* fin = fopen(File_Path, "rb");
	if (fin == NULL) return 1;
	fread(head, sizeof(*head), 1, fin);
	fread(head_info, sizeof(*head_info), 1, fin);

	long To_Read = sizeof(Pixel_t) * head_info->Width;

	*Pixel_mas = malloc(sizeof(Pixel_t) * head_info->Height * head_info->Width);
	if (head == NULL || head_info == NULL || *Pixel_mas == NULL) return 1;
	for (int i = 0; i < head_info->Height; ++i)
	{
		fread(&((*Pixel_mas) [i * head_info->Width]), To_Read, 1, fin);
		fread(&tmp_int_for_padding, (4 - To_Read % 4) % 4, 1, fin);
	}
	fclose(fin);
	return 0;
}

int save_bmp(char* File_Path, bmp_header_t* head, bmp_header_info_t* head_info, Pixel_t** Pixel_mas)
{
	const int nol = 0;
	long To_Write = sizeof(Pixel_t) * head_info->Width;

	FILE* fout = fopen(File_Path, "wb");
	if (fout == NULL) return 1;
	fwrite(head, sizeof(*head), 1, fout);
	fwrite(head_info, sizeof(*head_info), 1, fout);
	for (int i = 0; i < head_info->Height; ++i)
	{
		fwrite(*Pixel_mas + i * head_info->Width, To_Write, 1, fout);
		fwrite(&nol, (4 - To_Write % 4) % 4, 1, fout);
	}
	fclose(fout);
	return 0;
}

int crop(Pixel_t** Prev_mas, Pixel_t** Input_Rotate_crop_mas, int x, int y, int w, int h, int prev_wight)
{
	*Input_Rotate_crop_mas = malloc(sizeof(Pixel_t) * w * h);
	if (*Input_Rotate_crop_mas == NULL) return 1;
	for (int j = 0; j < h; ++j)
	{
		for (int i = 0; i < w; ++i)
			(*Input_Rotate_crop_mas)[j * w + i] = (*Prev_mas)[(j + y) * prev_wight + i + x];
	}
	return 0;
}

int rotate(Pixel_t** Cut_Pixel_mas, Pixel_t** Input_Rotate_rotate_mas, int w, int h)
{
	*Input_Rotate_rotate_mas = malloc(sizeof(Pixel_t) * w * h);
	if (*Input_Rotate_rotate_mas == NULL) return 1;
	for (int j = 0; j < h; ++j)
	{
		for (int i = 0; i < w; ++i)
			(*Input_Rotate_rotate_mas)[i * h + j] = (*Cut_Pixel_mas)[j * w +  w - i - 1];
	}
	return 0;
}