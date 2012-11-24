#include "sphere.h"
#include <math.h>
#define PI 3.14159f
#define TWOPI (2.0f * PI)

//constructor given  center, radius, and material
sphere::sphere(Vec3f c, float r, int m, scene* s) : rtObject(s)  
{
	center = c;
	radius = r;
	matIndex = m;
	myScene = s;
}

float sphere::testIntersection(Vec3f eye, Vec3f dir)
{
	float A = dir.Dot3(dir);
	float B = (eye - center).Dot3(dir) * 2.0;
	float C = (eye - center).Dot3(eye - center) - radius * radius;

	float discriminant = (B * B) - 4.0 * A * C;

	float t = 9999999;
	if (discriminant > 0.0) {
		float tMinus	= (-B/2.0 - sqrt(pow(B/2.0, 2.0) - A * C)) / A;
		float tPlus		= (-B/2.0 + sqrt(pow(B/2.0, 2.0) - A * C)) / A;

		if (tMinus > 0.0 && tPlus > 0.0) {
			t = min(tMinus, tPlus);
		} else if (tMinus > 0.0 || tPlus > 0.0) {
			t = max(tMinus, tPlus);
		} else {
			t = 9999999;
		}
	}

	return t;
}

Vec3f sphere::getNormal(Vec3f eye, Vec3f dir)
{
	//once you can test for intersection,
	//simply add (distance * view direction) to the eye location to get surface location,
	//then subtract the center location of the sphere to get the normal out from the sphere
	Vec3f normal = (eye + dir) - center;

	//dont forget to normalize
	normal.Normalize();

	return normal;
}

Vec3f sphere::getTextureCoords(Vec3f eye, Vec3f dir)
{
	//find the normal as in getNormal
	Vec3f normal = getNormal(eye, dir);

	//use these to find spherical coordinates
	Vec3f x(1.0f,0.0f,0.0f);
	Vec3f z(0.0f,0.0f,1.0f);

	//phi is the angle down from z
	//theta is the angle from x curving toward y
	//hint: angle between two vectors is the acos() of the dot product

	//find phi using normal and z
	float phi		= acos(normal.Dot3(z));

	//find the x-y projection of the normal
	Vec3f xyProj(normal.x(), normal.y(), 0);
	xyProj.Normalize();

	//find theta using the x-y projection and x
	float theta		= acos(xyProj.Dot3(x));

	if (xyProj.y() < 0)
		theta = TWOPI - theta;
	
	//return coordinates scaled to be between 0 and 1
	Vec3f coords;
	coords.Set(theta/TWOPI, phi / PI, 0);
	return coords;
}