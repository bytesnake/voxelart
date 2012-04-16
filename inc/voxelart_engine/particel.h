#ifndef VOXELART_PARTICEL_H
#define VOXELART_PARTICEL_H

#include "sprite.h"

using namespace vaEngine;
namespace vaEngine {
	class Particel{
		public:
			// Konstruktor und Destruktor
			//Bsb_Particel(Bsb_ParticelSystem* p_pSystem);
			Particel(Vector p_vPosition,Vector p_vVelocity,float p_fBirthday,float p_fLifetime);
			// virtual ~Bsb_Particel();
			// Methoden
			void update(float p_seconds);                    // Aufruf einmal pro Frame
			void render();                    // Aufruf einmal pro Frame
			void set(Vector p_vPosition,Vector p_vVelocity,float p_fBirthday,float p_fLifetime);                      // … steht für Attribute des Objekts

			// Attribute
			Vector m_vPosition;               // Position im Raum
			Vector m_vVelocity;               // Geschwindigkeitsvektor
			float m_clrColor[4];              // RGB-Farbe, m_clrColor[3]
			float m_fSize;					 // Logischerweise die Groesse
			float m_fBirthday;                // Zeitpunkt der Konstruktion
			float m_fLifetime;                // Lebensdauer in Sekunden
			bool m_bLife;                     // wird im Konstrukror auf true gesetzt.
			// Soll das Objekt vom Emitter gelöscht
			// werden: m_bLife = false
		private:
			Sprite* m_Sprite;
			//Bsb_ParticelSystem* m_pSystem;         // Zeiger auf das System
		};
}
#endif
