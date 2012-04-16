#include "../../inc/voxelart_engine/font.h"

using namespace std;

/**
 * erstellt eine Schrift mithilfe des Dateinamen der .png und der .bfd-Dateien, die von dem Java-Helper programm erstellt wurden
*/
vaEngine::Font::Font(const char* bitmap,const char* infofile) {

	fontmap=new Texture(bitmap);
	int font_height = 0;
	
	FILE* file;
	char* buffer;
	unsigned long fileLen;

	//Open file
	file = fopen(infofile, "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", infofile);
		return;
	}
	
	//Get file length
	fseek(file, 0, SEEK_END);
	fileLen=ftell(file);
	fseek(file, 0, SEEK_SET);

	fread(&font_height,1,1,file);
	cout << "height:"<<font_height<<endl;
	
	//Load the Chars
	for(int i=0;i<256;i++) {
		int tmp=0;
		fread(&tmp,1,1,file);
		cout << tmp << endl;
		char_widths[i]=tmp;
	 }
	
	fclose(file);
	
        base = glGenLists(256);                    // Storage For 256 Characters
        /* 
	 * Generate the display lists.  One for each character in the standard/extended ASCII chart.
         */   
	fontmap->bind();
        float textureDelta = 1.0f / 16.0f;
		
	//TODO: Remove Debug
	for(int i=0;i<256;i++){
		cout << char_widths[i]<<endl;
	}
		
        for(int i=0;i<256;i++) {
			
            float u = ((float)(i % 16)) / 16.0f;
            float v = 1.f - (((float)(i / 16)+1) / 16.0f);
            glNewList(base + i, GL_COMPILE);
         
            float char_texx=32*(i%16);//i%32;//fontInfo[i*4];            
            float char_texy=((int)(i/16))*32;//fontInfo[i*4+1];
			//cout << char_texx<<"*"<<char_texy<<endl;
            int char_width=char_widths[i];        
			//cout << i <<":"<<char_widths[i]<<endl;
            //cout << "font_height:" <<font_height << endl;
            int char_height=font_height;//fontInfo[i*4+3];
//			char_width=100;
//			char_height=100;
			
			//cout << "CHAR"<<char_width<<"x "<<char_height<<"  ,  "<<font_height<<endl;
			glBegin(GL_QUADS);
				glColor3f(1.0f,1.0f,1.0f);
				glTexCoord2f(0,1);
				glTexCoord2f((char_texx)/512.0f,(char_texy+char_height)/512.0f);
				glVertex3i(0, 0,1);
				glTexCoord2f(1,1);
				glTexCoord2f((char_texx+char_width)/512.0f,(char_texy+char_height)/512.0f);
				glVertex3i(char_width, 0,1);
				glTexCoord2f(1,0);
				glTexCoord2f((char_texx+char_width)/512.0f,(char_texy)/512.0f);
				glVertex3i(char_width, char_height,1);
				glTexCoord2f(0,0);
				glTexCoord2f((char_texx)/512.0f,(char_texy)/512.0f);
				glVertex3i(0, char_height,1);

			glEnd();
            glEndList();
        }
        
}

/**
 * malt einen String dieser Schriftart auf den Bildschirm.
 * TODO Tabulatoren, neue Zeile, zentrierte Schrift, uvm.
*/
void vaEngine::Font::draw_string(int p_x,int p_y,const char* p_string){
	glPushMatrix();
	glTranslatef(p_x,p_y,0.0f);
	fontmap->bind();
	for(int i=0;i<strlen(p_string);i++) {
		glCallList(base + p_string[i]);
		glTranslatef(char_widths[p_string[i]],0.0f, 0.0f);
 	}
	glTranslatef(-p_x, -p_y, 0.0f);
	glPopMatrix();
}
