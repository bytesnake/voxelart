#include "../../inc/bsb_engine/bsb_game.h"

// --- bsb_game.cpp ---
// 
//
// Änderungen:
// - 21.02.12: aufräumen (bit)

Bsb_Game* actGame;
int lastFPS;
int fps;
int DESIRED_FPS=20000;


int lastTimeStamp;

void updateFPS(){
	if (glutGet(GLUT_ELAPSED_TIME) - lastFPS > 1000) {
		actGame->currentFPS=fps;// set the fps of the game
		cout << "FPS: " << fps << endl;
		fps = 0;
		lastFPS += 1000;
	}
	fps++;
}
void bsb_render(){
	actGame->render();
}
void bsb_move(){
	
	actGame->render();
}
void timer(int) {
	int passed=(glutGet(GLUT_ELAPSED_TIME)-lastTimeStamp);

	actGame->update(passed/1000.0f);//TODO calculate time
	
	
	lastTimeStamp=glutGet(GLUT_ELAPSED_TIME);
	updateFPS();
	bsb_move();
	
	int passFPS=(glutGet(GLUT_ELAPSED_TIME)-lastFPS);
   // glutPostRedisplay();
   //cout << passed << endl;
   	//cout <<(1000/DESIRED_FPS)<< "/"<< ((1000/DESIRED_FPS)+(1000/DESIRED_FPS)-passed) << endl;
  // 	int towait=((1000/DESIRED_FPS)+(1000/DESIRED_FPS)-passed);
  
  	int towait;//=fps/passFPS;
  	
  	float diff=(float)passFPS/(float)fps+1;
  	
  	float tomuch=diff-1000/DESIRED_FPS;
//  	cout<< "fps:"<<fps<<" passfps:"<<passFPS<<" diff:"<<diff<<" needed:"<<1000/DESIRED_FPS<<" to much:"<<tomuch<<endl;
  	
  /*	if(fps/(1000/passFPS) < 1000/DESIRED_FPS){
  		towait=2000.0f/DESIRED_FPS-fps/(1000.0f/passFPS);
  	}else{
  		towait=2000.0f/DESIRED_FPS-fps/(1000.0f/passFPS);
  	}*/
  	towait=1000/DESIRED_FPS-tomuch;//-passed;
  	
  /*	if(1000/DESIRED_FPS<passed){
  		towait=1000/DESIRED_FPS+1000/DESIRED_FPS-passed;
  	}else{
		towait=1000/DESIRED_FPS-(1000/DESIRED_FPS-passed);  		
  	}*/
  
   	if(towait<0){towait=0;}
   	//towait=0;
 //  	cout << "to wait: "<<towait<<endl;
    glutTimerFunc(towait, timer, 0);
}
void bsb_key_pressed(unsigned char key, int x, int y){
	actGame->key_pressed(key);//auf der momentan aktiven Spielklasse aufrufen
	//if(key==27){
	//	actGame->quit();
	//}
}
void bsb_key_released(unsigned char key, int x, int y){
	actGame->key_released(key);
}

void bsb_specialkey_pressed(int key, int x, int y){
	cout << "specialkey"<<key<<endl;
	if(key==GLUT_KEY_F11){
		actGame->toggleFullscreen();
	}
	if(key==GLUT_KEY_F2){
		actGame->takeScreenshot();
	}
}

void bsb_mouse_event(int button, int state, int x, int y){
	cout << "mouse_moved" << endl;
	actGame->mouse_event(button, state, x, y);
}
void bsb_mouse_moved(int x,int y){
	actGame->mouse_motion(x,y);
}
void Bsb_Game::hideCursor(){
	glutSetCursor(GLUT_CURSOR_NONE); 
}
void Bsb_Game::showCursor() {
	glutSetCursor(GLUT_CURSOR_INFO);
}
void Bsb_Game::initGL(){
	glewInit();
	glViewport(0, 0, width, height);						// Reset The Current Viewport And Perspective Transformation
	glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glLoadIdentity();										// Reset The Projection Matrix
	gluPerspective(45.0f, width / height, 0.1f, 1000.0f);	// Calculate The Aspect Ratio Of The Window
	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();


	glCullFace(GL_BACK); // Doesn't draw back faces
	glEnable(GL_CULL_FACE);//vom zuschauer wegzeigende dreiecke nicht rendern
	
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);               //This Will Clear The Background Color To Black
	glClearDepth(1.0f);                                  //Enables Clearing Of The Depth Buffer
	glClearStencil(0);  

	glEnable(GL_TEXTURE_2D); // Enable Texture Mapping


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //set alpha blending
	
	glEnable(GL_DEPTH_TEST);                            //Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                             //The Type Of Depth Test To Do


	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial (GL_FRONT_AND_BACK, GL_EMISSION ) ;
	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
	glFrustum( -1.6, 1.6, -1.2, 1.2, 1.5, 6.5 ); 
}

void Bsb_Game::setSize(int p_width,int p_height){
	//TODO viewfrustum umsetzen, falls dies während des Spiels passiert
	width=p_width;
	height=p_height;
	//glutChangeWindowSize(width,height);
}

void Bsb_Game::setTitle(char* p_title){
	glutSetWindowTitle(p_title);
}
void Bsb_Game::start(int arg_c,char** arg_v){
	actGame=this;
	glutInit(&arg_c,arg_v);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(width,height);
	this->window=glutCreateWindow("");
	
	this->init();
	
	initGL();//init openGL
	glutMouseFunc(bsb_mouse_event);
	glutMotionFunc(bsb_mouse_moved); // wenn die maus gedrückt ist
	glutPassiveMotionFunc(bsb_mouse_moved); // wenn wie maus losgelassen ist.
	glutSpecialFunc(bsb_specialkey_pressed);
	glutKeyboardFunc(bsb_key_pressed);//wir wollen auf die Tastatur hören
	glutKeyboardUpFunc(bsb_key_released);//wir wollen auf die Tastatur hören
	glutDisplayFunc(bsb_render);//wenn das Fenster verschoben wird, neu malen
	//glutIdleFunc(bsb_move);//immer weiter move&render 
	
	
	timer(0);//unseren Timer starten
	glutMainLoop();//die main-Schleife von GLUT starten
}

void Bsb_Game::quit(){
	glutDestroyWindow(window);
	exit(0);
}

void Bsb_Game::toggleFullscreen(){
	fullscreen=!fullscreen;
	if (fullscreen){
		glutFullScreen(); // Enable Fullscreen
	} else {
		glutReshapeWindow(width, height);
	}
}


void Bsb_Game::takeScreenshot(){
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

	//encode and save
	std::vector<unsigned char> buffer;
	encoder.encode(buffer, (const unsigned char*)imageData, width,height);
	LodePNG::saveFile(buffer, "screenshot.png");
}

