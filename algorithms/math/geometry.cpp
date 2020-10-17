#include <cmath>


// Use the cosine formula to find the angle of a and b sides if the length of all sides are correct.
float angle_of_triangle(float a, float b, float c) {
    auto const PI = 3.14159265;
    
    auto cos_of_angle = acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (a * b * 2));
    
    return cos_of_angle * 180 / PI;
}
