#ifndef VECTOR_H
#define VECTOR_H

class Vector{
public:
	double x,y;

	Vector();
	Vector(double, double);

	void toSemiLogPixelMag();
	void toSemiLogPixelPhase();
	Vector operator+(const Vector &v) const;
	Vector operator-(const Vector &v) const;
	Vector operator*(const float s) const;
	Vector operator/(const float s) const;
	Vector operator-();
	float operator*(const Vector &v) const;

	bool operator==(const Vector &v) const;
	bool operator!=(const Vector &v) const;

	Vector &operator+=(const Vector &v);
	Vector &operator-=(const Vector &v);
};

#endif
