#ifndef BSB_PARTICELSYSTEM_H
#define BSB_PARTICELSYSTEM_H

#include "bsb_particel.h"
#include <vector>
class Bsb_ParticelSystem{
public:
	// Konstruktor und Destruktor
	//Bsb_Particel(Bsb_ParticelSystem* p_pSystem);
	Bsb_ParticelSystem();
	// virtual ~Bsb_Particel();
	// Methoden
	void update(float p_seconds);                    // Aufruf einmal pro Frame
	void render();                    // Aufruf einmal pro Frame
	void set();                      // … steht für Attribute des Objekts

	// Attribute
	Bsb_Vector* m_vPosition;               // Position im Raum
	Bsb_Vector* m_vVelocity;               // Geschwindigkeitsvektor
	float m_clrColor[4];              // RGB-Farbe, m_clrColor[3]
	 std::vector<Bsb_Particel*> particel;        
	float m_fSize;					 // Logischerweise die Groesse
	float m_fBirthday;                // Zeitpunkt der Konstruktion
	float m_fLifetime;                // Lebensdauer in Sekunden
	bool m_bLife;                     // wird im Konstrukror auf true gesetzt.
	// Soll das Objekt vom Emitter gelöscht
	// werden: m_bLife = false
};
#endif
