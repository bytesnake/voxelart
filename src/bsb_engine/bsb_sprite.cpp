#include "../../inc/bsb_engine/bsb_sprite.h"

// --- bsb_sprite.cpp ---
// Diese Klasse stellt einen Sprite dar.
//
// Änderungen:
// - 21.02.12: unnötige Ausgaben entfernt (bit)

void Bsb_Sprite::render(){
	float matrix[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, matrix );
	Bsb_Vector* right = new Bsb_Vector( matrix[0], matrix[4], matrix[8] );
	right->mul(width);
	Bsb_Vector* up = new Bsb_Vector( matrix[1], matrix[5], matrix[9] );
	up->mul(height);

	// wenn eine Textur vorhanden ist, binde diese
	if(m_texture!=NULL){
		m_texture->bind();
	}
	
	if(m_r!=NULL){
//		std::cout << m_color[3]<<std::endl;
		glColor4f(m_r,m_g,m_b,m_a);
	}
	
	// jetzt male uns ein schönes Rechteck TODO schneller mit Arrays? Wahrscheinlich nicht (bit)
	glBegin(GL_QUADS);
	glTexCoord2f(texX2,texY1);
	glVertex3f( position->x + right->x - up->x, position->y + right->y - up->y, position->z + right->z - up->z );//b
	glTexCoord2f(texX2, texY2);
	glVertex3f( position->x + right->x + up->x, position->y + right->y + up->y, position->z + right->z + up->z );//a
	glTexCoord2f(texX1, texY2);
	glVertex3f( position->x - right->x + up->x, position->y - right->y + up->y, position->z - right->z + up->z );//d
	glTexCoord2f(texX1, texY1);
	glVertex3f( position->x - right->x - up->x, position->y - right->y - up->y, position->z - right->z - up->z );//c
	glEnd();
	
}

void Bsb_Sprite::setTexture(Bsb_Texture* p_texture){
	m_texture=p_texture;
}
void Bsb_Sprite::setColor(float p_r,float p_g,float p_b,float p_a){
	m_r=p_r;
	m_g=p_g;
	m_b=p_b;
	m_a=p_a;
}

void Bsb_Sprite::setTexCoords(float x1,float y1,float x2,float y2){
	texX1=x1;
	texY1=y1;
	texX2=x2;
	texY2=y2;
}
