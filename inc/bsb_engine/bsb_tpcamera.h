#ifndef BSB_TPCAMERA_H
#define BSB_TPCAMERA_H
#include "bsb_game.h"
//#include "../main.h"

class Bsb_TPCamera: public Bsb_Camera{
	private:

    	//the rotation around the Y axis of the camera
    	float       m_yaw;  		//the rotation around the X axis of the camera
    	float       m_pitch;
		float       m_slant;
		//bool       wackel;
	public:
	    	//3d vector to store the camera's position in
	 //   Bsb_Vector* position;
		Bsb_TPCamera(float x, float y, float z);
		void yaw(float amount);
		void pitch(float amount);
		void walkForward(float distance);
		void walkBackwards(float distance);
		void strafeLeft(float distance);
		void strafeRight(float distance);
		void jump();
		void lookThrough();
		//using Bsb_Camera::lookThrough;
//		virtual void lookThrough() override;
};
#endif
