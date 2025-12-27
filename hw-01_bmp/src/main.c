#include "bmp.h"
#include "stego.h"

int crop_rotate(char** argv, bmp_header_t* input_head, bmp_header_info_t* input_head_info, Pixel_t** input_Pixel_mas)
{
	bmp_header_t head = *input_head;
	bmp_header_info_t head_info = *input_head_info;
	Pixel_t* Pixel_mas = *input_Pixel_mas;
	int x = atoi(argv[4]);
	int y = atoi(argv[5]);
	int w = atoi(argv[6]);
	int h = atoi(argv[7]);

	if (!(0 <= x && x < x + w && x + w <= head_info.Width && 0 <= y && y < y + h && y + h <= head_info.Height))
		return 1;
	y = head_info.Height - y - h;
	Pixel_t* Cut_Pixel_mas;
	if (crop(&Pixel_mas, &Cut_Pixel_mas, x, y, w, h, head_info.Width)) return 1;
	Pixel_t * Final_Pixel_mas;
	if (rotate(&Cut_Pixel_mas, &Final_Pixel_mas, w, h))
	{
		free(Cut_Pixel_mas);
		return 1;
	}
	head_info.Width = h;
	head_info.Height = w;
	int Byte_Width = sizeof(Pixel_t) * head_info.Width;
	head_info.ImageSize = (Byte_Width + (4 - Byte_Width % 4) % 4) * head_info.Height;
	head.File_Size = head_info.ImageSize + sizeof(head) + sizeof(head_info);
	free(Cut_Pixel_mas);
	if (save_bmp(argv[3], &head, &head_info, &Final_Pixel_mas))
	{
		free(Final_Pixel_mas);
		return 1;
	}
	free(Final_Pixel_mas);
	return 0;
}

int main(int argc, char** argv)
{
	if (argc < 3) return 1;
	Pixel_t* Pixel_mas;
	bmp_header_t head;
	bmp_header_info_t head_info;
	if (load_bmp(argv[2], &head, &head_info, &Pixel_mas)) return 1;
	if (strcmp(argv[1], "crop-rotate") == 0)
	{
		if (argc < 8) return 1;
		if (crop_rotate(argv, &head, &head_info, &Pixel_mas))
		{
			free(Pixel_mas);
			return 1;
		}
		free(Pixel_mas);
		return 0;
	}
	else if (strcmp(argv[1], "insert") == 0)
	{
		if (argc < 6) return 1;
		if (insert(argv, &head, &head_info, &Pixel_mas))
		{
			free(Pixel_mas);
			return 1;
		}
		free(Pixel_mas);
		return 0;
	}
	else if (strcmp(argv[1], "extract") == 0)
	{
		if (argc < 5) return 1;
		if (extract(argv, &head, &head_info, &Pixel_mas))
		{
			free(Pixel_mas);
			return 1;
		}
		free(Pixel_mas);
		return 0;
	}
	free(Pixel_mas);
	return 1;
}