#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>

template <typename T>
std::string to_string(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

#endif // UTILS_H

