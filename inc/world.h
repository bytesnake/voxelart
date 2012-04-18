/*
 * Hier kommt mal eine Lizens (GPL/BSD oder so)
 */


#ifndef WORLD_H
#define WORLD_H

#include "worldGenerator.h"
#include "byteorder.h"
#include "voxelart_engine/mesh.h"
#include "voxelart_engine/water.h"
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

		uint32_t m_x, m_z;
		uint8_t m_blockType[16*128*16];
		int m_blockLightning[16*128*16];
		Cube::pointer_t m_cubes[16*128*16];
		vaEngine::Mesh* mesh;
		vaEngine::Water* water;

		uint8_t getBlockType(int x, int y, int z) {  return m_blockType[BLOCK_INDEX(x,y,z)]; }
		void setBlockType(int x, int y, int z, uint8_t blockType) { m_blockType[BLOCK_INDEX(x,y,z)] = blockType;}
		uint8_t getLightning(int x, int y, int z) { return m_blockLightning[BLOCK_INDEX(x,y,z)]; }
		void setLightning(int x, int y, int z, uint8_t lightning) {  m_blockLightning[BLOCK_INDEX(x,y,z)] = lightning;  }

		Cube::pointer_t getCube(int x, int y, int z) { return m_cubes[BLOCK_INDEX(x,y,z)]; }
		void refreshVisibility(bool existChunk[4], cubiverse::World_Chunk::pointer_t arround[4]);

		World_Chunk() { 
			mesh = new vaEngine::Mesh();
			water = new vaEngine::Water(16, 50, "../Data/normal_water.jpg");
		}	
	
		~World_Chunk() {
			mesh->deleteMesh();		
		}		
	};

	class World {
		public:
			typedef boost::shared_ptr<cubiverse::World> pointer_t;
			typedef std::map<std::pair<uint32_t,uint32_t>, cubiverse::World_Chunk::pointer_t> chunkList_t;

			World(float freq, int height, int octaves, int seed);

			//Generieren Eines Chunks
			void generateThread();
			void addChunksToList(int p_x, int p_z);
			void clearChunksList();
			bool generateChunk(int p_x, int p_z) {	pair<int,bool> firstCoor(p_z, false); pair<int,pair<int,bool> > coord(p_x,firstCoor); return std::find(generateChunks.begin(), generateChunks.end(), coord)!=generateChunks.end(); }

			//Setzten/Geben/Überprüfen eines Chunks
			bool hasChunk(int x, int z) { return m_chunks.find(std::make_pair(x,z)) != m_chunks.end(); }
			cubiverse::World_Chunk::pointer_t getChunk(int x, int z) { return m_chunks[make_pair(x,z)]; }
			void setChunk(int x, int z, cubiverse::World_Chunk::pointer_t chunk) { m_chunks[make_pair(x,z)] = chunk; }
			void delChunk(int x, int z);

			//Rendern eines Chunks
			void renderWaterTextures(int p_x, int p_z);
			void renderChunk(int p_x, int p_z);
			void renderChunkWater(int p_x, int p_z);
			void updateChunk(int p_x, int p_z);
			void refreshVisibility(int p_x, int p_z);
			void render(int playerX, int playerZ);
			void createMesh(int x, int z);	
			void updateMesh(int x, int z);
			void deleteMesh(int x, int z);
			void refreshMesh(int x, int z);
			void refreshMeshSide(int p_x, int p_z, int side);
			void render();

		private:
	
			vector< pair <int,pair <int,bool > > > generateChunks; //Chunks
			chunkList_t m_chunks; //Zu generierende Chunks

			//Für Threads
			boost::thread_group groupRender;
			boost::mutex mutexRender; //Mutex ob Rendern oder verändern
			boost::mutex mutexGenerateList; //Mutex Generieren oder Liste zum Generieren verändern
			boost::mutex mutexAddChunksList;
			boost::mutex mutexRefreshVisible;

			cubiverse::World_Chunk::pointer_t mapGenerator(int x, int z);
			void refreshVisibility(cubiverse::World_Chunk::pointer_t);

			worldGenerator* testGen;
		
	};
}
#endif
