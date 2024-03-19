#pragma once

#include <string>

class NZ_String
{
public:
    static std::string replace(
        const std::string& s,
        const std::string& find_s,
        const std::string& replace_s
    )
    {
        std::string temp(s);
        std::size_t pos;

        while ((pos = temp.find(find_s)) != std::string::npos)
        {
            temp = temp.replace(pos, find_s.length(), replace_s);
        }

        return temp;
    }
};