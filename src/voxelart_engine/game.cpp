#include "../../inc/voxelart_engine/game.h"

// --- bsb_game.cpp ---
// 
//
// Änderungen:
// - 21.02.12: aufräumen (bit)

//Maximale FPS
const int DESIRED_FPS=300;


void vaEngine::Game::updateFPS(){
	if (glutGet(GLUT_ELAPSED_TIME) - lastTimeFPS >= 1000) {
		FPS = currentFPS;
		cout << "FPS: " << FPS << endl;
		currentFPS = 0;
		lastTimeFPS = glutGet(GLUT_ELAPSED_TIME);
	}
	currentFPS++;
}

void vaEngine::Game::timer(int) {
	//Vergangende Zeit
	int passed=(glutGet(GLUT_ELAPSED_TIME)-lastTimeStamp);

	//Update mit der verstrichenden Zeit in Sekunden
	this->update(passed/1000.0f);
	
	//Update FPS
	this->updateFPS();

	//Refresh lastTimeStamp
	lastTimeStamp=glutGet(GLUT_ELAPSED_TIME);

	//Nun Render alles
	this->render();
	
	int passFPS=(glutGet(GLUT_ELAPSED_TIME)-lastTimeFPS);
  	
	//Berechne die Zeit, die gewartet werden soll, wenn es eine FPS Beschränkung gibt
  	float diff=(float)passFPS/(float)currentFPS+1;
  	float tomuch=diff-1000/DESIRED_FPS;
  	int towait=1000/DESIRED_FPS-tomuch;
   	if(towait<0) towait=0;

	//Nun die Funktion mit der Verzögerung erneut aufrufen
	glutTimerFunc(towait, callTimer, 0);
}

void vaEngine::Game::hideCursor(){
	glutSetCursor(GLUT_CURSOR_NONE); 
}
void vaEngine::Game::showCursor() {
	glutSetCursor(GLUT_CURSOR_INFO);
}

void vaEngine::Game::initGL(){
	glewInit();
	glViewport(0, 0, width, height);						// Reset The Current Viewport And Perspective Transformation
	glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glLoadIdentity();										// Reset The Projection Matrix
	gluPerspective(45.0f, width / height, 0.1f, 1000.0f);	// Calculate The Aspect Ratio Of The Window
	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();
	
	//Nicht sichtbare Dreiecke nicht zeichnen
	glCullFace(GL_BACK); 
	glEnable(GL_CULL_FACE);
	
	//Alle Buffer löschen
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClearDepth(1.0f);
	glClearStencil(0);  

	//Texture Mapping
	glEnable(GL_TEXTURE_2D); 

	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	
	//Tiefentest aktivieren
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LEQUAL);
	
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial (GL_FRONT_AND_BACK, GL_EMISSION ) ;
	glShadeModel(GL_SMOOTH);

	// Really Nice Perspective Calculations
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
	glFrustum( -1.6, 1.6, -1.2, 1.2, 1.5, 6.5 ); 
}

void vaEngine::Game::setSize(int width,int height){
	//TODO viewfrustum umsetzen, falls dies während des Spiels passiert
	this->width=width;
	this->height=height;
}

void vaEngine::Game::setTitle(char* p_title){
	glutSetWindowTitle(p_title);
}

void vaEngine::Game::start(int arg_c,char** arg_v){
	//Set Instance to Static
	currentInstance = this;

	glutInit(&arg_c,arg_v);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(width,height);
	this->window=glutCreateWindow("");
		
	//Initalisiere openGL
	this->initGL();

	//Den selbst definierten openGL Flags immer den Vorang geben
	this->init();

	//Binde Mouse Events zu unseren Funktionen
	glutMouseFunc(callMouseEvent);
	glutMotionFunc(callMouseMotion); 
	glutPassiveMotionFunc(callMouseMotion); 

	//Binde Tasten Events zu unseren Funktionen
	glutKeyboardFunc(callKeyPressed);
	glutKeyboardUpFunc(callKeyReleased);
	glutSpecialFunc(callSpecialKeyPressed);

	//wenn das Fenster verschoben wird, neu malen
	glutDisplayFunc(callRender);
	
	this->timer(0);//unseren Timer starten
	glutMainLoop();//die main-Schleife von GLUT starten
}

void vaEngine::Game::quit(){
	glutDestroyWindow(window);
	exit(0);
}

void vaEngine::Game::toggleFullscreen(){
	//Switche den Fullscreen und setzte ihn neu
	fullscreen=!fullscreen;
	if (fullscreen){
		glutFullScreen();
	} else {
		glutReshapeWindow(width, height);
	}
}

void vaEngine::Game::specialkey_pressed(int key, int x, int y){
	if(key==GLUT_KEY_F11){
		toggleFullscreen();
	}
	if(key==GLUT_KEY_F2){
		takeScreenshot();
	}
}

void vaEngine::Game::takeScreenshot(){
	glReadBuffer(GL_BACK);

	//TODO nutze width und height des Bildschirms, wenn ein Screenshot im Vollbild modus gemacht werden soll
	GLvoid *imageData = malloc(width*height*(/*BIT_R+BIT_G+BIT_B+BIT_A*/32)); //Allocate memory for storing the image
	
	glReadPixels(0, 0,width,height, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //Copy the image to th
	//return gluUnProject((GLdouble)screenX,(GLdouble)realY, (GLdouble)winZ, mvmatrix,projmatrix,viewport, &wx,&wy,&wz); 


	//
	// Flip and invert the PNG image since OpenGL likes to load everything
	// backwards from what is considered normal!
	//
	unsigned char *imagePtr = (unsigned char*)imageData;
	int halfTheHeightInPixels = height/ 2;
	int heightInPixels = height;

	// Assuming RGBA for 4 components per pixel.
	int numColorComponents = 4;

	// Assuming each color component is an unsigned char.
	int widthInChars =width* numColorComponents;

	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;

	for( int h = 0; h < halfTheHeightInPixels; ++h )
	{
		top = imagePtr + h * widthInChars;
		bottom = imagePtr + (heightInPixels - h - 1) * widthInChars;

		for( int w = 0; w < widthInChars; ++w )
		{
		    // Swap the chars around.
		    temp = *top;
		    *top = *bottom;
		    *bottom = temp;

		    ++top;
		    ++bottom;
		}
	}

	// Bilddaten encodieren und abspeichern		
	LodePNG::Encoder encoder;
	encoder.addText("Comment", "Bsb_Engine screenshot");

	//Daten in buffer schreiben
	std::vector<unsigned char> buffer;
	encoder.encode(buffer, (const unsigned char*)imageData, width,height);

	//Aus Buffer in PNG speichern
	LodePNG::saveFile(buffer, "screenshot.png");
}

