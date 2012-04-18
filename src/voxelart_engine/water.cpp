#include "../../inc/voxelart_engine/water.h"

void vaEngine::Water::RenderReflection()
{
    glViewport(0,0, this->size, this->size);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(1.0, -1.0, 1.0);
    double plane[4] = {0.0, this->waterHeight+1, 0.0, 0.0}; //water at y=0
    glEnable(GL_CLIP_PLANE0);
    glClipPlane(GL_CLIP_PLANE0, plane);

    for(int i=0; i < arroundMesh.size(); i++)
	arroundMesh[i] -> render();

    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();

    //render reflection to texture
    this->reflectionMap->bind();
    //glCopyTexSubImage2D copies the frame buffer
    //to the bound texture
    glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0,this->size, this->size);
}

void vaEngine::Water::RenderRefraction()
{
    glViewport(0,0, this->size, this->size);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    //normal pointing along negative y
    double plane[4] = {0.0, this->waterHeight-1, 0.0, 0.0};
    glEnable(GL_CLIP_PLANE0);
    glClipPlane(GL_CLIP_PLANE0, plane);

    for(int i=0; i < arroundMesh.size(); i++)
	arroundMesh[i] -> render();

    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();

    //render color buffer to texture
	
    glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0,this->size, this->size);
    this->refractionMap->bind();
    //render depth to texture
    this->depthMap->bind();
    glCopyTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT, 0,0, this->size,this->size, 0);
}

void vaEngine::Water::RenderWater() 
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	this->reflectionMap->bind();

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	this->refractionMap->bind();

	glActiveTextureARB(GL_TEXTURE2_ARB);
	glEnable(GL_TEXTURE_2D);
	this->normalMap->bind();

	glActiveTextureARB(GL_TEXTURE3_ARB);
	glEnable(GL_TEXTURE_2D);
	this->depthMap->bind();

	this->waterMesh->render();
}
