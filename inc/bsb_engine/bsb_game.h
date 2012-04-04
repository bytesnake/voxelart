#ifndef BSB_GAME_H
#define BSB_GAME_H
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <GL/glut.h>
#include <iostream>

#include "bsb_vector.h"
#include "bsb_object.h"
#include "bsb_mesh.h"
#include "bsb_camera.h"
#include "bsb_FPCamera.h"
#include "bsb_tpcamera.h"
#include "bsb_texture.h"
#include "bsb_font.h"
#include "bsb_sprite.h"

/**
 * Hauptklasse der Bsb Engine.
 * Die Spielklasse des fertigen Spiels sollte von dieser Klasse ableiten
 */
class Bsb_Game{
	public:
		/**
		 * diese Methode wird einmal zu Beginn aufgerufen, damit du das Spiel initialisieren kannst.
		 */
		virtual void init()=0;
		/**
		 * diese Methode wird immer aufgerufen, wenn eine Taste gedrückt wird.
		 */
		virtual void key_pressed(unsigned char key)=0;
		/**
		 * diese Methode wird immer aufgerufen, wenn eine Taste losgelassen wird.
		 */
		virtual void key_released(unsigned char key)=0;
		/**
		 * Diese Methode wird immer aufgerufen, wenn die Maus gedrückt wird.
		 */
		virtual void mouse_event(int button, int state, int x, int y)=0;
		/**
		 * Diese Methode wird immer aufgerufen, wenn die Maus sich bewegt.
		 */
		virtual void mouse_motion(int x,int y)=0;
		/**
		 * Diese Methode wird in jedem Frame aufgerufen, damit du deine Spiellogik anhand der vergangenen Sekunden (seit dem letzten Frame) berechnen kannst.
		 */
		virtual void update(float p_seconds)=0;
		/**
		 * Diese Methode wird in jedem Frame aufgerufen. Hier solltest du alle deine schönen Graphiken rendern.
		 */
		virtual void render()=0;
		
		/**
		 * setzt den Titel des Spielfensters
		 */
		void setTitle(char* p_title);
		/**
		 * setzt die Fenstergröße
		 */
		void setSize(int p_width,int p_height);
		/**
		 * beended das Spiel
		 */
		void quit();
		/**
		 * macht den Mauszeiger unsichtbar
		 */
		void hideCursor();
		/*
		 * zeigt einen Cursor
		*/
		void showCursor();
		/**
		 * welchselt zwischen Vollbild und Fenster-modus
		 */
		void toggleFullscreen();
		/**
		 * macht einen Screenshot
		 */
		void takeScreenshot();
		
		
		void start(int arg_c,char** arg_v);
		void initGL();
		
		/**
		 * in dieser Variable wird die Anzahl der Frames in der letzen Sekunde gespeichert.
		 */
		int currentFPS;
		
		/**
		 * Breite des Fensters
		 */
		int width;
		/**
		 * Höhe des Fensters
		 */
		int height;
	private:
		/**
		 * die ID, mit der wir das Fenster ansprechen können.
		 */
		int window;
		/**
		 * ist das Fenster momentan Vollbild?
		 */
		bool fullscreen;
};
#endif
