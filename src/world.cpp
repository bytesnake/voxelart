#include <iostream>
#include <fstream>
#include "../inc/world.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include "math.h"
#include <boost/thread.hpp> 

using namespace std;
//boost::thread_group genThreadGroup;

// --- world.cpp ---
// Verwaltung der Welten und Chunks
//
// Änderungen:
// - 22.02.12: Erster Versuch einer Optimierung (20/21fps) (byt)
// - 25.02.12: Jetzt werden alle Seiten der Blöcke, falls nötig angezeigt 
// - 28.02.12: Wir arbeiten am Löschen und Neuerstellen des Meshs
// - 19.03.12: Einige Änderungen: Threads/keine maps mehr/Trennung von Access und den Daten/Kommentare (byt)
// - 21.03.12: Wieder auf maps umgestiegen, mit smart Pointer funktionieren die auch :)

boost::mutex mutexThread; //Mutex ob zeichnen oder verändern

cubiverse::World::World(float freq, int height, int octaves, int seed) {
	testGen = new worldGenerator(freq, height, octaves, seed);
}

/*
 * Diese Funktion wird in einem eigenen Thread gestartet und
 * verarbeitet die zu rendernden Chunks, die von addChunkToList eingetragen wurden
 * Dabei bestehen die Vektoren aus drei einträgen: X;Y und isGenerated, damit während des
 * generieren kein Thread auf die Idee kommt den auch zu generieren
 */
void cubiverse::World::generateThread() {
	while(true) {
		if(generateChunks.size() > 0) {

			//Ermittel die Koordinaten aus dem Eintrag
			mutexThread.lock();
			pair<int, pair<int, bool> >  it = generateChunks.back();
			int x = it.first;
			int z = it.second.first;

			//Falls er nicht gerade generiert wird -> anfangen
			if(!it.second.second) {
				//Eintragen, er wird jetzt generiert
				pair<int,bool> firstCoor(z, true);
				pair<int,pair<int,bool> > coord(x,firstCoor); 
				it = coord;
				mutexThread.unlock();

				//Generieren, dies steht nicht im Mutex, da es am Ressourcenlastigsten ist
				cubiverse::World_Chunk::pointer_t newChunk = mapGenerator(x,z);

				//Sichtbarkeit der Blöcke setzten, Chunk setzten und Eintrag löschen
				mutexThread.lock();
				newChunk->m_x = x;  newChunk->m_z = z;	
				newChunk->m_render=false;
				setChunk(x, z, newChunk);

				refreshVisibility(x,z);
				if(hasChunk(x, (z+16)))
					refreshVisibility(x, (z+16));
				if(hasChunk(x, (z-16)))
					refreshVisibility(x, (z-16));
				if(hasChunk((x+16), z))
					refreshVisibility((x+16), z);
				if(hasChunk((x-16), z))
					refreshVisibility((x-16), z);

				generateChunks.pop_back();

				cout << "Es sollen " << generateChunks.size() << " gerendert werden" << endl;
			}
			mutexThread.unlock();
		}
	}
}

/*
 * Erneuert die Vector Liste mit den zu generiernden Chunks
 * Dabei werden alle einträge gelöscht und neu generiert
 */
void cubiverse::World::addChunksToList(int p_x, int p_z) {
	if(generateChunks.size() > 0) {
		clearChunksList();
	}
	//Chunks je nach Position rendern
	//Die Äußeren Chunks zuerst generiert, damit die innersten zuletzt auf die Map fürs bearbeiten kommen
	//da die Threads immer von hinten arbeiten
	mutexThread.lock();	
	for(int length=112; length >= 0; length-=16) 
	for(int x=-length; x <= length; x=x+16) 
	for(int z=-length; z <= length; z=z+16) {
		if( (x==length) || (x==-length) || (z==length) || (z==-length)) {
			pair<int,bool> firstCoor(z + p_z, false);
			pair<int,pair<int,bool> > coord(x + p_x,firstCoor); 
			if(!hasChunk(x + p_x, z + p_z) && std::find(generateChunks.begin(), generateChunks.end(), coord)==generateChunks.end()) {	
				cout << "Add Chunk to Render X:" << x+p_x << " Y:" << z + p_z << endl;
				generateChunks.push_back(coord);
			}	
		}
	}
	mutexThread.unlock();	
}

