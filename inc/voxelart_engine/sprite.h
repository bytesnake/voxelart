#ifndef VOXELART_SPRITE_H
#define VOXELART_SPRITE_H

#include <iostream>
#include <GL/gl.h>

#include "object.h"
#include "vector.h"
#include "texture.h"

using namespace vaEngine;
namespace vaEngine {
	class Sprite : public Object{
		public:
			virtual void render();
			float width;
			float height;
		
			void setTexture(Texture* p_texture);
			void setTexCoords(float x1,float y1,float x2,float y2);
			void setColor(float p_r,float p_g,float p_b,float p_a);
			
		private:
			float m_r;
			float m_g;
			float m_b;
			float m_a;
		
			Texture* m_texture;
		
			//Texturkoordinaten
			float texX1;
			float texY1;
			float texX2;
			float texY2;
	};
}

#endif
