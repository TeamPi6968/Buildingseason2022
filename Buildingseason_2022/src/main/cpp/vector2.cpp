#include "Vector2.h"
#include <sstream>
#include <iostream>

namespace patch {
    template <typename T>
    std::string to_string(const T &n)
    {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
}

Vector2::Vector2(long double x_input, long double y_input, std::string type = "cartesian") { // type should be "cartesian" or "polar"
    if (type == "cartesian")
    {
        x = x_input;
        y = y_input;
    }
    else
    {                                            // when vector type is not cartesian, type is assumed to be polar
        x = x_input * cos(y_input * M_PI / 180); // x_input is r and y_input is theta, in DEGREES (not radians)
        y = x_input * sin(y_input * M_PI / 180);
    }
}

long double Vector2::angle() {
    long double angle_180 = atan2(y, x) * 180 / M_PI;
    // std::cout << angle_180 << " " << atan2(y,x) << "\n";
    if (angle_180 < 0)
    {
        return 360 + angle_180;
    }
    return angle_180;
}

long double Vector2::length() {
    return sqrt(y * y + x * x);
}

Vector2 operator-(const Vector2 vector_1) {
    return Vector2(-vector_1.x, -vector_1.y);
}

Vector2 operator+(const Vector2 vector_1, const Vector2 vector_2) {
    return Vector2(vector_1.x + vector_2.x, vector_1.y + vector_2.y);
}

Vector2 operator-(const Vector2 vector_1, const Vector2 vector_2) {
    return Vector2(vector_1.x - vector_2.x, vector_1.y - vector_2.y);
}

Vector2 operator*(const Vector2 vector_to_multiply, long double scalar) {
    return Vector2(scalar * vector_to_multiply.x, scalar * vector_to_multiply.y);
}

Vector2 operator*(long double scalar, const Vector2 vector_to_multiply) {
    return Vector2(scalar * vector_to_multiply.x, scalar * vector_to_multiply.y);
}

std::string Vector2::values() {
    return "x: " + patch::to_string(this->x) + ", y: " + patch::to_string(this->y) + ", length: " + patch::to_string(this->length()) + ", angle: " + patch::to_string(this->angle());
}

int main() {   
    Vector2 wheel1(1, 2);
    Vector2 wheel2(-5, 1);
    Vector2 wheel3 = wheel1 + wheel2;
    Vector2 wheel4(2, 0);
    Vector2 wheel5 = 5 * wheel4;
    Vector2 wheel6 = -wheel5;
    Vector2 wheel7(10, 180, "polar");
    std::cout << wheel1.values() << "\n";
    std::cout << wheel2.values() << "\n";
    std::cout << wheel3.values() << "\n";
    std::cout << wheel4.values() << "\n";
    std::cout << wheel5.values() << "\n";
    std::cout << wheel6.values() << "\n";
    std::cout << wheel7.values() << "\n";
    std::cout << "it4" << "\n";
}