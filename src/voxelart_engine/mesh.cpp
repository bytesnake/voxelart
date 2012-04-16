#include "../../inc/voxelart_engine/mesh.h"
vaEngine::Mesh::Mesh() {
	isRender = existData = false;
}

/**
 * creates the mesh from the vertices
 */
void vaEngine::Mesh::createMesh(){
	if(existData && !isRender) {
		glGenBuffers(1, &vboID); // Create the buffer ID, this is basically the same as generating texture ID's
		glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind the buffer (vertex array data)
	
		// Allocate space.  We could pass the mesh in here (where the NULL is), but it's actually faster to do it as a 
		// seperate step.  We also define it as GL_STATIC_DRAW which means we set the data once, and never 
		// update it.  This is not a strict rule code wise, but gives hints to the driver as to where to store the data	
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), &vertices.front());

		// Set the pointers to our data.  Except for the normal value (which always has a size of 3), we must pass 
		// the size of the individual component.  ie. A vertex has 3 points (x, y, z), texture coordinates have 2 (u, v) etc.
		// Basically the arguments are (ignore the first one for the normal pointer), Size (many components to 
		// read), Type (what data type is it), Stride (how far to move forward - in bytes - per vertex) and Offset 
		// (where in the buffer to start reading the data - in bytes)

		// Make sure you put glVertexPointer at the end as there is a lot of work that goes on behind the scenes
		// with it, and if it's set at the start, it has to do all that work for each gl*Pointer call, rather than once at
		// the end.	
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
		glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

		// When we get here, all the vertex data is effectively on the card
		//cout<<"put data on card"<<endl;
		glGenBuffers(1, &indexVBOID); // Generate buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID); // Bind the element array buffer
		// Upload the index array, this can be done the same way as above (with NULL as the data, then a 
		// glBufferSubData call, but doing it all at once for convenience)	
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

		isRender = true;
	}

}

void vaEngine::Mesh::updateMesh(){
	if(isRender) {
		glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind the buffer (vertex array data)
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), &vertices.front());	

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID); 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);
	}
}

void vaEngine::Mesh::render(){
	if(isRender) {
		//Enable VBOs
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		
		glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind the buffer (vertex array data)

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);

		// Set the state of what we are drawing (I don't think order matters here, but I like to do it in the same 
		// order I set the pointers
		// Resetup our pointers.  This doesn't reinitialise any data, only how we walk through it
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
		glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

		// Actually do our drawing, parameters are Primative (Triangles, Quads, Triangle Fans etc), Elements to 
		// draw, Type of each element, Start Offset
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));

		//Disable our client state back to normal drawing
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void vaEngine::Mesh::deleteMesh(){
	if(isRender) {
		glDeleteBuffers(1,&vboID);
		glDeleteBuffers(1,&indexVBOID);
		
		vboID=0;
		indexVBOID=0;
		isRender = false;
	}
}
void vaEngine::Mesh::setVertices(vector<Vertex> p_vertices){
	vertices=p_vertices;
	existData = true;
}
void vaEngine::Mesh::setIndices(vector<GLuint> p_indices){
	indices=p_indices;
	existData = true;
}



