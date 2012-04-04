#ifndef BSB_CAMERA_H
#define BSB_CAMERA_H

#include "bsb_vector.h"


class Bsb_Camera{
	public:
		Bsb_Vector* position;
		Bsb_Vector* lookAt;
		Bsb_Vector* upVector;
		Bsb_Camera();
		virtual void lookThrough();
};


#endif