/* Löscht alle Einträge der zu generierdenen Chunks */
void cubiverse::World::clearChunksList() {
	mutexThread.lock();
	generateChunks.clear();
	mutexThread.unlock();
}

/*
 * Erneuert die Sichtbarkeit von einem Chunk
 * 1. gehe alle umliegende Chunks durch und erstell eine Liste
 * 2. Gib dies der Funktion refreshVisibility von einem Chunk und dieser Berechnet die Sichtbaren Würfelseiten
 */
void cubiverse::World::refreshVisibility(cubiverse::World_Chunk::pointer_t chunk) {
	int p_x = chunk->m_x; /**/ int p_z = chunk->m_z;
	cubiverse::World_Chunk::pointer_t arround[4];

	bool existChunks[4] = {hasChunk(p_x, (p_z+16)), hasChunk(p_x, (p_z-16)), hasChunk((p_x+16), p_z), hasChunk((p_x-16), p_z) };
	//Erstelle die Liste mit den umliegenden Chunks
	if(existChunks[0]) arround[0] = getChunk(p_x, (p_z+16)); 
	if(existChunks[1]) arround[1] = getChunk(p_x, (p_z-16)); 
	if(existChunks[2]) arround[2] = getChunk((p_x+16), p_z);
	if(existChunks[3]) arround[3] = getChunk((p_x-16), p_z);

	chunk->refreshVisibility(existChunks, arround);
}
	
void cubiverse::World::refreshVisibility(int p_x, int p_z) {
	refreshVisibility(getChunk(p_x, p_z));
}

//TODO: Mach eine erweiterbare Liste mit mehreren Worldgeneratoren und lagere das hier aus
/*
 * Generiert ein neuen Chunk und gib diesen zurück
 * Dazu wird ein PerlinNoise Generator benutzt
 */
cubiverse::World_Chunk::pointer_t cubiverse::World::mapGenerator(int p_x, int p_z) {
		//Heightmap
		int heightMap[16][16][128];
		for(int x=0; x < 16; x++)
		for(int z=0; z < 16; z++)
		for(int y=0; y < 128; y++)
			heightMap[x][z][y] = testGen->getNoiseHeight(p_x+x,p_z+z, y)+64;

		//Colormap
		int colorMap[16][16];
		for(int x=0; x < 16; x++)
		for(int z=0; z < 16; z++)
			colorMap[x][z] = testGen->getNoiseColor(p_x+x, p_z+z);

		cubiverse::World_Chunk::pointer_t newChunk = boost::make_shared<cubiverse::World_Chunk>();		
		newChunk->m_render=false;			

		for(int x=0; x < 16; x++) {
			for(int z=0; z < 16; z++) {
				int height=500; 
				for(int y=0; y<=127; y++) {	//andersrum
					if(y < heightMap[x][z][y]) {

						newChunk->m_blockType[BLOCK_INDEX(x,y,z)] = 1;
						Cube::pointer_t newCube = boost::make_shared<Cube>();
						//newCube->setColor(0.1f,0.9f,0.1f,1.0f);
						//Farbe:
						// wenn block drüber besetzt: braun
						// sonst: grün
						if(!((y+1) < heightMap[x][z][y+1]) && y >= 50){
							newCube->setColor(0.2+(colorMap[x][z] / 256.0f),0.5-(colorMap[x][z] / 128.0f),0.2f-(colorMap[x][z] / 256.0f),1.0f);
						}else{
							newCube->setColor(y/192.0f,0.3f,0.2f,1.0f);
						}
						//newCube->setColor(0.2f,y/128.0f,0.2f,1.0f);
						//newCube->setColor(0.2f, pow((((float)y+1.0f)/128.0f), 2), 0.2f, 0.1f);
						//newCube->setColor(p_x/100.0f+(double)x/16.0f,p_z/100.0f+(double)z/16.0f,(double)y/128.0f, 1.0f);
						newChunk->m_cubes[BLOCK_INDEX(x,y,z)] = newCube;	
					}
					//TODO: verschiedene Wasserhöhen
					else if(y <=50) {
						if(height==500) { height=y;}
						newChunk->m_blockType[BLOCK_INDEX(x,y,z)] = 2;
						Cube::pointer_t newCube = boost::make_shared<Cube>();
						//newCube->setColor(0.1f, 0.1,5*heightMap[x][z][y], 1.0f);//verschiedene Farben im Wasser (kann man das irgendwie über die echte tiefe machen?)
						newCube->setColor(0.0f, 0.0f, 1.0f, 1.0f);
						//Verschiedene Farbe je nach höhe
						//Je höher desto heller
						//(cout << 0.8f+((((double)height)/((double)y)-0.8)*5)-0.9 << endl;
						//newCube->setColor(0.1f, 0.1,0.0f+((((double)height)/((double)y)-0.6)*2), 0.9f);
						newChunk->m_cubes[BLOCK_INDEX(x,y,z)] = newCube;
					}	 			
					else{
						newChunk->m_blockType[BLOCK_INDEX(x,y,z)] = 0;
						}
					//TODO:Wie machen wir das mit den Lichtern? Softwareseitig vorgerendert oder nur von der GPU gerendert?	
					// Wie findest du denn das OpenGL-Licht?				
					newChunk->m_blockLightning[BLOCK_INDEX(x,y,z)] = 1;
					
									 			
				}
			}
		}

		return newChunk;
}	

