#include "../inc/game.h"

#include <ctime>


// --- main.cpp ---
// Die Hauptklasse unseres Spiels
//
// Änderungen:
// - 21.02.12: Code aufgeräumt (bit)
// - 22.02.12: Chunks werden nun gerendert
// - 22.02.12: Aggressive aufgeräumt
// - 25.03.12: Namespaces/smartPointer/unbennung in Cubiverse

int frames;
int lastframe;
int triangles;

Bsb_FPCamera* myCamera;
                     
//Position des einen Lichts, das wir haben

//jetzt nutzen wir Licht und Gegenlich
// TODO in eigene Input-Klasse auslagern

// letzte Position der Maus
int oldX=-1;
int oldY=-1;
float mouse_sensivity=0.1f;

// Sind diese Tasten gerade gedrückt?
bool k_left;
bool k_right;
bool k_up;
bool k_down;
 
GLfloat light_position[] = { 0.35, 0.5f, 0.15, 0.0 };
GLfloat light_position2[] = { -0.35, -0.5f, -0.15, 0.0 };
GLfloat light_ambient  [] = {0.1, 0.1, 0.1, 1.0};
GLfloat light_diffuse [] = {0.2, 0.2, 0.2, 1.0};
GLfloat light_ambient2  [] = {0.0, 0.0, 0.0, 1.0};
GLfloat light_diffuse2 [] = {-0.2, -0.2, -0.2, 1};
	
//Alte Koordinaten, um zu überprüfen ob sich die Kamera bewegt hat
int oldPlayerX, oldPlayerZ;

int main(int arg_c,char** arg_v){

	cubiverse::Game::pointer_t game=boost::make_shared<cubiverse::Game>();
	game->setSize(800,600);// Fenstergröße Setzen
	game->start(arg_c,arg_v);// das Spiel starten :)


	return 0;
}


//Fenster, Welt, Kamera und Licht inialisieren
void cubiverse::Game::init(){
	//Title setzten und Cursor verstecken
	setTitle("Cubiverse");
	//hideCursor();

	//Neue (test) world generieren
	GUI = boost::make_shared<cubiverse::GUI>(width, height);

	// First Person Kamera initialisieren
	myCamera=new Bsb_FPCamera(0,100,0);

	//Position des einen Lichts, das wir haben
	GLfloat light_position[] = { 0.35, 0.5f, 0.15, 0.0 };
	GLfloat light_position2[] = { -0.35, -0.5f, -0.15, 0.0 };
	//jetzt nutzen wir Licht und Gegenlich
	GLfloat light_ambient  [] = {0.1, 0.1, 0.1, 1.0};
	GLfloat light_diffuse [] = {0.2, 0.2, 0.2, 1.0};
	GLfloat light_ambient2  [] = {0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse2 [] = {-0.2, -0.2, -0.2, 1.0};
	// Licht aufsetzen und anschalten TODO in Lichtklasse auslagern
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
	
	glEnable (GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	voxelEditor = boost::make_shared<cubiverse::VoxelEditor>(); 

	boost::thread move( boost::bind( &cubiverse::Game::movePlayer, this));

	testWorldInit = false;


}

//TODO: Collision/Real running
void cubiverse::Game::movePlayer() {
	int oldtime = clock(); 
	while(true) {
		//cout << clock()-oldtime << endl << endl;
                if(clock()-oldtime > 20000) {
                        oldtime = clock();
			myCamera->move(0.02);
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	}
}
//Kamerabewegung bei Tastendruck
void cubiverse::Game::update(float p_seconds)
{
	if(k_left){
		myCamera->strafeLeft(2);
	}
	if(k_right){
		myCamera->strafeRight(2);
	}
	if(k_up){
		myCamera->walkForward(2);
	}
	if(k_down){
		myCamera->walkBackwards(2);
	}

}

//Unsere Hauptrenderfunktion
void cubiverse::Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //Der Bildschirm wird geleert TODO in Bsb_Game auslagern?
	glLoadIdentity(); //Alle Verschiebungen, Rotationen usw. werden zurückgesetzt.
	myCamera->lookThrough(); //Wir schauen durch die Kamera
	glEnable(GL_LIGHTING); //Licht an	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //Lichtposition wird gesetzt TODO in Lichtklasse auslagern
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2); //Lichtposition wird gesetzt TODO in Lichtklasse auslagern	
	glClearColor(0.0,0.0,0.0,0.0);

	glDisable(GL_TEXTURE_2D);
	
	int playerX = ((int)myCamera->position->x-(int)myCamera->position->x%16);
	int playerZ = ((int)myCamera->position->z-(int)myCamera->position->z%16);

	//Falls sich die Position des Spieler um 16 in X/Z geändert hat
	if(playerX != oldPlayerX || playerZ != oldPlayerZ) {

                //Liste mit den zu Generierenden Chunks refreshen
		this->test_world->clearChunksList();
		this->test_world->addChunksToList(-playerX, -playerZ);
                //Chunks außerhalb der sich löschen
                cout << "Player X:" << playerX << "Z:" << playerZ << endl;
                for(int i=-128; i < 128; i++) {
                        test_world->delChunk((-playerX)+128, playerZ+i);
                        test_world->delChunk((-playerX)-128, playerZ+i);
                        test_world->delChunk(playerX+i, (-playerZ)+128);
                        test_world->delChunk(playerX+i, (-playerZ)-128);
                }

		//Positionen neusetzten
		oldPlayerX = playerX; oldPlayerZ = playerZ;		
	}

	if(GUI->getMenu() == "Singleplayer" || GUI->getMenu() == "Multiplayer") {
		if(!testWorldInit) {
			test_world = boost::make_shared<cubiverse::World>(0.02, 64 , 6, 50);
			testWorldInit = true;
		}
		else test_world->render(playerX, playerZ);
	}

	else if(GUI->getMenu() == "Voxel")
		voxelEditor->render(-myCamera->position->x, -myCamera->position->y, -myCamera->position->z);

	switchToOrtho();// Das HUD wollen wir in 2D zeichnen
	//GUI zeichnen
	GUI->draw();

	//FPS Zeichnen
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f,1.0f,1.0f,1.0f);//Schriftfarbe auf weiß setzen
	GUI->drawFPS(currentFPS);
	glDisable(GL_TEXTURE_2D);
	backToFrustum();//im nächsten Frame wollen wir wieder 3D malen	
	glutSwapBuffers();//front- und back-buffer vertauschen => Das Bild wird angezeigt :) 
}

