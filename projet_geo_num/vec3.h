#ifndef vec3_H
#define vec3_H


class vec3
{
public:
    vec3(float x = 0.f, float y=0.f, float z=0.f);
    float x;
    float y;
    float z;
        //FUNCTION
    vec3 operator*(float scalaire);
};

#endif // vec3_H
