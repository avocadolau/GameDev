#pragma once

template<class TYPE>

class vec3
{
public:

	TYPE x, y, z;

	vec3()
	{}

	vec3(const vec3<TYPE>& v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	vec3(const TYPE& x, const TYPE& y, const TYPE& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// OPERATORS
	vec3 operator -(const vec3& v) const
	{
		vec3 r;

		r.x = x - v.x;
		r.y = y - v.y;
		r.z = z - v.z;

		return(r);
	}

	vec3 operator + (const vec3& v) const
	{
		vec3 r;

		r.x = x + v.x;
		r.y = y + v.y;
		r.z = z + v.z;

		return(r);
	}

	const vec3& operator -=(const vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return(*this);
	}

	const vec3& operator +=(const vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return(*this);
	}

	bool operator ==(const vec3& v) const
	{
		return (x == v.x && y == v.y && z==v.z);
	}

	// METHODS

	vec3& SetToZero()
	{
		x = y = z = 0;
		return(*this);
	}

	TYPE DistanceTo(const vec3& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;
		TYPE fz = z - v.z;

		return sqrtf((fx * fx) + (fy * fy));
	}

	vec3 Normalize() {
		TYPE lenght = sqrt(x * x + y * y + z * z);
		vec3 n;
		n.x /= lenght;
		n.y /= lenght;
		n.z /= lenght;

		return n;
	}
};

typedef vec3<int> ivec3;
//typedef vec3<float> ivec3;