//Funktionen an Tastendrücke binden
void cubiverse::Game::key_pressed(unsigned char key){
	switch(key){
		case 27:
			GUI->changeMenu("Main");
			showCursor();
			break;
		case ' ':
			myCamera->jump();//TODO in die Spielerklasse auslagern und die Position der Kamera von Spieler abhängig machen
			break;
		case 'r':
			voxelEditor->checkCollision(0, 30, 10);
			break;
		case 'q':
			myCamera->down();
			break;
		case 'w':
			k_up=true;
			break;
		case 's':
			k_down=true;
			break;
		case 'a':
			k_left=true;
			break;
		case 'd':
			k_right=true;
			break;
	}
}

void cubiverse::Game::key_released(unsigned char key){
	switch(key){
		case 'w':
			k_up=false;
			break;
		case 's':
			k_down=false;
			break;
		case 'a':
			k_left=false;
			break;
		case 'd':
			k_right=false;
			break;
	}
}


void cubiverse::Game::mouse_event(int button, int state, int x, int y){
	if(button == 0) {
		string menu = GUI->checkButton(x,y);
		GUI->changeMenu(menu);
		cout << menu << endl;
		if(menu == "Main") {
			showCursor();
		}
		else if(menu == "Singleplayer" || menu == "Multiplayer") {
			hideCursor();
		}
		else if(menu == "Exit")
			quit();
	}
}

void cubiverse::Game::mouse_motion(int x,int y){
	if(oldX==-1){//Es ist noch nichts mit der Maus passiert
		oldX=x;
		oldY=y;
	}

	if(GUI->getMenu() != "Main") {
	
		myCamera->yaw((x-oldX)*mouse_sensivity);
		myCamera->pitch((y-oldY)*mouse_sensivity);
	
		//Maus in der Mitte des Bildschirms fangen
		if(oldX!=x){
			glutWarpPointer( width/2,height/2);
		}
		oldX=width/2;
		oldY=height/2;
	}
}


// zu 2D Projektion switchen
void cubiverse::Game::switchToOrtho(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0,width,0,height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// zu 3D Projektion switchen
void cubiverse::Game::backToFrustum(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

