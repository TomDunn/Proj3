#include "triangle.h"

//constructor given  center, radius, and material
triangle::triangle(Vec3f p0, Vec3f p1, Vec3f p2, float tx0, float tx1, float tx2, float ty0, float ty1, float ty2, int m, scene* s) : rtObject(s)  
{
	point0 = p0;
	point1 = p1;
	point2 = p2;
	texX0 = tx0;
	texX1 = tx1;
	texX2 = tx2;
	texY0 = ty0;
	texY1 = ty1;
	texY2 = ty2;
	matIndex = m;
	myScene = s;
}

float triangle::testIntersection(Vec3f eye, Vec3f dir)
{
	// from ray tracing chapter of red book
	Vec3f A = point0, B = point1, C = point2;

	float	a = A[0] - B[0],
			b = A[1] - B[1],
			c = A[2] - B[2],
			d = A[0] - C[0],
			e = A[1] - C[1],
			f = A[2] - C[2],
			g = dir[0],
			h = dir[1],
			i = dir[2],
			j = A[0] - eye[0],
			k = A[1] - eye[1],
			l = A[2] - eye[2];

	float M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);
	float beta =
		(j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g)) / M;
	float gamma =
		(i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
	float t = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c)) / M;

	if (t < 0.0 || gamma > 1.0 || gamma < 0.0 || beta > (1.0 - gamma) || beta < 0.0) {
		return 9999999;
	}
	return t;
}

Vec3f triangle::getNormal(Vec3f eye, Vec3f dir)
{
	//construct the barycentric coordinates for the plane
	Vec3f bary1 = point1-point0;
	Vec3f bary2 = point2-point0;

	//cross them to get the normal to the plane
	//note that the normal points in the direction given by right-hand rule
	//(this can be important for refraction to know whether you are entering or leaving a material)
	Vec3f normal;
	Vec3f::Cross3(normal,bary1,bary2);
	normal.Normalize();

	return normal;
}

Vec3f triangle::getTextureCoords(Vec3f eye, Vec3f dir)
{
	//find alpha and beta (parametric distance along barycentric coordinates)
	//use these in combination with the known texture surface location of the vertices
	//to find the texture surface location of the point you are seeing

	Vec3f coords;
	return coords;
}