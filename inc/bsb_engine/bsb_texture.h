#ifndef BSB_TEXTURE_H
#define BSB_TEXTURE_H
#include "../lodepng.h"

class Bsb_Texture{
	public:
		int id;
		Bsb_Texture(const char* filename);
		Bsb_Texture(const char* filename,bool inverted);
		void bind();
		void unload();
};
#endif
