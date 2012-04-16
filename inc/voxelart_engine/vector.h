#ifndef VOXELART_VECTOR_H
#define VOXELART_VECTOR_H
#include <math.h>
namespace vaEngine {
	class Vector
	{
	    public:
	    
		float   x;
		float   y;
		float   z;
		
		Vector() { x = y = z = 0.0f; }
		
		Vector(float r, float s, float t)
		{
		    x = r;
		    y = s;
		    z = t;
		}
		
		Vector& Set(float r, float s, float t)
		{
		    x = r;
		    y = s;
		    z = t;
		    return (*this);
		}

		float& operator [](long k)
		{
		    return ((&x)[k]);
		}
		
		const float& operator [](long k) const
		{
		    return ((&x)[k]);
		}
		
		Vector& operator +=(const Vector& v)
		{
		    x += v.x;
		    y += v.y;
		    z += v.z;
		    return (*this);
		}
		
		Vector& operator -=(const Vector& v)
		{
		    x -= v.x;
		    y -= v.y;
		    z -= v.z;
		    return (*this);
		}
		
		Vector& operator *=(float t)
		{
		    x *= t;
		    y *= t;
		    z *= t;
		    return (*this);
		}
		
		Vector& operator /=(float t)
		{
		    float f = 1.0F / t;
		    x *= f;
		    y *= f;
		    z *= f;
		    return (*this);
		}
		
		Vector& operator %=(const Vector& v)
		{
		    float       r, s;
		    
		    r = y * v.z - z * v.y;
		    s = z * v.x - x * v.z;
		    z = x * v.y - y * v.x;
		    x = r;
		    y = s;
		    
		    return (*this);
		}
		
		Vector& operator &=(const Vector& v)
		{
		    x *= v.x;
		    y *= v.y;
		    z *= v.z;
		    return (*this);
		}
		
		Vector operator -(void) const
		{
		    return (Vector(-x, -y, -z));
		}
		
		Vector operator -(const Vector& v) const
		{
		    return (Vector(x - v.x, y - v.y, z - v.z));
		}

		Vector operator +(const Vector& v) const
		{
		    return (Vector(x + v.x, y + v.y, z + v.z));
		}
	
		Vector operator *(float t) const
		{
		    return (Vector(x * t, y * t, z * t));
		}

		Vector operator *(const Vector& v) const
		{
		    return (Vector(x * v.x, y * v.y, z * v.z));
		}

		Vector operator /(float t) const
		{
		    float f = 1.0F / t;
		    return (Vector(x * f, y * f, z * f));
		}

		Vector operator /(const Vector& v) const
		{
		    return (Vector(x / v.x, y / v.y, z / v.z));
		}

		
		Vector operator %(const Vector& v) const
		{
		    return (Vector(y * v.z - z * v.y, z * v.x - x * v.z,
		            x * v.y - y * v.x));
		}
		
		Vector operator &(const Vector& v) const
		{
		    return (Vector(x * v.x, y * v.y, z * v.z));
		}
		
		bool operator ==(const Vector& v) const
		{
		    return ((x == v.x) && (y == v.y) && (z == v.z));
		}
		
		bool operator !=(const Vector& v) const
		{
		    return ((x != v.x) || (y != v.y) || (z != v.z));
		}
		
		Vector& Normalize(void)
		{
		    return (*this /= sqrtf(x * x + y * y + z * z));
		}

     		float length(){
       			return (float)sqrt(x*x+y*y+z*z);
		}

		Vector* cross(Vector* b){
			return new Vector(y*b->z - z*b->y, z*b->x-x*b->z,x*b->y-y*b->x);
		}
	};
}
#endif
