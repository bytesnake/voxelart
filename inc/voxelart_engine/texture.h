#ifndef VOXELART_TEXTURE_H
#define VOXELART_TEXTURE_H
#include "../lodepng.h"
#include <GL/gl.h>

namespace vaEngine {
	class Texture{
		public:
			GLuint id;
			Texture();
			Texture(const char* filename);
			Texture(const char* filename,bool inverted);
			void bind();
			void unload();
	};
}

#endif
