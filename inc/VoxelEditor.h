#ifndef VOXELEDITOR_H
#define VOXELEDITOR_H

#include <vector>
#include <map>
#include "byteorder.h"
#include "cube.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "voxelart_engine/mesh.h"
#include "voxelart_engine/vector.h"

namespace cubiverse {


	//Ein Keyframe, der das gesamte Skelett beschreibt
	struct keyframe {
		float time;
		std::vector<float> angleX;
		std::vector<float> angleY;
	};

	class action {
		float time;
		std::vector<keyframe> keyframes;
	};

	struct joint {
		uint8_t id;
		uint8_t g1, g2; //Die Beiden Gruppen, die verbunden werden
		uint32_t x1,y1,z1,x2,y2,z2; //Welcher Block wird verbunden
	};

	class VoxelEditor
	{
		public:
			typedef boost::shared_ptr<cubiverse::VoxelEditor> pointer_t;
			typedef std::map<std::pair<uint32_t,std::pair<uint32_t,uint32_t > >, Cube::pointer_t> voxelList_t;
		private:
			std::vector<voxelList_t> voxels;
			std::vector<joint> joints;
			std::vector<action> actions;
			std::vector<vaEngine::Mesh*> meshs;

			int idColor;
		public:
			bool hasVoxel(int x, int y, int z, int group) { 
				return voxels[group].find(std::make_pair(x,std::make_pair(y,z))) != voxels[group].end(); 
			}
			Cube::pointer_t getVoxel(int x, int y, int z, int group) { 
				return voxels[group][make_pair(x,make_pair(y,z))]; 
			}
			void setVoxel(int x, int y, int z, int group, Cube::pointer_t newVoxel) { 
				voxels[group][make_pair(x,make_pair(y,z))] = newVoxel; 
			}
			void delVoxel(int x, int y, int z, int group) {
				voxels[group].erase(make_pair(x,make_pair(y,z)));
			} 
			void saveToFile(string file);
			void loadFromFile(string file);
		
			void refreshVisibility();
			void render(float playerX, float playerY, float playerZ);
			void key_pressed(unsigned char key);

			vaEngine::Vector checkCollision(float x, float y, float z); 

			void createMesh(int group);
			void updateMeshInfo(int group);
			void updateMesh(int group);
	};
}

#endif
