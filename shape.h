#ifndef SHAPE_H
#define SHAPE_H

#include <cmath>
#include <stdexcept>
#include "vector.h"

const auto TAU = 3.14159265 * 2;

class Shape
{
public:
    virtual Vector operator()(float t) const = 0;
    virtual Vector tang_at(float t) const = 0;
};

class Ellipse : public Shape
{
protected:
    float ra, rb;

public:
    float get_ra() const
    {
        return ra;
    }

    float get_rb() const
    {
        return rb;
    }

    Ellipse(float ra_, float rb_)
    {
        if (ra_ <= 0 || rb_ <= 0)
        {
            throw std::runtime_error("Radius should be positive");
        }
        ra = ra_;
        rb = rb_;
    }

    virtual Vector operator()(float t) const
    {
        return Vector(ra * cos(t), rb * sin(t), 0);
    }

    virtual Vector tang_at(float t) const
    {
        return (Vector(-ra * sin(t), rb * cos(t), 0)).norm();
    }
};

class Circle : public Ellipse
{
public:
    Circle(float r) : Ellipse(r, r)
    {
    }
};

class Helix : public Circle
{
public:
    Helix(float r) : Circle(r)
    {
    }
    virtual Vector operator()(float t) const
    {
        return Vector(ra * cos(t), rb * sin(t), t / TAU);
    }

    virtual Vector tang_at(float t) const
    {
        return Vector(-ra * sin(t), rb * cos(t), 1.0f / TAU).norm();
    }
};

std::ostream &operator<<(std::ostream &out, const Ellipse &e)
{
    out << "Ellipse(" << e.get_ra() << ", " << e.get_rb() << ")";
    return out;
}

std::ostream &operator<<(std::ostream &out, const Circle &e)
{
    out << "Circle(" << e.get_ra() << ")";
    return out;
}

std::ostream &operator<<(std::ostream &out, const Helix &e)
{
    out << "Helix(" << e.get_ra() << ")";
    return out;
}
#endif