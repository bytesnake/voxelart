#ifndef BSB_VECTOR_H
#define BSB_VECTOR_H

#include <math.h>

class Bsb_Vector
{
	public:
		float x;
	    float y;
	    float z;
		Bsb_Vector();
    	Bsb_Vector(float p_x,float p_y,float p_z);
	    void add(Bsb_Vector* b);
	    void sub(Bsb_Vector* b);
		void mul(Bsb_Vector* b);
		void div(Bsb_Vector* b);
		void div(float c);
		void mul(float c);
		float scal_prod(Bsb_Vector* b);
		float length();
		float length_sq();
		void normalize();
		Bsb_Vector* cross(Bsb_Vector* b);
		float dot(Bsb_Vector* b);
		float angle(Bsb_Vector* b);
};


static Bsb_Vector* add(Bsb_Vector* a,Bsb_Vector* b);
#endif
