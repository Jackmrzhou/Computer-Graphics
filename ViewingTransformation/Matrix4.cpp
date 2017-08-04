#include "Matrix4.hpp"
#include "Vector3.hpp"

Matrix4::Matrix4() 
{
	for (int i = 0; i != 4; ++i)
		for (int j = 0; j != 4; ++j)
			data[i][j] = 0;
}

Matrix4::Matrix4(const Matrix4 &m)
{
	for (int r = 0; r != 4; ++r)
		for (int c = 0; c != 4; ++c)
			data[r][c] = m.data[r][c];
}

Matrix4::Matrix4(const Vector3 &v1, const Vector3 &v2,
				const Vector3 &v3, const Vector3 &v4)
{
	data[0][0] = v1.x, data[1][0] = v1.y, data[2][0] = v1.z;
	data[0][1] = v2.x, data[1][1] = v2.y, data[2][1] = v2.z;
	data[0][2] = v3.x, data[1][2] = v3.y, data[2][2] = v3.z;
	data[0][3] = v4.x, data[1][3] = v4.y, data[2][3] = v4.z;
	data[3][0] = data[3][1] = data[3][2] = 0;
	data[3][3] = 1;
}

Matrix4 Matrix4::operator*(const Matrix4 &m)
{
	Matrix4 res;
	for (int i = 0; i != 4; ++i)
		for (int j = 0; j != 4; ++j)
			for (int k = 0; k != 4; ++k)
				res.data[i][j] += data[i][k] * m.data[k][j];
	return res;
}

Vector3 Matrix4::operator*(const Vector3 &v)
{
	return Vector3(data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z + data[0][3],
				data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z + data[1][3],
				data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z + data[2][3]);
}