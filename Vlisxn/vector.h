#pragma once

#include "sse.h"

typedef float matrix3x4_t[3][4];

#define pi 3.14159265358979323846
//#define rad(a) a*(pi/180)
//#define deg(a) a*(180/pi)
#define rad(a) a * 0.01745329251
#define deg(a) a * 57.295779513082

class Vector
{
public:
	Vector(float a = 0,float b = 0,float c = 0) { x = a; y = b; z = c; }
	//Vector( float *i ) { x = i[0]; y = i[1]; z = i[2]; };

	inline void operator=(Vector a) { x = a.x; y = a.y; z = a.z; }
	inline bool operator!() { return !x && !y && !z; }
	inline bool operator!=(Vector a) { return x != a.x || y != a.y || z != a.z; }
	inline float& operator[](int i) { return ((float*)this)[i]; }
	inline Vector operator+(Vector a) { return Vector(x+a.x,y+a.y,z+a.z); }
	inline Vector operator-(Vector a) { return Vector(x-a.x,y-a.y,z-a.z); }
	inline Vector operator*(Vector a) { return Vector(x*a.x,y*a.y,z*a.z); }
	inline Vector operator/(Vector a) { return Vector(x/a.x,y/a.y,z/a.z); }
	inline void operator+=(Vector a) { *this = Vector(x+a.x,y+a.y,z+a.z); }
	inline void operator-=(Vector a) { *this = Vector(x-a.x,y-a.y,z-a.z); }
	inline void operator*=(Vector a) { *this = Vector(x*a.x,y*a.y,z*a.z); }
	inline void operator/=(Vector a) { *this = Vector(x/a.x,y/a.y,z/a.z); }
	inline Vector operator*(float a) { return Vector(x*a,y*a,z*a); }
	inline Vector operator/(float a) { return Vector(x/a,y/a,z/a); }
	inline void operator*=(float a) { *this = Vector(x*a,y*a,z*a); }
	inline void operator/=(float a) { *this = Vector(x/a,y/a,z/a); }
	inline float Length() { return sqrt2(x*x+y*y+z*z); }
	inline float Dot(Vector a) { return x*a.x+y*a.y+z*a.z; }
	inline float DotAbs(Vector a) { return fabsf(x*a.x)+fabsf(y*a.y)+fabsf(z*a.z); }
	inline Vector Cross(Vector a) { return Vector(y*a.z - z*a.y,z*a.x - x*a.z,x*a.y - y*a.x); }

	inline Vector Angle(Vector* up = 0)
	{
		if (!x && !y)
			return Vector(0,0,0);

		float roll = 0;

		if (up)
		{
			Vector left = (*up).Cross(*this);

			roll = deg(atan2f(left.z,(left.y * x) - (left.x * y)));
		}

		return Vector(deg(atan2f(-z,sqrtf(x*x+y*y))),deg(atan2f(y,x)),roll);
	}
	inline Vector Forward()
	{
		float cp, cy, sp, sy;

		SinCos(rad(x),sp,cp);
		SinCos(rad(y),sy,cy);

		return Vector(cp*cy,cp*sy,-sp);
	}
	inline Vector Right()
	{
		float sp,sy,sr,cp,cy,cr;

		SinCos(rad(x),sp,cp);
		SinCos(rad(y),sy,cy);
		SinCos(rad(z),sr,cr);

		return Vector(-1*sr*sp*cy+-1*cr*-sy,-1*sr*sp*sy+-1*cr*cy,-1*sr*cp);
	}
	inline Vector Up()
	{
		float sp,sy,sr,cp,cy,cr;

		SinCos(rad(x),sp,cp);
		SinCos(rad(y),sy,cy);
		SinCos(rad(z),sr,cr);

		return Vector(cr*sp*cy+-sr*-sy,cr*sp*sy+-sr*cy,cr*cp);
	}

