#ifndef VOXELEDITOR_H
#define VOXELEDITOR_H

#include <vector>
#include <map>
#include "byteorder.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "bsb_engine/bsb_mesh.h"

namespace cubiverse {
	
	//One Voxel
	GLfloat vertices_front[]  = { 0.5, 0.5, 0.5,  -0.5, 0.5, 0.5,  -0.5,-0.5, 0.5,   0.5,-0.5, 0.5};	// v0-v0.5-v2-v3	front
	GLfloat vertices_right[]  = { 0.5, 0.5, 0.5,   0.5,-0.5, 0.5,   0.5,-0.5,-0.5,   0.5, 0.5,-0.5};	// v0-v3-v4-v5	right
	GLfloat vertices_top[]    = { 0.5, 0.5, 0.5,   0.5, 0.5,-0.5,  -0.5, 0.5,-0.5,  -0.5, 0.5, 0.5};	// v0-v5-v6-v0.5	top
	GLfloat vertices_left[]   = {-0.5, 0.5, 0.5,  -0.5, 0.5,-0.5,  -0.5,-0.5,-0.5,  -0.5,-0.5, 0.5};	// v0.5-v6-v7-v2	left
	GLfloat vertices_bottom[] = {-0.5,-0.5,-0.5,   0.5,-0.5,-0.5,   0.5,-0.5, 0.5,  -0.5,-0.5, 0.5};	// v7-v4-v3-v2	bottom
	GLfloat vertices_back[]   = { 0.5,-0.5,-0.5,  -0.5,-0.5,-0.5,  -0.5, 0.5,-0.5,   0.5, 0.5,-0.5};	// v4-v7-v6-v5	back

	struct voxel {
		uint8_t id;
		bool visible[6];
	};

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
			typedef std::map<std::pair<uint32_t,std::pair<uint32_t,uint32_t > >, voxel> voxelList_t;
		private:
			std::vector<voxelList_t> voxels;
			std::vector<joint> joints;
			std::vector<action> actions;
			std::vector<Bsb_Mesh*> meshs;
		public:
			bool hasVoxel(int x, int y, int z, int group) { 
				return voxels[group].find(std::make_pair(x,std::make_pair(y,z))) != voxels[group].end(); 
			}
			voxel getVoxel(int x, int y, int z, int group) { 
				return voxels[group][make_pair(x,make_pair(y,z))]; 
			}
			void setVoxel(int x, int y, int z, int group, voxel newVoxel) { 
				voxels[group][make_pair(x,make_pair(y,z))] = newVoxel; 
			}
			void saveToFile(string file);
			void loadFromFile(string file);
		
			void refreshVisibility();
			void render();

			void createMesh(int group);
			void updateMeshInfo(int group);
			void updateMesh(int group);
	};
}

#endif
