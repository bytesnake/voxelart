#ifndef BSB_PARTICEL_H
#define BSB_PARTICEL_H

#include "bsb_sprite.h"

class Bsb_Particel{
public:
	// Konstruktor und Destruktor
	//Bsb_Particel(Bsb_ParticelSystem* p_pSystem);
	Bsb_Particel(Bsb_Vector* p_vPosition,Bsb_Vector* p_vVelocity,float p_fBirthday,float p_fLifetime);
	// virtual ~Bsb_Particel();
	// Methoden
	void update(float p_seconds);                    // Aufruf einmal pro Frame
	void render();                    // Aufruf einmal pro Frame
	void set(Bsb_Vector* p_vPosition,Bsb_Vector* p_vVelocity,float p_fBirthday,float p_fLifetime);                      // … steht für Attribute des Objekts

	// Attribute
	Bsb_Vector* m_vPosition;               // Position im Raum
	Bsb_Vector* m_vVelocity;               // Geschwindigkeitsvektor
	float m_clrColor[4];              // RGB-Farbe, m_clrColor[3]
	float m_fSize;					 // Logischerweise die Groesse
	float m_fBirthday;                // Zeitpunkt der Konstruktion
	float m_fLifetime;                // Lebensdauer in Sekunden
	bool m_bLife;                     // wird im Konstrukror auf true gesetzt.
	// Soll das Objekt vom Emitter gelöscht
	// werden: m_bLife = false
private:
	Bsb_Sprite* m_Sprite;
	//Bsb_ParticelSystem* m_pSystem;         // Zeiger auf das System
};
#endif
