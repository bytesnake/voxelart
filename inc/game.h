#ifndef GAME_H
#define GAME_H

#include "bsb_engine/bsb_game.h"
//#include "cube.h"
#include "PlayerBody.h"
#include "world.h"
#include "GUI.h"
#include "VoxelEditor.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp> 
#include <boost/bind.hpp>

// --- game.h ---
// 
//
// Änderungen:
// - 21.02.12: Unnötige Variablen entfernt (bit)


using namespace std;

namespace cubiverse {
	class Game:public Bsb_Game{
		public:
			typedef boost::shared_ptr<cubiverse::Game> pointer_t;

			virtual void render();
			virtual void init();
			virtual void update(float p_seconds);
			virtual void key_pressed(unsigned char key);
			virtual void key_released(unsigned char key);
			virtual void mouse_event(int button, int state, int x, int y);
			virtual void mouse_motion(int x,int y);
		
			void movePlayer();
			void switchToOrtho();
			void backToFrustum();
		private:
			bool testWorldInit;
			cubiverse::World::pointer_t test_world;
			cubiverse::GUI::pointer_t GUI;
			cubiverse::VoxelEditor::pointer_t voxelEditor;
	};
}
#endif
