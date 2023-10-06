#pragma once

#include <cstdlib>
#include <ctime>

const double EPS = 1e-9; // tolerance
bool equal(const float &a, const float &b) { return std::abs(a - b) < EPS; }

template <typename T>
T operator*(const int &scalar, const T &coordinates2D) { return T{coordinates2D.m_x * scalar, coordinates2D.m_y * scalar}; }
template <typename T>
T operator*(const T &coordinates2D, const int &scalar) { return scalar * coordinates2D; }
template <typename T>
T operator*(const float &scalar, const T &coordinates2D) { return T{coordinates2D.m_x * scalar, coordinates2D.m_y * scalar}; }
template <typename T>
T operator*(const T &coordinates2D, const float &scalar) { return scalar * coordinates2D; }

class Coordinates2D
{
public:
    Coordinates2D(const float &x, const float &y) : m_x{x}, m_y{y} {}
    Coordinates2D() {}

    float m_x;
    float m_y;

    template<typename T>
    T operator+(const T &other) const { return T{m_x + other.m_x, m_y + other.m_y}; }
    template <typename T>
    T operator-(const T &other) const { return T{m_x - other.m_x, m_y - other.m_y}; }

    template <typename T>
    T &operator+=(const T &other) { return *this = *this + other; }
    template <typename T>
    T &operator-=(const T &other) { return *this = *this - other; }

    
    template <typename T>
    T &operator*=(const int &scalar) { return *this = *this * scalar; }
    template <typename T>
    T &operator*=(const float &scalar) { return *this = *this * scalar; }

    bool operator==(const Coordinates2D &other) const { return equal(m_x, other.m_x) && equal(m_y, other.m_y); }
    bool operator!=(const Coordinates2D &other) const { return !(*this == other); }
};

class Position : public Coordinates2D
{
public:
    Position(const float &x, const float &y) : Coordinates2D{x, y} {}
    Position() {}
};

class Size : public Coordinates2D
{
public:
    Size(const float &w, const float &h) : Coordinates2D{w, h} {}
    Size() {}
};

class Vector : public Coordinates2D
{
public:
    Vector(const float &x, const float &y) : Coordinates2D{x, y} {}
    Vector() {}
};

/* const */

const Position BEGIN_COORDINATES{0.0, 0.0};
const Vector VECTOR_I{1, 0};
const Vector VECTOR_NEGATIVE_I{-1, 0};
const Vector VECTOR_J{0, 1};
const Vector VECTOR_NEGATIVE_J{0, -1};


class Color
{
public:
    Color(const float &R, const float &G, const float &B) : m_R{R}, m_G{G}, m_B{B} {}
    Color() {}

    float m_R;
    float m_G;
    float m_B;
};

/* const */

const Color RED{1.0, 0.0, 0.0};
const Color DARK_RED{0.5, 0.1, 0.1};
const Color BLACK{0.0, 0.0, 0.0};
const Color WHITE{1.0, 1.0, 1.0};
const Color DARK_GREEN{0.0, 0.5, 0.0};
const Color LIGHT_GREEN{0.7, 1.0, 0.7};
const Color GREY{0.2, 0.23, 0.2};

class RNGenerator
{
    int m_min;
    int m_max;

public:
    RNGenerator(const int &min, const int &max) : m_min{min}, m_max{max} 
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }
    RNGenerator() {} 
    int generate() const { return m_min + (std::rand() % (m_max - m_min + 1)); }
};