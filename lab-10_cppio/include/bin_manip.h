#ifndef LAB10_MANIP_H_INCLUDED
#define LAB10_MANIP_H_INCLUDED

#include <ostream>
#include <istream>
#include <cstring>

const char ChAllOnes = 0xFF;

namespace Manip
{
	std::ostream &bin(std::ostream &os);
	std::ostream &nobin(std::ostream &os);
	std::istream &bin(std::istream &is);
	std::istream &nobin(std::istream &is);
	int get_bin_flag();

	typedef struct
	{
		int32_t x;
	} WriteInt32Bin_t;

	typedef struct
	{
		bool x;
	} WriteBoolBin_t;

	typedef struct
	{
		char *x;
	} WriteStrBin_t;

	typedef struct
	{
		int32_t &x;
	} ReadInt32Bin_t;

	typedef struct
	{
		bool &x;
	} ReadBoolBin_t;

	typedef struct
	{
		char *x;
		int32_t size;
	} ReadStrBin_t;

	WriteInt32Bin_t write_le_int32(int x);
	WriteBoolBin_t write_bool(bool x);
	WriteStrBin_t write_c_str(char *x);

	ReadInt32Bin_t read_le_int32(int &x);
	ReadBoolBin_t read_bool(bool &x);
	ReadStrBin_t read_c_str(char *x, int32_t size);

	std::ostream &operator<<(std::ostream &os, const WriteInt32Bin_t &manip);
	std::ostream &operator<<(std::ostream &os, const WriteBoolBin_t &manip);
	std::ostream &operator<<(std::ostream &os, const WriteStrBin_t &manip);

	std::istream &operator>>(std::istream &is, const ReadInt32Bin_t &manip);
	std::istream &operator>>(std::istream &is, const ReadBoolBin_t &manip);
	std::istream &operator>>(std::istream &is, const ReadStrBin_t &manip);
}

#endif