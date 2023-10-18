#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

class Vector
{
private:
    float x, y, z;

public:
    float get_x() const
    {
        return x;
    }

    float get_y() const
    {
        return y;
    }

    float get_z() const
    {
        return z;
    }

    Vector(float x_, float y_, float z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }

    Vector operator+(const Vector &other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector operator*(float k) const
    {
        return {x * k, y * k, z * k};
    }

    float mag() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    Vector norm() const
    {
        return (*this) * (1 / mag());
    }
};

std::ostream &operator<<(std::ostream &out, const Vector &v)
{
    out << "Vector(" << v.get_x() << ", " << v.get_y() << ", " << v.get_z() << ")";
    return out;
}

#endif