#ifndef _Vector3_H_
#define _Vector3_H_
class Vector3{
public:
    Vector3() { x = y = z = 0; }
    Vector3(float a, float b, float c)
    {
        x = a, y = b, z = c;
    }
    float x, y, z;
    void out();
    Vector3 &normalize();
    float Lenth();
    float sqrLenth();
    Vector3 &copy(const Vector3 &v);
    Vector3 multiply(float n);
    Vector3 operator+(const Vector3 &v);
    Vector3 operator-(const Vector3 &v);
    float operator*(const Vector3 &v);   //vector dot multiply
    Vector3 operator^(const Vector3 &v); //vector cross multiply
    bool operator==(const Vector3 &v);
	Vector3 &operator=(const Vector3 &v);
	Vector3 operator/(float n);
};
#endif