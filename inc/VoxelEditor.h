#ifndef VOXELEDITOR_H
#define VOXELEDITOR_H

namespace cubiverse {
	
	//Ein Keyframe, der das gesamte Skelett beschreibt
	struct keyframe {
		float time;
		std::vector<float> angleX;
		std::vector<float> angleY;
	}

	struct action {
		std::vector<keyframe> keyframes;
	}

	struct joint {
		uint8_t id;
		uint8_t g1, g2; //Die Beiden Gruppen, die verbunden werden
		uint32_t x1,y1,z1,x2,y2,z2; //Welcher Block wird verbunden
	}

	class VoxelEditor
	{
		public:
			typedef boost::shared_ptr<cubiverse::VoxelEditor> pointer_t;
			typedef std::map<std::pair<uint32_t,std::pair<uint32_t,uint32_t > >, uint8_t> voxelList_t;
		private:
			std::vector<voxelList_t> voxels;
			std::vector<joint> joints;
			std::vector<action> actions;
			std::vector<Bsb_Mesh*> meshs;
		public:
			bool hasVoxel(int x, int y, int z, int group) { 
				return voxels[group].find(std::make_pair(x,std::make_pair(y,z))) != voxels[group].end(); 
			}
			uint8_t getBlock(int x, int y, int z, int group) { 
				return voxels[group][make_pair(x,make_pair(y,z))]; 
			}
			void setChunk(int x, int y, int z, int group, uint8_t id) { 
				voxels[group][make_pair(x,make_pair(y,z))] = id; 
			}
			void saveToFile(string file);
			void loadFromFile(string file);
		
			void render();
	}
}
