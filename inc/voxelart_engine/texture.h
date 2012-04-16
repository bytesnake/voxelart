#ifndef VOXELART_TEXTURE_H
#define VOXELART_TEXTURE_H
#include "../lodepng.h"

namespace vaEngine {
	class Texture{
		public:
			int id;
			Texture(const char* filename);
			Texture(const char* filename,bool inverted);
			void bind();
			void unload();
	};
}

#endif
