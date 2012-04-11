#ifndef BSB_FPCAMERA_H
#define BSB_FPCAMERA_H
#include "bsb_game.h"

class Bsb_FPCamera: public Bsb_Camera{
	private:

    	//the rotation around the Y axis of the camera
		float       m_yaw;  		//the rotation around the X axis of the camera
		float       m_pitch;
		float       m_slant;
		Bsb_Vector* m_speed;

	public:

		Bsb_FPCamera(float x, float y, float z);
		void yaw(float amount);
		void pitch(float amount);
		void stopFall();
		void walkForward(float distance);
		void walkBackwards(float distance);
		void strafeLeft(float distance);
		void strafeRight(float distance);
		void top(float distance);
		void jump();
		void down();
		void move(float time);
		void lookThrough();
		void gravitation(float force, float time);
};
#endif