	// clamp viewangles
	inline void clampAngles() {
		if( x != x )
			x = 0;

		if( y != y )
			y = 0;

		if( x > 89 )
			x = 89;

		if( x < -89 )
			x = -89;

		if( y > 180 )
			y -= 360;

		if( y < -180 )
			y += 360;

		if( y > 180 )
			y = 180;

		if( y < -180 )
			y = -180;

		z = 0;
	}

	// clamp move
	inline void clampMove() {
		if( x > 10000 )
			x = 10000;

		if( x < -10000 )
			x = -10000;

		if( y > 10000 )
			y = 10000;

		if( y < -10000 )
			y = -10000;

		z = 0;
	}

	float x,y,z;
};

template<typename t> void clamp( t &num, float fmin, float fmax ) {
	num = ( (num < fmin) ? fmin : ( (num > fmax) ? fmax : num ) );
}

inline void VectorTransform( Vector in, matrix3x4_t &matrix, Vector &out ) {
	out.x = in.Dot(Vector(matrix[0][0], matrix[0][1], matrix[0][2])) + matrix[0][3];
	out.y = in.Dot(Vector(matrix[1][0], matrix[1][1], matrix[1][2])) + matrix[1][3];
	out.z = in.Dot(Vector(matrix[2][0], matrix[2][1], matrix[2][2])) + matrix[2][3];
}

inline void MatrixPosition( matrix3x4_t &matrix, Vector &out ) {
	out.x = matrix[0][3];
	out.y = matrix[1][3];
	out.z = matrix[2][3];
}

inline void VectorRotate( Vector &in, matrix3x4_t &matrix ) {
	in.x = in.Dot( Vector(matrix[0][0], matrix[0][1], matrix[0][2]) );
	in.y = in.Dot( Vector(matrix[1][0], matrix[1][1], matrix[1][2]) );
	in.z = in.Dot( Vector(matrix[2][0], matrix[2][1], matrix[2][2]) );
}

inline void matrixFromAngles( Vector origin, Vector angs, matrix3x4_t &matrix ) {
	Vector forward, right, up;
	forward = angs.Forward();
	right = angs.Right();
	up = angs.Up();
	matrix[0][0] = forward[0];
	matrix[1][0] = forward[1];
	matrix[2][0] = forward[2];
	matrix[0][1] = right[0];
	matrix[1][1] = right[1];
	matrix[2][1] = right[2];
	matrix[0][2] = up[0];
	matrix[1][2] = up[1];
	matrix[2][2] = up[2];
	matrix[0][3] = origin.x;
	matrix[1][3] = origin.y;
	matrix[2][3] = origin.z;
}

inline void rotateAABB( matrix3x4_t &matrix, Vector &mins, Vector &maxs ) {
	Vector center;
	center = (mins + maxs) * 0.5;

	Vector extents;
	extents = maxs - center;

	Vector newCenter;
	VectorRotate( center, matrix );

	Vector newExtents;
	newExtents.x = extents.DotAbs( Vector(matrix[0][0], matrix[0][1], matrix[0][2]) );
	newExtents.y = extents.DotAbs( Vector(matrix[1][0], matrix[1][1], matrix[1][2]) );
	newExtents.z = extents.DotAbs( Vector(matrix[2][0], matrix[2][1], matrix[2][2]) );

	mins = newCenter - newExtents;
	maxs = newCenter + newExtents;
}

inline void transformAABB( matrix3x4_t &matrix, Vector &mins, Vector &maxs ) {
	Vector center;
	center = (mins + maxs) * 0.5;

	Vector extents;
	extents = maxs - center;

	Vector worldCenter;
	VectorTransform( center, matrix, worldCenter );

	Vector worldExtents;
	worldExtents.x = extents.DotAbs( Vector(matrix[0][0], matrix[0][1], matrix[0][2]) );
	worldExtents.y = extents.DotAbs( Vector(matrix[1][0], matrix[1][1], matrix[1][2]) );
	worldExtents.z = extents.DotAbs( Vector(matrix[2][0], matrix[2][1], matrix[2][2]) );

	mins = worldCenter - worldExtents;
	maxs = worldCenter + worldExtents;
}