/*
 * Löscht einen Chunk aus der Map
 * Findet ihn dazu und löscht den Chunk
*/	
void cubiverse::World::delChunk(int x, int z) {
	if(hasChunk(x,z)) {
		getChunk(x,z)->deleteMesh();
		mutexThread.lock(); 
		m_chunks.erase(make_pair(x,z)); 
		mutexThread.unlock();
	}
}

/*
 * Rendert alle Chunks
 */
void cubiverse::World::render(int playerX, int playerZ) { 
	//Rendert die Chunks und erstellt falls nötig eine Mesh
	for(int x=-128; x <= 128; x=x+16) {
		for(int z=-128; z <= 128; z=z+16) {
			int x_chunk = (x-playerX);
			int z_chunk = (z-playerZ);
			if(hasChunk(x_chunk,z_chunk) ) {
				if(getChunk(x_chunk,z_chunk)->isRender()) {
					// ---- Draw one Chunk ---
					glTranslatef(x_chunk, 0.0f, z_chunk);		
					renderChunk(x_chunk, z_chunk);
					glTranslatef(-x_chunk, 0.0f, -z_chunk);
				}
				else if(!generateChunk(x+playerX, z+playerZ)) {
					//Update the Meshs arround 
					if(hasChunk((x_chunk+16), z_chunk) && getChunk((x_chunk+16), z_chunk)->isRender()) 
						getChunk((x_chunk+16), z_chunk)->updateMesh();
					if(hasChunk((x_chunk-16), z_chunk) && getChunk((x_chunk-16), z_chunk)->isRender())
						getChunk((x_chunk-16), z_chunk)->updateMesh();
					if(hasChunk(x_chunk, (z_chunk+16)) && getChunk(x_chunk, (z_chunk+16))->isRender()) 
						getChunk(x_chunk, (z_chunk+16))->updateMesh();
					if( hasChunk(x_chunk, (z_chunk-16)) && getChunk(x_chunk, (z_chunk-16))->isRender()) 
						getChunk(x_chunk, (z_chunk-16))->updateMesh();

					getChunk(x_chunk,z_chunk)->createMesh();
				}
			}
		}
	}
	//glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	//Das gleiche fürs Wasser
	for(int x=-128; x <= 128; x=x+16) {
		for(int z=-128; z <= 128; z=z+16) {
			int x_chunk = (x-playerX);
			int z_chunk = (z-playerZ);
			if(hasChunk(x_chunk,z_chunk) ) {
				if(getChunk(x_chunk,z_chunk)->isRender()) {
					glTranslatef(x_chunk, 0.0f, z_chunk);	
					renderChunkWater(x_chunk, z_chunk);
					glTranslatef(-x_chunk, 0.0f, -z_chunk);
				}
			}
		}
	}
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
}
/*
 * Erneuert die Mesh, indem sie die Cubes
 * neu durchgeht und einfügt
*/
void cubiverse::World_Chunk::refreshMesh() {
	mutex.lock();
	vector<Vertex> vertices, vertices_water;
	vector<GLuint> indices, indices_water;
	//Zuerst alle Blöcke, falls sichtbar, zu einer Mesh verknüpfen
	for(int x=0; x < 16; x++){
		for(int z=0; z < 16; z++){	
			for(int y=0; y < 128; y++) {
				if(getBlockType(x,y,z)  == 1) {		
					getCube(x,y,z)->renderToMesh(x,y,z,&vertices,&indices);				
				}
				else if(getBlockType(x,y,z) == 2) {
					getCube(x,y,z)->renderToMesh(x,y,z,&vertices_water,&indices_water);	
				}
			}
		}
	}
	mesh->setVertices(vertices);
	mesh->setIndices(indices);
	mesh_water->setVertices(vertices_water);
	mesh_water->setIndices(indices_water);
	mutex.unlock();
}
/*
 * Erstellt eine Mesh
 * und gib diese der Grafikkarte
 */
