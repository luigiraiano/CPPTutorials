#include <../include/CPPTutorials/Box.h>

int Box::uses_ = 0;

/**
 * @brief Box defines a box by specifying its width x length x height in meters
 * @param x: box width
 * @param y: box length
 * @param z: box height
 */
Box::Box(const double& x, const double& y, const double& z)
{
    static int uses = 0;
    x_ = x;
    y_ = y;
    z_ = z;

    uses_++;
}

double Box::getVolume(double (*volumeFunction)(const double&, const double&, const double&) )
{
    return (*volumeFunction)(x_,y_,z_);
}

double Box::getVolume(const double& x, const double& y, const double& z, double (*volumeFunction)(const double&, const double&, const double&) )
{
    return (*volumeFunction)(x,y,z);
}
