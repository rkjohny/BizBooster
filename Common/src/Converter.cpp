
#include "Converter.h"
#include <sstream>

namespace Common {

int64_t Converter::ToInt32(std::string&& num, int8_t base) throw (std::invalid_argument, std::out_of_range)
{
#if __WORDSIZE == 32
    return std::strtoull(num.c_str(), nullptr, base);
#elif __WORDSIZE == 64
    return std::strtoul(num.c_str(), nullptr, base);
#endif
}

std::string Converter::ToStr(int32_t n, int8_t base)
{
    std::ostringstream sout;

    switch (base) {
        case 10:
            sout << std::dec << n;
            break;

        case 16:
            sout << "0x" << std::hex << std::uppercase << n;
            break;

        case 8:
            sout << std::oct  << n;
            break;
    }
    return sout.str();
}

}