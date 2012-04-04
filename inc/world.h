/*
 * Hier kommt mal eine Lizens (GPL/BSD oder so)
 */


#ifndef WORLD_H
#define WORLD_H

#include "worldGenerator.h"
#include "byteorder.h"
#include "bsb_engine/bsb_mesh.h"
#include "cube.h"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp> 

#define BLOCK_INDEX(x,y,z) (x+y*16+z*16*128)

using namespace std;

// --- world.h ---
// Verwaltung der Welten und Chunks
//
// Änderungen:
// - 23.02.12: Chunks erweitert, so dass sie ihre eigenen Meshs speichern (bit)
//             Vertex-Struktur hinzugefügt (für VBOs)
 

namespace cubiverse {


	struct World_Chunk
	{
		typedef boost::shared_ptr<cubiverse::World_Chunk> pointer_t;

		bool m_render;
		uint32_t m_x, m_z;
		uint8_t m_blockType[16*128*16];
		uint8_t m_blockLightning[16*128*16];
		Cube::pointer_t m_cubes[16*128*16];
		Bsb_Mesh* mesh;
		Bsb_Mesh* mesh_water;

		boost::mutex mutex;

		uint8_t getBlockType(int x, int y, int z) {  return m_blockType[BLOCK_INDEX(x,y,z)]; }
		void setBlockType(int x, int y, int z, uint8_t blockType) { m_blockType[BLOCK_INDEX(x,y,z)] = blockType;}
		uint8_t getLightning(int x, int y, int z) { return m_blockLightning[BLOCK_INDEX(x,y,z)]; }
		void setLightning(int x, int y, int z, uint8_t lightning) {  m_blockLightning[BLOCK_INDEX(x,y,z)] = lightning;  }
		bool isRender() {  return m_render;}
		void setRender(bool render) { m_render = render;}

		Cube::pointer_t getCube(int x, int y, int z) { return m_cubes[BLOCK_INDEX(x,y,z)]; }
		void refreshVisibility(bool existChunk[4], cubiverse::World_Chunk::pointer_t arround[4]);

		void createMesh();	
		void updateMesh();
		void deleteMesh();
		void refreshMesh();
		void render();
		
		
		
	};

	class World {
		public:
			typedef boost::shared_ptr<cubiverse::World> pointer_t;
			typedef std::map<std::pair<uint32_t,uint32_t>, cubiverse::World_Chunk::pointer_t> chunkList_t;
    			//typedef std::vector<cubiverse::World_Generator::pointer_t> generatorList_t;

			World(float freq, int height, int octaves, int seed);

			void generateThread();
			void addChunksToList(int p_x, int p_z);
			void clearChunksList();

			bool hasChunk(int x, int z) { return m_chunks.find(std::make_pair(x,z)) != m_chunks.end(); }
			cubiverse::World_Chunk::pointer_t getChunk(int x, int z) { return m_chunks[make_pair(x,z)]; }
			void setChunk(int x, int z, cubiverse::World_Chunk::pointer_t chunk) { m_chunks[make_pair(x,z)] = chunk; }
			void delChunk(int x, int z);
			bool hasBlock(int x, int y, int z) { return hasChunk(x,z) && getChunk(x,z)->getCube(x-(x%16),y,z-(z%16)) != 0; }
			Cube::pointer_t getCube(int x, int y, int z) { if(hasBlock(x,y,z)) return getChunk(x,z)->getCube(x-(x%16),y,z-(z%16)); }
			bool generateChunk(int p_x, int p_z) {	pair<int,bool> firstCoor(p_z, false); pair<int,pair<int,bool> > coord(p_x,firstCoor); return std::find(generateChunks.begin(), generateChunks.end(), coord)!=generateChunks.end(); }

			void renderChunk(int p_x, int p_z);
			void renderChunkWater(int p_x, int p_z);
			void updateChunk(int p_x, int p_z);
			void refreshVisibility(int p_x, int p_z);
			void render(int playerX, int playerZ);

		private:
	
			vector< pair <int,pair <int,bool > > > generateChunks;
			chunkList_t m_chunks;
			int m_seed;
			cubiverse::World_Chunk::pointer_t mapGenerator(int x, int z);
			void refreshVisibility(cubiverse::World_Chunk::pointer_t);
			worldGenerator* testGen;
		
	};
}
#endif
