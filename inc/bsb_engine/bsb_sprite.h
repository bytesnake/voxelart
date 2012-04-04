#ifndef BSB_SPRITE_H
#define BSB_SPRITE_H
#include "bsb_object.h"
#include "bsb_vector.h"
#include "bsb_texture.h"
#include <iostream>
#include <GL/gl.h>
class Bsb_Sprite : public Bsb_Object{
	public:
		virtual void render();
		float width;
		float height;
		
		void setTexture(Bsb_Texture* p_texture);
		void setTexCoords(float x1,float y1,float x2,float y2);
		void setColor(float p_r,float p_g,float p_b,float p_a);
			
	private:
		float m_r;
		float m_g;
		float m_b;
		float m_a;
		
		Bsb_Texture* m_texture;
		
		//Texturkoordinaten
		float texX1;
		float texY1;
		float texX2;
		float texY2;
};
#endif
