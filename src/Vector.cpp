#include "Vector.h"
#include "Graphics.h"

#include <cmath>

Vector::Vector(){
	x=0;
	y=0;
}
Vector::Vector(double x, double y):x(x),y(y){}

void Vector::toSemiLogPixelMag(){
	int slogstep = Graphics::window_width / 4;
	
	int i;
	double j;	
	if(log10(x)<0){
		i = 0;
		j = x*10;
	}else {
		i = log10(x)+1;
		j = (x/pow(10,i-1));
	}

	x = (i + log10(j))*slogstep;
	y = (y*Graphics::window_height/80) + Graphics::window_height/4;
}

void Vector::toSemiLogPixelPhase(){
	int slogstep = Graphics::window_width / 4;
	
	int i;
	double j;	
	if(log10(x)<0){
		i = 0;
		j = x*10;
	}else {
		i = log10(x)+1;
		j = (x/pow(10,i-1));
	}

	x = (i + log10(j))*slogstep;
	y = (y*Graphics::window_height/(4*90)) + 2*Graphics::window_height/4;
}

Vector Vector::operator+(const Vector &v) const
{
	return Vector(x + v.x, y + v.y);
}
Vector Vector::operator-(const Vector &v) const
{
	return Vector(x - v.x, y - v.y);
}
Vector Vector::operator*(const float scale) const
{
	return Vector(x * scale, y * scale);
}
Vector Vector::operator/(const float scale) const
{
	return Vector(x / scale, y / scale);
}
Vector Vector::operator-()
{
	return Vector(-1 * x, -1 * y);
}
float Vector::operator*(const Vector &v) const
{
	return (x * v.x + y * v.y);
}

bool Vector::operator==(const Vector &v) const
{
	return (x == v.x) && (y == v.y);
}
bool Vector::operator!=(const Vector &v) const
{
	return (x != v.x) || (y != v.y);
}

Vector &Vector::operator+=(const Vector &v)
{
	x += v.x;
	y += v.y;
	return *this;
}
Vector &Vector::operator-=(const Vector &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

