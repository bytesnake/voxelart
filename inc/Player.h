#ifndef Player_H
#define Player_H

#include <iostream>
#include "bsb_engine/bsb_game.h"

class Player
{
	private:
		Bsb_Vector* m_speed;
		Bsb_Vector* m_acc;
		float m_atten;
		float m_yaw, m_pitch;
		Bsb_FPCamera* m_camera;
	public:
		Player();
		Bsb_Vector* getSpeed() { return m_speed; }
		Bsb_Vector* getAcc() { return m_acc; }
		void addSpeed(Bsb_Vector* speed) { m_speed->add(speed); }
		void addAcc(Bsb_Vector* acc) { m_acc->add(acc); }
		void setAtt(float atten) { m_atten = atten; }

		void move(float time);
		

		
		
	
			
};
#endif
