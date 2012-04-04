#include "../inc/Player.h"

Player::Player() {
	m_camera = new Bsb_FPCamera(0,40,0);
	m_speed = m_acc = new Bsb_Vector(0, 0, 0);
}

void Player::move(float time) {
	m_camera->walkForward(m_speed->z*time);
	m_camera->strafeLeft(m_speed->z*time);
	m_camera->top(m_speed->y*time);	

	m_speed->add(new Bsb_Vector(m_acc->x*time, m_acc->y*time, m_acc->z*time));
}
