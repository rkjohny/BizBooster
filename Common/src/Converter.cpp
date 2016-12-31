/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#include "Converter.h"
#include <sstream>
#include <iomanip>

namespace Common {

int64_t Converter::ToInt32(const std::string &num, int8_t base) throw (std::invalid_argument, std::out_of_range)
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
        sout << std::showbase // show the 0x prefix 
                << std::internal // fill between the prefix and the number
                << std::setfill('0'); // fill with 0s
        sout << std::hex << std::setw(4) << std::uppercase << n;
        break;

    case 8:
        sout << std::oct << n;
        break;
    }
    return sout.str();
}

std::string Converter::ToHexStr(const std::vector<uint8_t> &vec)
{
    std::ostringstream sout;

    sout << std::internal // fill between the prefix and the number
            << std::setfill('0'); // fill with 0s
    for (auto &value : vec) {
        sout << std::hex << std::setw(2) << std::uppercase << (uint32_t) value;
    }
    return sout.str();
}

std::string Converter::ToHexStr(const uint8_t *arr, int length)
{
    std::ostringstream sout;

    sout << std::internal // fill between the prefix and the number
            << std::setfill('0'); // fill with 0s

    for (int i = 0; i < length; i++) {
        sout << std::hex << std::setw(2) << std::uppercase << (uint32_t) arr[i];
    }
    
    return sout.str();

#if 0    
    char *p = new char[length * 2];
    int ln = 0;
    for (int i = 0; i < length; i++) {
        ln += snprintf((p + ln), (length * 2), "%02X", (uint32_t) arr[i]);
    }
    std::string s(p);
    delete p;
    return s;
#endif
}

}