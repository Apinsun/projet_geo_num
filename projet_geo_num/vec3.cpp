#include "vec3.h"

vec3::vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{}

vec3 vec3::operator *(float scalaire){
    vec3 vReturn;
    vReturn.x = this->x  * scalaire;
    vReturn.y = this->y  * scalaire;
    vReturn.z = this->z  * scalaire;
    return vReturn;
}
