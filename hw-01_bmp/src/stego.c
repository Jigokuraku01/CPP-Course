#include "stego.h"


/*For letters A-Z codes: 0-25. For " " - 26. For "." - 27. For "," - 28*/
const int CNT_BYTS_FOR_STEGO = 5;

int extract(char** argv, bmp_header_t* input_head, bmp_header_info_t* input_head_info, Pixel_t** input_Pixel_mas)
{
	bmp_header_t head = *input_head;
	head = head;
	bmp_header_info_t head_info = *input_head_info;
	Pixel_t* Pixel_mas = *input_Pixel_mas;
	int x, y, READ_BYT = 0;
	char c;
	int CUR_CHAR_IND = 0;
	char DECODE_COMB[29];
	for (int i = 0; i < 26; ++i)
		DECODE_COMB[i] = i + 'A';
	DECODE_COMB[26] = ' ';
	DECODE_COMB[27] = '.';
	DECODE_COMB[28] = ',';
	
	FILE *fin = fopen(argv[3], "r");
	if (fin == NULL) return 1;
	FILE* fout = fopen(argv[4], "wb");
	if (fout == NULL)
	{
		fclose(fin);
		return 1;
	}
	while (!feof(fin))
	{
		if (fscanf(fin, "%d %d %c\n", &x, &y, &c) != 3)
			break;
		if (ferror(fin))
			break;
		y = head_info.Height - y - 1;
		Pixel_t Cur_Pixel = Pixel_mas[y * head_info.Width + x];
		if (c == 'R')
			CUR_CHAR_IND += (Cur_Pixel.R & 1) << READ_BYT;
		else if (c == 'B')
			CUR_CHAR_IND += (Cur_Pixel.B & 1) << READ_BYT;
		else if (c == 'G')
			CUR_CHAR_IND += (Cur_Pixel.G & 1) << READ_BYT;
		READ_BYT++;
		if (READ_BYT == CNT_BYTS_FOR_STEGO)
		{
			fwrite(&DECODE_COMB[CUR_CHAR_IND], sizeof(char), 1, fout);
			CUR_CHAR_IND = 0;
			READ_BYT = 0;
		}
		if (feof(fin))
			break;
	}
	fwrite("\n", sizeof(char), 1, fout);
	fclose(fout);
	fclose(fin);
	return 0;
}

int insert(char** argv, bmp_header_t* input_head, bmp_header_info_t* input_head_info, Pixel_t** input_Pixel_mas)
{
	bmp_header_t head = *input_head;
	bmp_header_info_t head_info = *input_head_info;
	Pixel_t* Pixel_mas = *input_Pixel_mas;
	int x, y, INT_TO_WRITE_IN_BYTS;
	char INPUT_CHAR, c;

	FILE* fkey = fopen(argv[4], "rb");
	if (fkey == NULL)
		return 1;
	FILE* fmsg = fopen(argv[5], "r");
	if (fmsg == NULL)
	{
		fclose(fkey);
		return 1;
	}
	while (!feof(fmsg))
	{
		if (fread(&INPUT_CHAR, sizeof(char), 1, fmsg) != 1)
			break;
		if (ferror(fmsg))
			break;
		if (INPUT_CHAR >= 'A' && INPUT_CHAR <= 'Z') INT_TO_WRITE_IN_BYTS = INPUT_CHAR - 'A';
		else if (INPUT_CHAR == ' ') INT_TO_WRITE_IN_BYTS = 26;
		else if (INPUT_CHAR == '.') INT_TO_WRITE_IN_BYTS = 27;
		else if (INPUT_CHAR == ',') INT_TO_WRITE_IN_BYTS = 28;
		for (int i = 0; i < CNT_BYTS_FOR_STEGO; ++i)
		{
			if (fscanf(fkey, "%d %d %c\n", &x, &y, &c) != 3)
				break;
			if (ferror(fkey))
				break;

			y = head_info.Height - y - 1;
			Pixel_t* Cur_Pixel = &Pixel_mas[y * head_info.Width + x];
			if (c == 'R')
			{
				(*Cur_Pixel).R -= (*Cur_Pixel).R & 1;
				(*Cur_Pixel).R += INT_TO_WRITE_IN_BYTS % 2;
			}
			else if (c == 'B')
			{
				(*Cur_Pixel).B -= (*Cur_Pixel).B & 1;
				(*Cur_Pixel).B += INT_TO_WRITE_IN_BYTS % 2;
			}
			else if (c == 'G')
			{
				(*Cur_Pixel).G -= (*Cur_Pixel).G & 1;
				(*Cur_Pixel).G += INT_TO_WRITE_IN_BYTS % 2;
			}
			INT_TO_WRITE_IN_BYTS >>= 1;
			if (feof(fkey))
				break;
		}
		if (feof(fmsg))
			break;
	}
	fclose(fmsg);
	fclose(fkey);
	if (save_bmp(argv[3], &head, &head_info, &Pixel_mas)) return 1;
	return 0;
}