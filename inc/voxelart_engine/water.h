#ifndef VAENGINE_WATER_H
#define VAENGINE_WATER_H

#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "texture.h"
#include "mesh.h"
#include "shader.h"

using namespace vaEngine;
namespace vaEngine {
	class Water {
		private:
			std::vector<Mesh*> arroundMesh;

			Texture* reflectionMap;
			Texture* refractionMap;
			Texture* normalMap;
			Texture* depthMap;

			Shader* shader;
			bool hasMesh;
			int size;
			int waterHeight;
			void RenderReflection();
			void RenderRefraction();
		public:
			Mesh* waterMesh;

			Water(int size, int waterHeight, char* normalMapName) {
				this->size = size;
				this->waterHeight = waterHeight;
				this->normalMap = new Texture(normalMapName);
			}
			void RenderWater();
			void RenderTextures() {
				RenderReflection();
				RenderRefraction();
			}
			void setMesh(Mesh* water, std::vector<Mesh*> arroundMesh) {
				this->waterMesh = water;
				this->arroundMesh = arroundMesh;
				hasMesh = true;
			}
			void setSize(int size) { this->size = size; }
			void setNormalMap(char* name) { this->normalMap = new Texture(name); }
			bool hasMeshs() { return hasMesh; }

			~Water() {
				waterMesh->deleteMesh();
			}
	};
}

#endif
