#include "../../inc/bsb_engine/bsb_font.h"

using namespace std;

Bsb_Font::Bsb_Font(const char* bitmap,const char* infofile){

	fontmap=new Bsb_Texture(bitmap);
	int font_height;
	
//	fclose(f);
	char* buffer;
	FILE *file;
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
	cout << fileLen << endl;

/*	//Allocate memory
	buffer=(char *)malloc(fileLen+1);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
                                fclose(file);
		return;
	}*/
	
/*	int* test=(int*) buffer;
	cout << "start" << endl;
	for(int i=0;i<10;i++){
		cout<<test[i]<<endl;
	}*/
	

	/*
	cout << endl <<"start"<<endl;
	for(int i=0;i<10;i++){
		cout <<buffer[i]<<endl;
	}*/

	//Read file contents into buffer
	//fread(buffer, fileLen, 1, file);
	
	//fseek(file, 0, SEEK_SET);
	font_height=0;
	fread(&font_height,1,1,file);
	cout << "height:"<<font_height<<endl;
	/*int tmp;
	fread(&tmp,1,1,file);
	cout << "height:"<<tmp<<endl;
	for(int i=0;i<50;i++){
		fread(&tmp,1,1,file);
		cout <<tmp<<endl;
	}*/
	
	for(int i=0;i<256;i++) {
		int tmp=0;
		fread(&tmp,1,1,file);
		cout << tmp << endl;
		char_widths[i]=tmp;
	 }
	
	fclose(file);
	
//	dump_buffer(buffer,fileLen);
	//exit(0);

	//Do what ever with buffer

	//free(buffer);
	//exit(0);
		//float delta=0;
     /*       int width = fm.stringWidth("W")+10;
            int height = fm.getHeight();
            int lineWidth = (width > height) ? width * 16 : height * 16;
            if(!directionSet) {
                if(lineWidth > bitmapSize) {
                    delta = -2;
                }
                else {
                    delta = 2;
                }
                directionSet = true;
            }
            if(delta > 0) {
                if(lineWidth < bitmapSize) {
                    fontSize += delta;
                }
                else {
                    sizeFound = true;
                    fontSize -= delta;
                }
            }
            else if(delta < 0) {
                if(lineWidth > bitmapSize) {
                    fontSize += delta;
                }
                else {
                    sizeFound = true;
                    fontSize -= delta;
                }
            }*/

//       int texture = buf.get(0);                           // Return Image Address In Memory
        base = glGenLists(256);                    // Storage For 256 Characters
        /* Generate the display lists.  One for each character in the standard/extended ASCII chart.
         */   fontmap->bind();
        float textureDelta = 1.0f / 16.0f;
		
		for(int i=0;i<256;i++){
			cout << char_widths[i]<<endl;
		}
		
        for(int i=0;i<256;i++) {
			
            float u = ((float)(i % 16)) / 16.0f;
            float v = 1.f - (((float)(i / 16)+1) / 16.0f);
            glNewList(base + i, GL_COMPILE);
         
           // glBindTexture(GL_TEXTURE_2D, texture);
        /*    glBegin(GL_QUADS);
            glTexCoord2f(u, v);
            glVertex3f(-0.0450f, 0.0450f, 0.0f);
            glTexCoord2f((u + textureDelta), v);
            glVertex3f(0.0450f, 0.0450f, 0.0f);
            glTexCoord2f((u + textureDelta), v - textureDelta);
            glVertex3f(0.0450f, -0.0450f, 0.0f);
            glTexCoord2f(u, v - textureDelta);
            glVertex3f(-0.0450f, -0.0450f, 0.0f);
            glEnd();*/
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
        
     //   exit(0);
	FILE * pFile;
	char mystring [100];
	int line=0;

/*	pFile = fopen ("Data/font1.bfd" , "r");
	if (pFile == NULL){
		cerr << "file not found" << endl;
	}else {
		while(!feof(pFile)){
		if ( fgets (mystring , 100 , pFile) != NULL ){
			cout <<line<<":"<< mystring << endl;
			line++;
		}
		}
			
	fclose (pFile);
	}*/
/*	  ofstream file ("Data/example.bin", ios::out|ios::binary||ios::beg);
	  if (file.is_open())
	  {
	//	size = file.tellg();
		memblock = new char [size];
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();

		cout << "the complete file content is in memory";

		delete[] memblock;
	  }
	  else{ cout << "Unable to open file";}*/
	  
/*	unsigned long i=11,z;
	int test[4]={100,120,543};
//	char a[11]="Datenblock",b[11];
	FILE*f;

	f=fopen("Data/datei.dat","wb");//öffnen der Datei im binären Schreibmodus

//	fwrite(&i,1,sizeof(unsigned long),f);//Schreibe Variable i in die Datei
	char testx='t';
	fwrite(&testx,1,sizeof(char),f);
	fwrite(&test,1,sizeof(test),f);//Schreibe den Datenblock in die Datei
	fclose(f);
	*/
}


void Bsb_Font::draw_string(int p_x,int p_y,const char* p_string){
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
