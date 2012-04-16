#ifndef VOXELART_PARTICELSYSTEM_H
#define VOXELART_PARTICELSYSTEM_H

#include "particel.h"
#include <vector>

using namespace vaEngine;
namespace vaEngine {
	class ParticelSystem{
	public:
		// Konstruktor und Destruktor
		//Bsb_Particel(Bsb_ParticelSystem* p_pSystem);
		ParticelSystem();
		// virtual ~Bsb_Particel();
		// Methoden
		void update(float p_seconds);                    // Aufruf einmal pro Frame
		void render();                    // Aufruf einmal pro Frame
		void set();                      // … steht für Attribute des Objekts

		// Attribute
		Vector* m_vPosition;               // Position im Raum
		Vector* m_vVelocity;               // Geschwindigkeitsvektor
		float m_clrColor[4];              // RGB-Farbe, m_clrColor[3]
		 std::vector<Particel*> particel;        
		float m_fSize;					 // Logischerweise die Groesse
		float m_fBirthday;                // Zeitpunkt der Konstruktion
		float m_fLifetime;                // Lebensdauer in Sekunden
		bool m_bLife;                     // wird im Konstrukror auf true gesetzt.
		// Soll das Objekt vom Emitter gelöscht
		// werden: m_bLife = false
	};
}
#endif
