#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

class Vector2 { // 2-dimensional vector which could be useful for readability and ease of use in the swerve code
    public: 
        long double x;
        long double y;
    
        Vector2(long double x_input, long double y_input, std::string type);
        Vector2 ZeroVector();
        Vector2 MirrorX(Vector2 vector_1);
        Vector2 Rotate(Vector2 vector_1, long double angle_1);
        Vector2 ToUnitCircle(Vector2 vector_1);

        long double angle();
        long double length();
        std::string values();

};

Vector2 operator-(Vector2 vector_1); // -vector
Vector2 operator+(const Vector2 vector_1, const Vector2 vector_2); // vector + vector
Vector2 operator-(const Vector2 vector_1, const Vector2 vector_2); // vector - vector
Vector2 operator*(const Vector2 vector_to_multiply, long double scalar); // vector * scalar
Vector2 operator*(long double scalar, const Vector2 vector_to_multiply); // scalar * vector