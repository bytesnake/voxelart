#include "../inc/GUI.h"
#include <iostream>

using namespace std;

/*
 * Wechselt das Menü
 */
void cubiverse::GUI::changeMenu(string menu) {
	if((menu == "Singleplayer") || (menu == "Multiplayer")) {
		this->menu=menu;
		draw.disconnect_all_slots();
		draw.connect(boost::bind( &cubiverse::GUI::drawMap, this));
		draw.connect(boost::bind( &cubiverse::GUI::drawBottom, this));
	}	
	else if(menu == "Voxel") {
		this->menu=menu;
		draw.disconnect_all_slots();
		draw.connect(boost::bind( &cubiverse::GUI::drawBottom, this));
	}
	else if(menu == "Main")  {
		this->menu=menu;

		std::string entry[] = {"Singleplayer", "Multiplayer", "Voxel", "Options", "Exit" };
		for(int i=0; i < sizeof(entry) / sizeof(entry[0]); i++) {
			addButton(entry[i], width/3, height-100-i*70, 200, 50);
		}
		draw.disconnect_all_slots();
		draw.connect(boost::bind( &cubiverse::GUI::drawMenu, this));
		draw.connect(boost::bind( &cubiverse::GUI::drawButton, this));
	}
}

void cubiverse::GUI::drawButton() {
	for(int i=0; i < buttonName.size(); i++) {
		char* buffer = new char[buttonName.at(i).length()+1];
		strcpy(buffer,buttonName.at(i).c_str());

		int x = buttonPosition.at(i*4);
		int y = buttonPosition.at(i*4+1);
		int p_width = buttonPosition.at(i*4+2);
		int p_height = buttonPosition.at(i*4+3);

		//Zeichnet den Button
		glTranslatef(x, y, 0.0f);
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		glBegin(GL_LINES);
			glVertex3f(-0.1f, -0.1f, 0.0f); 
			glVertex3f((float)p_width+0.1f, -0.1f, 0.0f); 
			glVertex3f((float)p_width+0.1f, (float)p_height+0.1f, 0.0f); 
			glVertex3f(-0.1f, (float)p_height+0.1f, 0.0f);
		glEnd();	
	
		glColor4f(0.0f, 0.0f,0.0f,1.0f);
		glBegin(GL_QUADS);
			glVertex3f(0.0f, 0.0f, 0.0f); 
			glVertex3f((float)p_width, 0.0f, 0.0f); 
			glVertex3f((float)p_width, (float)p_height, 0.0f); 
			glVertex3f(0.0f, (float)p_height, 0.0f); 
		glEnd();

		//Schrift zeichnen
		glColor4f(0.0f,0.0f,0.0f,1.0f);//Schriftfarbe auf weiß setzen
		glEnable(GL_TEXTURE_2D);
		std_font->draw_string( p_width/2-(buttonName.at(i).length()/2*15),p_height/5, buffer);
		glTranslatef(-x, -y, 0.0f);		
		glDisable(GL_TEXTURE_2D);
	}
}

void cubiverse::GUI::addButton(string name, int x, int y, int width, int height) {
	buttonName.push_back(name);
	buttonPosition.push_back(x);
	buttonPosition.push_back(y);
	buttonPosition.push_back(width);
	buttonPosition.push_back(height);
}

/*
 * Überprüft eine Kollision vom Mauszeiger mit einem Button
 * und gibt den Namen des Buttons zurücl
 * Die Mausposition ist von der oberen linken Ecke
 * Die Position in openGL, aber von der unteren linken Ecke
*/
string cubiverse::GUI::checkButton(int p_x, int p_y) {
	for(int i=0; i < buttonName.size(); i++) {
		int x = buttonPosition.at(i*4);
		int y = buttonPosition.at(i*4+1);
		int p_width = buttonPosition.at(i*4+2);
		int p_height = buttonPosition.at(i*4+3);
		if( y < (height-p_y) && x < p_x && (y+p_height) > (height-p_y) && (x+p_width) > p_x) {
			return buttonName[i];
		}
	}
	return "";
}
		
void cubiverse::GUI::drawMenu() {
	//Zeichnet den transparenten Hintergrund vom Menü
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	glColor4f(0.3, 0.3, 0.3, 0.1);
	glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.0f, 0.0f);  
		glVertex3f(width, 0.0, 0.0f);
		glVertex3f(width, height, 0.0f);  
		glVertex3f(0.0f, height, 0.0f);
	glEnd();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
}

void cubiverse::GUI::drawMap() {
}
void cubiverse::GUI::drawBottom() {
	//cout << "drawBottom" << endl;	
}
void cubiverse::GUI::drawFPS(int fps) {
	char tmp[10];
	sprintf(tmp,"FPS: %d",fps);
	std_font->draw_string(width-130,height-50,tmp);
}
	
cubiverse::GUI::GUI(int width, int height) {
	this->std_font=new Bsb_Font("Data/test.png","Data/test.bfd");

	this->width = width;
	this->height = height;
	this->menu="Main";
	this->changeMenu("Main");
}