void cubiverse::World_Chunk::createMesh(){
	mesh = new Bsb_Mesh();
	mesh_water = new Bsb_Mesh();

	refreshMesh();

	if(!m_render) {
		mutex.lock();
		mesh->createMesh();
		mesh_water->createMesh();
		m_render = true;
		mutex.unlock();
	}


}

/* 
 * Update einer Mesh
 * Dazu werden die äußeren Ränder eines Chunks durchlaufen
 * und geupdatet (warum nur diese?)
 */
void cubiverse::World_Chunk::updateMesh(){
	refreshMesh();

	if(m_render) {
		mutex.lock();
		mesh->updateMesh();
		mesh_water->updateMesh();
		mutex.unlock();
	}
}



/*
 * Löscht eine Mesh aus der Grafikkarte
 */
void cubiverse::World_Chunk::deleteMesh(){
	if(m_render) {
		mutex.lock();
		mesh->deleteMesh();
		mesh_water->deleteMesh();
		m_render = false;
		mutex.unlock();
	}
}

/*
 * Rendert einen Chunk
 */
void cubiverse::World::renderChunk(int p_x, int p_z) {
	if(hasChunk(p_x, p_z) && getChunk(p_x, p_z)->m_render) {
		getChunk(p_x, p_z)->mesh->render();
	}
}
//TODO: Was muss openGL gegeben werden, damit das wierklich transparent gezeichnet wird 	
void cubiverse::World::renderChunkWater(int p_x, int p_z) {
	if(hasChunk(p_x, p_z) && getChunk(p_x, p_z)->m_render) {
		//glDisable(GL_DEPTH_TEST);
		//glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
		//glDepthMask(GL_FALSE);
		getChunk(p_x, p_z)->mesh_water->render();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		//glDisable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);
	}
}

