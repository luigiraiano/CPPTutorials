#ifndef BOX_H
#define BOX_H

#include "utils.h"

class Box
{
public:
    /**
     * @brief Box defines a box by specifying its width x length x height in meters
     * @param x: box width
     * @param y: box length
     * @param z: box height
     */
    Box(const double& x, const double& y, const double& z);

    /**
     * @brief Box defines an intialized box.
     */
    Box() {}

public:
    double getVolume(){volume = (x_ * y_ * z_); return volume;}
    double getVolume(double (*volumeFunction)(const double&, const double&, const double&) );
    double getVolume(const double& x, const double& y, const double& z, double (*volumeFunction)(const double&, const double&, const double&) );

    void setWidth(const double& val) {x_ = val;}
    void setLength(const double& val) {x_ = val;}
    void setHeight(const double& val) {x_ = val;}

    static int getUseCounts() {return uses_;}

public:
    Box operator+(const Box& box)
    {
        Box box_res;
        box_res.x_ = this->x_ + box.x_;
        box_res.y_ = this->y_ + box.y_;
        box_res.z_ = this->z_ + box.z_;

        return box_res;
    }

private:
    double x_{0},y_{0},z_{0};
    double volume{0};
    static int uses_;
};

#endif // BOX_H
