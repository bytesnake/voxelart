#include "../../inc/bsb_engine/bsb_mesh.h"
Bsb_Mesh::Bsb_Mesh(){
    position=new Bsb_Vector();
    rotation=new Bsb_Vector();
    velocity=new Bsb_Vector();
}

/**
 * creates the mesh from the vertices
 */
void Bsb_Mesh::createMesh(){
	//cout << "Create Mesh " << m_x << m_z << endl;
	glGenBuffers(1, &vboID); // Create the buffer ID, this is basically the same as generating texture ID's
	//cout << "CreateMesh " << m_x << m_z << endl;
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

}

void Bsb_Mesh::updateMesh(){
	glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind the buffer (vertex array data)
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), &vertices.front());	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);
}

void Bsb_Mesh::render(){

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

void Bsb_Mesh::deleteMesh(){
		glDeleteBuffers(1,&vboID);
		glDeleteBuffers(1,&indexVBOID);
		
		vboID=0;
		indexVBOID=0;
}
void Bsb_Mesh::setVertices(vector<Vertex> p_vertices){
	vertices=p_vertices;
}
void Bsb_Mesh::setIndices(vector<GLuint> p_indices){
	indices=p_indices;
}
/*
    void Bsb_Mesh::setVertices(float p_vertices[],int p_count){
		vertex_count=p_count;
	
		vertices=p_vertices;
    }
    void Bsb_Mesh::setColors(float p_colors[]){
		colors=p_colors;
    }
    void Bsb_Mesh::setIndices(unsigned char p_indices[],int p_count){
    	indices=indices;
    	indices_count=p_count;
    }
    void Bsb_Mesh::setTextureCoords(float p_texcoords[]){
    	texCoords=p_texcoords;
    }
    void Bsb_Mesh::setNormals(float p_normals[]){
    	normals=p_normals;
    }
	void Bsb_Mesh::setTexture(Bsb_Texture* p_texture){
		texture=p_texture;
	}
 
 
     
    void Bsb_Mesh::render(){
        
        //
        // ACHTUNG:
        // Die zuletzt angegebene Transformation wird als erstes ausgeführt!
        // Daher zuerst verschieben, dann rotieren und dann skalieren angeben.
        //
        
        //Mesh an die Richtige Stelle verschieben
       // glTranslatef(position->x,position->y,position->z);

        //TODO rotation verbessern? zum Beispiel eine MATIX oO oder einfach nur die drei werte mitgeben, also z.b. so :glRotatef(maximalrotation, xr, yr, zr);
        if(rotation->x!=0){
            glRotatef(rotation->x, 1.0f, 0.0f, 0.0f); // Rotate On The X Axis  
        }
        if(rotation->y!=0){
            glRotatef(rotation->y, 0.0f, 1.0f, 0.0f); // Rotate On The Y Axis  
        }
        if(rotation->z!=0){
            glRotatef(rotation->z, 0.0f, 0.0f, 1.0f); // Rotate On The Z Axis  
        }
        

        //TODO skalieren
       
        if(colors!=NULL){
            glEnableClientState(GL_COLOR_ARRAY);
        	glColorPointer(3,GL_FLOAT, 0, colors);
        }
        
		
        if(texCoords!=NULL){
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
           // texture.bind();
            texture->bind();
            glTexCoordPointer(2,GL_FLOAT, 0, texCoords);
        }
        if(normals!=NULL){
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(0,GL_FLOAT,normals);
        }



		//  GL11.glColor3f(0.0f,1.0f,1.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_FLOAT, vertex_count,vertices);
        if(indices==NULL){
//      	   	glDrawArrays(GL_POINTS,0,NumVertices);
            glDrawArrays(GL_TRIANGLES,0,vertex_count);
        }else{
            //Draw elements
               glDrawElements( GL_TRIANGLES, //mode
                        indices_count,  //count, ie. how many indices
                        GL_UNSIGNED_BYTE, //type of the index array
                        indices);
        }
		glDisableClientState(GL_VERTEX_ARRAY);
	//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
    }*/


