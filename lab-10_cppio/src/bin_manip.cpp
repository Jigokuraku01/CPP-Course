#include "bin_manip.h"

int Manip::get_bin_flag()
{
    static int flag = std::ios_base::xalloc();
    return flag;
}

std::ostream &Manip::bin(std::ostream &os)
{
    os.iword(get_bin_flag()) = 1;
    return os;
}

std::ostream &Manip::nobin(std::ostream &os)
{
    os.iword(get_bin_flag()) = 0;
    return os;
}

std::istream &Manip::bin(std::istream &is)
{
    is.iword(get_bin_flag()) = 1;
    return is;
}

std::istream &Manip::nobin(std::istream &is)
{
    is.iword(get_bin_flag()) = 0;
    return is;
}

Manip::WriteInt32Bin_t Manip::write_le_int32(int x)
{
    return Manip::WriteInt32Bin_t{x};
}
Manip::WriteBoolBin_t Manip::write_bool(bool x)
{
    return Manip::WriteBoolBin_t{x};
}
Manip::WriteStrBin_t Manip::write_c_str(char *x)
{
    return Manip::WriteStrBin_t{x};
}

std::ostream &Manip::operator<<(std::ostream &os, const WriteInt32Bin_t &manip)
{
    int32_t tmp = manip.x;
    os.put(static_cast<char>(tmp & ChAllOnes));
    os.put(static_cast<char>((tmp >> 8) & ChAllOnes));
    os.put(static_cast<char>((tmp >> 16) & ChAllOnes));
    os.put(static_cast<char>((tmp >> 24) & ChAllOnes));
    return os;
}
std::ostream &Manip::operator<<(std::ostream &os, const WriteBoolBin_t &manip)
{
    os.put(manip.x ? static_cast<char>(1) : static_cast<char>(0));
    return os;
}
std::ostream &Manip::operator<<(std::ostream &os, const WriteStrBin_t &manip)
{
    os.write(manip.x, strlen(manip.x) + 1);
    return os;
}

Manip::ReadInt32Bin_t Manip::read_le_int32(int &x)
{
    return Manip::ReadInt32Bin_t{x};
}
Manip::ReadBoolBin_t Manip::read_bool(bool &x)
{
    return Manip::ReadBoolBin_t{x};
}
Manip::ReadStrBin_t Manip::read_c_str(char *x, int32_t size)
{
    return Manip::ReadStrBin_t{x, size};
}

std::istream &Manip::operator>>(std::istream &is, const Manip::ReadInt32Bin_t &manip)
{
    char byte[4];
    is.read(byte, 4);
    manip.x = (static_cast<unsigned char>(byte[0])) | (static_cast<unsigned char>(byte[1]) << 8) | (static_cast<unsigned char>(byte[2]) << 16) | (static_cast<unsigned char>(byte[3]) << 24);
    return is;
}
std::istream &Manip::operator>>(std::istream &is, const Manip::ReadBoolBin_t &manip)
{
    char tmp;
    is.get(tmp);
    manip.x = (tmp != 0);
    return is;
}
std::istream &Manip::operator>>(std::istream &is, const Manip::ReadStrBin_t &manip)
{
    char tmp_chr;
    int32_t cur_pos = 0;
    is.get(tmp_chr);
    while (tmp_chr == ' ')
        is.get(tmp_chr);
    while ((tmp_chr != ' ' && tmp_chr != 0))
    {
        manip.x[cur_pos] = tmp_chr;
        cur_pos++;
        is.get(tmp_chr);
    }
    return is;
}