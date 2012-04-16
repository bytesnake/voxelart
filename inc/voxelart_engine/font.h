#ifndef VOXELART_FONT_H
#define VOXELART_FONT_H

#include <stdio.h>
#include <iostream>
#include "texture.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace vaEngine;
namespace vaEngine {
	class Font {
		int font_height;
		int char_widths[256];
		Texture* fontmap;
		int base;

		public:

			Font(const char* bitmap,const char* infofile);

			void draw_string(int p_x,int p_y,const char* p_string);
	
	};
}
#endif
