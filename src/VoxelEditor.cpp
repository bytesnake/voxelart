#include "../inc/VoxelEditor.h"
#include "../inc/color.h"

void cubiverse::VoxelEditor::refreshVisibility() {
	for(int group = 0; group < voxels.size(); group++)  {
	std::map<std::pair<uint32_t,std::pair<uint32_t,uint32_t > >, voxel>::iterator it;
	for ( it=voxels[group].begin(); it!=voxels[group].end(); it++) {
		int x = (*it).first.first;
		int y = (*it).first.second.first;
		int z = (*it).first.second.second;
		voxel* Voxel = &(*it).second;

		if(!hasVoxel(x,y,z+1, group)) Voxel->visible[0] = true;
		if(!hasVoxel(x,y,z-1, group)) Voxel->visible[1] = true;
		if(!hasVoxel(x+1,y,z, group)) Voxel->visible[2] = true;
		if(!hasVoxel(x-1,y,z, group)) Voxel->visible[3] = true;
		if(!hasVoxel(x,y+1,z, group)) Voxel->visible[4] = true;
		if(!hasVoxel(x,y-1,z, group)) Voxel->visible[5] = true;
	}
	}
}
		
void cubiverse::VoxelEditor::render() {
	for(int mesh = 0; mesh < meshs.size(); mesh++)
		meshs[mesh]->render();
}

void cubiverse::VoxelEditor::createMesh(int group) {
	updateMeshInfo(group);
	meshs[group]->createMesh();
}
void cubiverse::VoxelEditor::updateMesh(int group) {
	updateMeshInfo(group);
	meshs[group]->updateMesh();
}
void cubiverse::VoxelEditor::updateMeshInfo(int group) {
	std::map<std::pair<uint32_t,std::pair<uint32_t,uint32_t > >, voxel>::iterator it;
	for (it=voxels[group].begin(); it!=voxels[group].end(); it++) {
		int x = (*it).first.first;
		int y = (*it).first.second.first;
		int z = (*it).first.second.second;
		voxel* Voxel = &(*it).second;
		vector<Vertex> vertices;
		vector<GLuint> indices;	
		for(int side=0; side < 6; side++) {
			if(Voxel->visible[side]) {
				Vertex tmpvert;
				float normals[3];
				GLfloat* vertice;
				switch(side){
					case 0:
						normals[0]=0;
						normals[1]=0;
						normals[2]=1;
						vertice=vertices_front;
						break;
					case 1:
						normals[0]=0;
						normals[1]=0;
						normals[2]=-1;
						vertice=vertices_back;
						break;
					case 2:
						normals[0]=1;
						normals[1]=0;
						normals[2]=0;
						vertice=vertices_right;
						break;
					case 3:
						normals[0]=-1;
						normals[1]=0;
						normals[2]=0;
						vertice=vertices_left;
						break;
					case 4:
						normals[0]=0;
						normals[1]=1;
						normals[2]=0;
						vertice=vertices_top;
						break;
					case 5:
						normals[0]=0;
						normals[1]=-1;
						normals[2]=0;
						vertice=vertices_bottom;
						break;
				}
		
				tmpvert.normal[X_POS]=normals[0];
				tmpvert.normal[Y_POS]=normals[1];
				tmpvert.normal[Z_POS]=normals[2];
	
				tmpvert.color[R_POS]=cubiverse::color::get(Voxel->id, 0);
				tmpvert.color[G_POS]=cubiverse::color::get(Voxel->id, 1);
				tmpvert.color[B_POS]=cubiverse::color::get(Voxel->id, 2);
				tmpvert.color[A_POS]=1.0f;

				//all vertices
				for(int i=0; i < 11; i=i+3) {
					tmpvert.location[X_POS]	= x+vertice[i];
					tmpvert.location[Y_POS]	= y+vertice[i+1];
					tmpvert.location[Z_POS]	= z+vertice[i+2];
					vertices.push_back(tmpvert);
				}
	
				int oldsize = 0;
				indices.push_back(oldsize+0);
				indices.push_back(oldsize+1);
				indices.push_back(oldsize+2);
				indices.push_back(oldsize+2);
				indices.push_back(oldsize+3);
				indices.push_back(oldsize+0);
			}
			meshs[group]->setVertices(vertices);
			meshs[group]->setIndices(indices);
		}
	}
}
