#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

class Vector2 {
    public: 
        long double x;
        long double y;
    
        Vector2(long double x_input, long double y_input) {
            x = x_input;
            y = y_input;
        }

        long double angle() {
            long double angle_180 = atan2(y,x) * 180 / M_PI;
            // std::cout << angle_180 << " " << atan2(y,x) << "\n";
            if (angle_180 < 0) {
                return 360 + angle_180;
            }
            return angle_180;
        }
        
        long double length() {
            return sqrt(y*y+x*x);
        }

        static Vector2 Vector2_polar(long double length, long double angle) {
            return Vector2(length * cos(angle * M_PI / 180), length * sin(angle * M_PI / 180));
        }

        friend Vector2 operator-(const Vector2 vector_1) {
            return Vector2(-vector_1.x, -vector_1.y);
        }

        friend Vector2 operator+(const Vector2 vector_1, const Vector2 vector_2) {
            return Vector2(vector_1.x + vector_2.x, vector_1.y + vector_2.y);
        }

        friend Vector2 operator-(const Vector2 vector_1, const Vector2 vector_2) {
            return Vector2(vector_1.x - vector_2.x, vector_1.y - vector_2.y);
        }

        friend Vector2 operator*(const Vector2 vector_to_multiply, long double scalar) {
            return Vector2(scalar * vector_to_multiply.x, scalar * vector_to_multiply.y);
        }

        friend Vector2 operator*(long double scalar, const Vector2 vector_to_multiply) {
            return Vector2(scalar * vector_to_multiply.x, scalar * vector_to_multiply.y);
        }

        //string values() {
        //    return "x: " + x + ", y: " + y + ", length: " + self.length + ", angle: " + self.angle();
        //}
};

int main() {
    Vector2 wheel1(1, 2);
    Vector2 wheel2(-5, 1);
    Vector2 wheel3 = wheel1 + wheel2;
    Vector2 wheel4(2, 0);
    Vector2 wheel5 = 5 * wheel4;
    Vector2 wheel6 = -wheel5;
    Vector2 wheel7 = Vector2_polar(10, 180);
    std::cout << wheel1.length() << " " << wheel1.angle() << "\n";
    std::cout << wheel2.length() << " " << wheel2.angle() << "\n";
    std::cout << wheel3.length() << " " << wheel3.angle() << "\n";
    std::cout << wheel4.length() << " " << wheel4.angle() << "\n";
    std::cout << wheel5.length() << " " << wheel5.angle() << "\n";
    std::cout << wheel6.length() << " " << wheel6.angle() << "\n";
    std::cout << wheel7.x << " " << wheel7.y << "\n";
    std::cout << "it4" << "\n";
}