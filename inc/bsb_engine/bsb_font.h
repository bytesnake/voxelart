#include <stdio.h>
#include "bsb_texture.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>


class Bsb_Font{
	int font_height;
	int char_widths[256];
	Bsb_Texture* fontmap;
	int base;

	public:
		/**
		 * erstellt eine Schrift mithilfe des Dateinamen der .png und der .bfd-Dateien, die von dem Java-Helper programm erstellt wurden
		 */
		Bsb_Font(const char* bitmap,const char* infofile);
		/**
		 * malt einen String dieser Schriftart auf den Bildschirm.
		 * TODO Tabulatoren, neue Zeile, zentrierte Schrift, uvm.
		 */
		void draw_string(int p_x,int p_y,const char* p_string);
	
};
