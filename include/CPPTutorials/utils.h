#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <memory>
#include <string>

namespace Utils
{

inline double computeBoxVolume(const double& x, const double& y, const double& z)
{
    return (x * y * z);
}

} // namespace Utils

#endif // UTILS_H
