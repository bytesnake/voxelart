#include "../inc/VoxelEditor.h"
#include "../inc/color.h"
#include <math.h>

//void cubiverse::VoxelEditor::VoxelEditor() {
//	voxels.push_back(
void cubiverse::VoxelEditor::refreshVisibility() {
	for(int group = 0; group < voxels.size(); group++)  {
	std::map<std::pair<uint32_t,std::pair<uint32_t,uint32_t > >, Cube::pointer_t>::iterator it;
	for ( it=voxels[group].begin(); it!=voxels[group].end(); it++) {
		int x = (*it).first.first;
		int y = (*it).first.second.first;
		int z = (*it).first.second.second;
		Cube::pointer_t Voxel = (*it).second;

		if(!hasVoxel(x,y,z+1, group)) Voxel->show(0);
		else Voxel->hide(0);
		if(!hasVoxel(x,y,z-1, group)) Voxel->show(1);
		else Voxel->hide(1);
		if(!hasVoxel(x+1,y,z, group)) Voxel->show(2);
		else Voxel->hide(2);
		if(!hasVoxel(x-1,y,z, group)) Voxel->show(3);
		else Voxel->hide(3);
		if(!hasVoxel(x,y+1,z, group)) Voxel->show(4);
		else Voxel->hide(4);
		if(!hasVoxel(x,y-1,z, group)) Voxel->show(5);
		else Voxel->hide(5);
	}
	}
}
		
void cubiverse::VoxelEditor::render(float playerX, float playerY, float playerZ) {
	//Zeichne einen Kreis
	float x = 0.0f;
	float z = 0.0f;
	float radius = 10.0f;

	glBegin(GL_POLYGON);
	for( double theta = 0.0; theta < M_PI; theta +=  M_PI / 360.0 ) {
		x =  ( cos( theta ) * radius );
		z =  ( sin( theta ) * radius);
		glVertex3f( x, 20.0f, z );
	}

	Bsb_Vector* coll = checkCollision(playerX, playerY, playerZ);
	//if(coll->y != playerY) {
	//	Cube::pointer_t newCube = boost::make_shared<Cube>(1);
	//	voxels[0][make_pair(coll->x,make_pair(coll->y,coll->z))] = newCube;
		
	//}
		
	//Und dann die Meshs
	//for(int mesh = 0; mesh < meshs.size(); mesh++)
		//meshs[mesh]->render();

	//if(coll->y != playerY) {
	//	delVoxel(coll->x, coll->y, coll->z, 0);
		
	//}
}

Bsb_Vector* cubiverse::VoxelEditor::checkCollision(float p_x, float p_y, float p_z) {
	float matrix[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, matrix );
	Bsb_Vector* camera= new Bsb_Vector( matrix[2], matrix[6], matrix[10] );
	camera->div(2.0f);

	Bsb_Vector* camPos = new Bsb_Vector(p_x, p_y, p_z);

	cout << "X:" << camera->x << " Y:" << camera->y << " Z:" << camera->z << endl;
	if(p_y > 20 && camera->y > 0) {
		bool run = true;
		while(camPos->y > 20 && run) {
			camPos->sub(camera);
			for(int mesh = 0; mesh < meshs.size(); mesh++) {
				if(hasVoxel(camPos->x,camPos->y,camPos->z, mesh)) run = false;
			}
		}
		cout << "FOUND POS:" << camPos->x  << " : " << camPos->z << endl;
		return camPos;
	}			
	

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
	std::map<std::pair<uint32_t,std::pair<uint32_t,uint32_t > >, Cube::pointer_t>::iterator it;
	vector<Vertex> vertices;
	vector<GLuint> indices;	
	for (it=voxels[group].begin(); it!=voxels[group].end(); it++) {
		int x = (*it).first.first;
		int y = (*it).first.second.first;
		int z = (*it).first.second.second;
		Cube::pointer_t Voxel = (*it).second;
		Voxel->renderToMesh(x,y,z,&vertices,&indices);		
	}
	meshs[group]->setVertices(vertices);
	meshs[group]->setIndices(indices);
}
