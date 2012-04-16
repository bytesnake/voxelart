#include "../../inc/voxelart_engine/particel.h"

vaEngine::Particel::Particel(Vector p_vPosition,Vector p_vVelocity,float p_fBirthday,float p_fLifetime){
	m_vPosition = p_vPosition;
	m_vVelocity = p_vVelocity;
	m_fBirthday = p_fBirthday;
	m_fLifetime = p_fLifetime;
}

void vaEngine::Particel::update(float p_seconds){// Aufruf einmal pro Frame
	if(p_seconds - m_fBirthday > m_fLifetime){
		m_bLife= false ;              	// Partikel wird beim nächsten
		// Schleifendruchlauf gelöscht
		return;                       	// keine weiteren Updates mehr nötig
	}

	// neue Position anhand der Geschwindigkeit und der Zeit seit
	// dem letzen Update berechnen
	/*m_vPosition->x += (m_vVelocity->x*p_seconds);
	m_vPosition->y += (m_vVelocity->y*p_seconds);
	m_vPosition->z += (m_vVelocity->z*p_seconds);*/
	m_vPosition += m_vVelocity*p_seconds;
}
void vaEngine::Particel::render(){                    // Aufruf einmal pro Frame
	m_Sprite->render();
}
void vaEngine::Particel::set(Vector p_vPosition,Vector p_vVelocity,float p_fBirthday,float p_fLifetime){                      // … steht für Attribute des Objekts
	m_vPosition = p_vPosition;
	m_vVelocity = p_vVelocity;
	m_fBirthday = p_fBirthday;
	m_fLifetime = p_fLifetime;
}