/*
 * Überprüft welche Blöcke sichtbar sind
 * Geht dazu jeden Block durch und guck ob es an einer Grenzschicht liegt
 * wie Block -> Luft oder Block -> Wasser
*/
void cubiverse::World_Chunk::refreshVisibility(bool existChunk[4], cubiverse::World_Chunk::pointer_t arroundChunks[4]) {
	mutex.lock();
	for(int x=0; x < 16; x++) {
		for(int y=0; y < 128; y++) {			
			for(int z=0; z < 16; z++) {
					if(m_blockType[BLOCK_INDEX(x,y,z)] != 0) {	
						if((z >= 15) ? ((existChunk[0]) ? arroundChunks[0]->m_blockType[BLOCK_INDEX(x,y,0)]==0 || (arroundChunks[0]->m_blockType[BLOCK_INDEX(x,y,0)]==2 && m_blockType[BLOCK_INDEX(x,y,15)]==1):0):
							m_blockType[BLOCK_INDEX(x,y,(z+1))]==0 || (m_blockType[BLOCK_INDEX(x,y,(z+1))]==2 && m_blockType[BLOCK_INDEX(x,y,z)]==1))
								m_cubes[BLOCK_INDEX(x,y,z)]->show(0);

						if((z <= 0) ? ((existChunk[1]) ? arroundChunks[1]->m_blockType[BLOCK_INDEX(x,y,15)]==0 || (arroundChunks[1]->m_blockType[BLOCK_INDEX(x,y,15)]==2 && m_blockType[BLOCK_INDEX(x,y,0)]==1):0):
							m_blockType[BLOCK_INDEX(x,y,(z-1))]==0 || (m_blockType[BLOCK_INDEX(x,y,(z-1))]==2 && m_blockType[BLOCK_INDEX(x,y,z)]==1)) 
								m_cubes[BLOCK_INDEX(x,y,z)]->show(1);

						if((x >= 15) ? ((existChunk[2]) ? arroundChunks[2]->m_blockType[BLOCK_INDEX(0,y,z)]==0 || (arroundChunks[2]->m_blockType[BLOCK_INDEX(0,y,z)]==2 && m_blockType[BLOCK_INDEX(15,y,z)] == 1):0): 
							m_blockType[BLOCK_INDEX((x+1),y,z)]==0  || (m_blockType[BLOCK_INDEX((x+1),y,z)]==2 && m_blockType[BLOCK_INDEX(x,y,z)]==1))
							m_cubes[BLOCK_INDEX(x,y,z)]->show(2);

						if((x <= 0) ? ((existChunk[3]) ? arroundChunks[3]->m_blockType[BLOCK_INDEX(15,y,z)]==0 || (arroundChunks[3]->m_blockType[BLOCK_INDEX(15,y,z)]==2 && m_blockType[BLOCK_INDEX(0,y,z)]==1):0): 
							m_blockType[BLOCK_INDEX((x-1),y,z)]==0 || (m_blockType[BLOCK_INDEX((x-1),y,z)]==2 && m_blockType[BLOCK_INDEX(x,y,z)]==1))
								m_cubes[BLOCK_INDEX(x,y,z)]->show(3);

						if((y >= 127) ? 0: m_blockType[BLOCK_INDEX(x,(y+1),z)] == 0 || (m_blockType[BLOCK_INDEX(x,(y+1),z)] == 2 && m_blockType[BLOCK_INDEX(x,y,z)] == 1))
							m_cubes[BLOCK_INDEX(x,y,z)]->show(4);
						if((y <= 0) ? 0: m_blockType[BLOCK_INDEX(x,(y-1),z)] == 0 || (m_blockType[BLOCK_INDEX(x,(y-1),z)] == 2 && m_blockType[BLOCK_INDEX(x,y,z)] == 1))
							m_cubes[BLOCK_INDEX(x,y,z)]->show(5);
							
					}
					/*if(m_blockType[BLOCK_INDEX(x,y,z)] != 0) {	
						if((z >= 15) ? ((existChunk[0]) ? arroundChunks[0]->m_blockType[BLOCK_INDEX(x,y,0)]==0:0): m_blockType[BLOCK_INDEX(x,y,(z+1))]==0) 
							m_cubes[BLOCK_INDEX(x,y,z)]->show(0);
						if((z <= 0) ? ((existChunk[1]) ? arroundChunks[1]->m_blockType[BLOCK_INDEX(x,y,15)]==0:0): m_blockType[BLOCK_INDEX(x,y,(z-1))]==0) 
							m_cubes[BLOCK_INDEX(x,y,z)]->show(1);
						if((x >= 15) ? ((existChunk[2]) ? arroundChunks[2]->m_blockType[BLOCK_INDEX(0,y,z)]==0:0): m_blockType[BLOCK_INDEX((x+1),y,z)]==0)
							m_cubes[BLOCK_INDEX(x,y,z)]->show(2);
						if((x <= 0) ? ((existChunk[3]) ? arroundChunks[3]->m_blockType[BLOCK_INDEX(15,y,z)]==0:0): m_blockType[BLOCK_INDEX((x-1),y,z)]==0)
							m_cubes[BLOCK_INDEX(x,y,z)]->show(3);
						if((y >= 127) ? 0: m_blockType[BLOCK_INDEX(x,(y+1),z)] == 0)
							m_cubes[BLOCK_INDEX(x,y,z)]->show(4);
						if((y <= 0) ? 0: m_blockType[BLOCK_INDEX(x,(y-1),z)] == 0)
							m_cubes[BLOCK_INDEX(x,y,z)]->show(5);
							
					}*/
					
			}
		}
	mutex.unlock();
	}
}
