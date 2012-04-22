#ifndef VOXELART_GAME_H
#define VOXELART_GAME_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

#include "vector.h"
#include "object.h"
#include "mesh.h"
#include "camera.h"
#include "fpcamera.h"
#include "font.h"
#include "sprite.h"
#include "water.h"
#include "texture.h"

/**
 * Hauptklasse der Bsb Engine.
 * Die Spielklasse des fertigen Spiels sollte von dieser Klasse ableiten
 */
namespace vaEngine { 
	class Game {
		public:
			// Diese Funktion wird beim initialisieren aufgerufen und kann beliebig überschrieben werden
			virtual void init()=0;
			// Diese Methode wird in jedem Frame aufgerufen, damit man die Spiellogik anhand der vergangenen Sekunden (seit dem letzten Frame) berechnen kannt.
			virtual void update(float p_seconds)=0;
			// Diese Methode wird in jedem Frame aufgerufen. Hier solltest du alle deine schönen Graphiken rendern.
			virtual void render()=0;
			// diese Methode wird immer aufgerufen, wenn eine Taste gedrückt wird.
			virtual void key_pressed(unsigned char key)=0;
			// diese Methode wird immer aufgerufen, wenn eine Taste losgelassen wird.
			virtual void key_released(unsigned char key)=0;
			// Diese Methode wird immer aufgerufen, wenn die Maus gedrückt wird.
			virtual void mouse_event(int button, int state, int x, int y)=0;
			// Diese Methode wird immer aufgerufen, wenn die Maus sich bewegt.
			virtual void mouse_motion(int x,int y)=0;

			// setzt den Titel des Spielfensters
			void setTitle(char* p_title);
			// setzt die Fenstergröße
			void setSize(int p_width,int p_height);

			// macht den Mauszeiger unsichtbar
			void hideCursor();
			// zeigt einen Cursor
			void showCursor();
			// welchselt zwischen Vollbild und Fenster-modus
			void toggleFullscreen();
			// macht einen Screenshot
			void takeScreenshot();
			//Spezielle Tasten
			void specialkey_pressed(int key, int x, int y);

			//Starte das Spiel
			void start(int arg_c,char** arg_v);
			//Initialisiere einige vorbestimmte Flags
			void initGL();
			// beende das Spiel
			void quit();
			//Update FPS
			void updateFPS();
			//The Timer
			void timer(int);
		
			// in dieser Variable wird die Anzahl der Frames in der letzen Sekunde gespeichert.
			int currentFPS;
			//Diese Variable wird alle Sekunde geupdatet
			int FPS;
		
			// Breite/Höhe des Fensters
			int width;
			int height;
		private:
			//Fenster ID
			int window;
			//Ist das Fenster im Vollbild
			bool fullscreen;
			//Letzte Zeit bei der gerendert wurde
			long lastTimeFPS;
			//Letzte Zeit bei der time() aufgerufen wurde
			int lastTimeStamp;

	};

}

//Leider müssen hier ein paar statische umleitungen in die Klasse vorgenommen werden, da freeGLUT für C geschrieben wurde :(
static vaEngine::Game* currentInstance;
static void callRender() { currentInstance->render(); }
static void callKeyPressed(unsigned char key, int x, int z) { currentInstance->key_pressed(key); }
static void callKeyReleased(unsigned char key, int x, int z) { currentInstance->key_released(key); }
static void callMouseEvent(int button, int state, int x, int y) { currentInstance->mouse_event(button, state, x, y); }
static void callMouseMotion(int x, int y) { currentInstance->mouse_motion(x,y); } 
static void callTimer(int) { currentInstance->timer(0); }
static void callSpecialKeyPressed(int key, int x, int y) { currentInstance->specialkey_pressed(key, x, y); }

#endif
